import numpy as np
import tkinter as tk
from tkinter import ttk
from tkinter import filedialog
import os

from params import Param, ParamHolder
from glyph import GlyphHandler, GlyphCell
from src_generator import generate_source_code
from styles import STYLE_LABEL, STYLE_FRAME, STYLE_BUTTON


DIMENSION_X = 160
DIMENSINO_Y = 144


class Cell(tk.Frame):
    WIDTH = 40
    HEIGHT = 40
    COLORS = {
        False: 'White',
        True: 'Black'
    }

    def __init__(self, master, row: int, col: int):
        super().__init__(master, width=self.WIDTH, height=self.HEIGHT,
                         **STYLE_FRAME)
        self.on = False
        self._hover = False
        self._master = master

        self.bind('<Button-1>', self._toggle)
        self.bind('<Control-Enter>', self._move_fill)
        self.bind('<Shift-Enter>', self._move_clear)
        self.bind('<Leave>', self._leave)

        self._set_bg()

    def _leave(self, e):
        self._hover = False

    def _move_clear(self, e):
        if not self._hover:
            self._hover = True
            self.update_value(0)

    def _move_fill(self, e):
        if not self._hover:
            self._hover = True
            self.update_value(1)

    def _toggle(self, *e):
        self.on = not self.on
        self._set_bg()

    def update_value(self, value: int) -> None:
        self.on = value == 1
        self._set_bg()

    def _set_bg(self):
        self.config(bg='black' if self.on else 'white')


class Canvas(tk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, text="8x8 Map", **STYLE_FRAME)

        self.top_frame = tk.Frame(self, **STYLE_FRAME)

        self.name = Param(self.top_frame, 'Glyph name')
        self.help = tk.Label(self.top_frame, text='Ctrl to Fill, Shift to clear',
                             **STYLE_LABEL)
        self._clear = tk.Button(self.top_frame, text='Clear', **STYLE_BUTTON,
                                command=self.clear)

        self.name.grid(row=0, column=0, columnspan=2, pady=10)
        self.help.grid(row=1, column=0, padx=10, pady=10)
        self._clear.grid(row=1, column=1, padx=10, pady=10)

        self.grid_frame = tk.Frame(self, **STYLE_FRAME)

        self.top_frame.pack()
        self.grid_frame.pack()

        self.cells = []
        for row in range(8):
            self.cells.append([])
            tk.Label(self.grid_frame, text=str(row), width=4, height=1,
                    **STYLE_LABEL).grid(row=row+1, column=0)
            tk.Label(self.grid_frame, text=str(row), width=2, height=1,
                    **STYLE_LABEL).grid(row=0, column=row+1)
            for col in range(8):
                new_cell = Cell(self.grid_frame, row, col)
                new_cell.grid(row=row+1, column=col+1)
                self.cells[row].append(new_cell)

    def clear(self):
        self.update_values(np.zeros((8, 8)).tolist())

    def release(self):
        self.mouse_down = False

    def click(self):
        self.mouse_down = True

    def update_values(self, values: list) -> None:
        """ [0, 1, 2] """
        for row in range(8):
            for col in range(8):
                self.cells[row][col].update_value(values[row][col])

    def get_cells(self) -> np.ndarray:
        matrix = np.zeros((8, 8))
        for row in range(8):
            for col in range(8):
                matrix[row, col] = 1 if self.cells[row][col].on else 0
        return matrix

    def get_values(self) -> list:
        """ Returns a tuple of: (glyph name, list of values) """
        return self.name.get_value(), self.get_cells().tolist()

    def set_cell(self, glyph: GlyphCell) -> None:
        self.name.set_value(glyph.name)
        self.update_values(glyph.data)


class Output(tk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, text="Output", **STYLE_FRAME)
        self.textbox = tk.Text(self, width=64, height=12,
                               font=("Helvetica", 16))
        self.textbox.pack(padx=10, pady=5)

    def update_text(self, values: np.ndarray, name: str):
        self.textbox.delete('1.0', 'end')

        text = '\nglyph_t __GLYPH_%s = {\n' % name

        for row in range(8):
            text += '    '

            for col in range(8):
                # 8x8 -> 64  |   0-63
                value = int(values[row, col])
                text += f'{value}, '

            text += '\n'

        text += '};'
        self.textbox.insert('current', text)
        return text


class ToolBox(tk.LabelFrame):
    def __init__(self, master):
        super().__init__(master, text="Tools", **STYLE_FRAME)

        self.dims = ParamHolder(self, 'Dimension')
        self.dims.add('X', DIMENSION_X)
        self.dims.add('Y', DIMENSINO_Y)
        self.dims.pack(side='left', padx=10, pady=10)

        self.update_btn = tk.Button(self, text='Generate source file',
                                    command=master.cb_save_source,
                                    **STYLE_BUTTON)
        self.update_btn.pack(side='left')

    def update_status(self, text: str) -> None:
        self.status.config(text=text)


class App(tk.Tk):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title('Pixel creator')
        self.config(bg=STYLE_FRAME['bg'])

        self.tools = ToolBox(self)
        self.tools.pack(fill='x', padx=20, pady=10)

        self.frame = tk.Frame(self, **STYLE_FRAME)
        self.status = tk.Label(self.frame, **STYLE_LABEL)
        self.canvas = Canvas(self.frame)
        #self.output = Output(self.frame)
        self.glyphs = GlyphHandler(self.frame, self, 300, 300)

        self.status.grid(row=0, columnspan=2, pady=10)
        self.glyphs.grid(row=1, column=0, padx=30, pady=20)
        self.canvas.grid(row=1, column=1, padx=30, pady=20)
        #self.output.grid(row=2, column=0, columnspan=2, padx=30, pady=20)

        self.frame.pack(padx=50, pady=50)

    def cb_save_source(self) -> None:
        filepath = filedialog.asksaveasfilename()
        filename = os.path.basename(filepath)
        src = generate_source_code(filename, self.glyphs.get_glyphs())
        with open(filepath, 'w') as f:
            f.write(src)
        self.update_status(f'Source code saved to {filepath}')

    def cb_save(self, glyph: GlyphCell) -> None:
        glyph_name, data_values = self.canvas.get_values()
        glyph.update_data(glyph_name, data_values)
        self.glyphs.save()
        self.update_status('Saved')

    def cb_select(self, glyph: GlyphCell) -> None:
        self.canvas.set_cell(glyph)

    def update_status(self, text: str, color: str = 'green') -> None:
        self.status.config(text=text, fg=color)
        # Clear the text after x seconds.
        self.after(3000, lambda: self.status.config(text=''))


if __name__ == '__main__':
    app = App()

    s = ttk.Style()
    s.theme_use('alt')
    print(s.theme_names())
    print(s.theme_use())

    app.mainloop()

    """

    putChar(x, y, char);
    x = DIM_X / 8
    y = DIM_Y / 8

    """