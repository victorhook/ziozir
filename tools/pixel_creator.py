import numpy as np
import tkinter as tk
from tkinter import ttk

from glyph import Glyph, GlyphHandler, GlyphCell
from scrollframe import ScrollableFrame

DIMENSION_X = 160
DIMENSINO_Y = 144


class Canvas(ttk.LabelFrame):

    def __init__(self, master, *args, **kwargs):
        super().__init__(master, *args, text="8x8 Map", **kwargs)

        self.cells = []
        for row in range(8):
            self.cells.append([])
            tk.Label(self, text=str(row), width=4, height=1).grid(row=row+1,
                                                                  column=0)
            tk.Label(self, text=str(row), width=2, height=1).grid(row=0,
                                                                  column=row+1)

            for col in range(8):
                new_cell = Cell(self, row, col)
                new_cell.grid(row=row+1, column=col+1)
                self.cells[row].append(new_cell)

    def update_values(self, values: list) -> None:
        """ [0, 1, 2] """
        for row in range(8):
            for col in range(8):
                self.cells[row][col].update_value(row * 8 + col)

    def get_cells(self) -> np.ndarray:
        matrix = np.zeros((8, 8))
        for row in range(8):
            for col in range(8):
                matrix[row, col] = 1 if self.cells[row][col].on else 0
        return matrix

    def set_cell(self, glyph: Glyph) -> None:
        self.update_values(glyph.data)


class Cell(tk.Frame):
    WIDTH = 40
    HEIGHT = 40
    COLORS = {
        False: 'White',
        True: 'Black'
    }

    def __init__(self, master: Canvas, row: int, col: int):
        super().__init__(master, width=self.WIDTH, height=self.HEIGHT,
                         borderwidth=1, relief="solid")
        self.on = True
        self._click(1)
        self.bind('<Button-1>', self._click)

    def _click(self, e):
        self.on = not self.on
        self._set_bg()

    def _set_bg(self) -> None:
        self.config(bg=self.COLORS[self.on])

    def update_value(self, value: int) -> None:
        self.on = value == 1
        self._set_bg()


class Output(ttk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, text="Output")
        self.textbox = tk.Text(self, width=64, height=12, font=("Helvetica", 16))
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


class Param(tk.Frame):

    def __init__(self, master, text, *args, value=None, **kwargs):
        super().__init__(master, *args, **kwargs)
        self.label = tk.Label(self, text=text)
        self.entry = tk.Entry(self)
        if value is not None:
            self.entry.insert(0, value)

        self.label.pack(side='left', padx=2, pady=2)
        self.entry.pack(side='left', padx=2, pady=2)


class ParamHolder(ttk.LabelFrame):
    def __init__(self, master, title, *args, **kwargs):
        super().__init__(master, *args, text=title, **kwargs)
        self.params = {}

    def add(self, name: str, value=None):
        new_param = Param(self, name, value=value)
        new_param.pack(side='left')
        self.params[name] = (new_param)

    def read(self, name: str) -> str:
        return self.params[name].entry.get()


class ToolBox(ttk.LabelFrame):
    def __init__(self, master):
        super().__init__(master, text="Tools")

        self.dims = ParamHolder(self, 'Dimension')
        self.dims.add('X', DIMENSION_X)
        self.dims.add('Y', DIMENSINO_Y)

        self.output = ParamHolder(self, 'Glyph')
        self.output.add('Glyph name', 'A')
        self.output.add('Outputfile', 'src/glyphs.c')

        self.auto = ttk.Checkbutton(self, text='Auto output')

        self.dims.pack(side='left')
        self.output.pack(side='left')
        self.auto.pack(side='left')

    def is_auto(self) -> bool:
        return self.auto.state()[0] == 'selected'

    def get_outputfile(self) -> str:
        return self.output.read('Outputfile')

    def get_glyphname(self) -> str:
        return self.output.read('Glyph name')


class App(tk.Tk):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title('Pixel creator')

        self.tools = ToolBox(self)
        self.tools.pack()

        self.update_btn = ttk.Button(self, text='Update', command=self._update)
        self.update_btn.pack()

        self.frame = tk.Frame(self)
        self.canvas = Canvas(self.frame)
        self.output = Output(self.frame)
        self.glyphs = GlyphHandler(self.frame, self, 300, 300)

        self.glyphs.grid(row=0, column=0, padx=30, pady=20)
        self.canvas.grid(row=0, column=1, padx=30, pady=20)
        self.output.grid(row=1, column=0, columnspan=2, padx=30, pady=20)

        self.frame.pack()

    def cb_save(self, glyph: GlyphCell) -> None:
        glyph_values = self.canvas.get_cells()
        print(glyph_values)
        glyph.update_data(glyph_values)
        self.glyphs.save()

    def cb_select(self, glyph: GlyphCell) -> None:
        self.canvas.set_cell(glyph)

    def _update(self):
        pass

    def _append_to_file(self, filepath: str, data: str):
        with open(filepath, 'a') as f:
            f.write(data)


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