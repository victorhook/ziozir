import json
import threading
import tkinter as tk
from scrollframe import ScrollableFrame
from PIL import Image, ImageTk
import numpy as np
import os


GLYPH_FILEPATH = os.path.join(os.path.dirname(__file__), 'glyphs.json')
GLYPH_NAME = 'Glyph '


def default_values() -> list:
    return [[255 for i in range(8)] for i in range(8)]


def default_names(glyphs: dict) -> str:
    max = 0
    for glyph in glyphs:
        name = glyph.name
        if name.startswith(GLYPH_NAME):
            nbr = int(name.split(GLYPH_NAME)[1])
            if nbr > max:
                max = nbr

    return f'{GLYPH_NAME}{max+1}'


def glyph_list_to_np_matrix(data: list) -> bytes:
    buff = np.zeros((8, 8, 3), dtype=np.uint8)
    for row in range(8):
        for col in range(8):
            value = int(data[row][col]) * 255

            # Invert to make 1 -> black
            buff[row, col] = [255-value, 255-value, 255-value]

    return buff


class GlyphCell(tk.Frame):

    def __init__(self, master, click_cb, name: str, data: list):
        super().__init__(master, highlightthickness=1,
                         highlightbackground='black')
        self._img_width = 32
        self._img_height = 32

        self._name = tk.Label(self, text=name, width=32)
        self.image = tk.Label(self, relief='ridge', width=self._img_width,
                              height=self._img_height)
        self.update_data(name, data)

        self._name.pack(side='left')
        self.image.pack(side='left')

        self.bind('<Button-1>', lambda e: click_cb(self))
        self._name.bind('<Button-1>', lambda e: click_cb(self))
        self.image.bind('<Button-1>', lambda e: click_cb(self))

        self.deselect()

    def _toggle_bg(self, color):
        self.config(bg=color)
        self._name.config(bg=color)
        self.image.config(bg=color)

    def deselect(self):
        self._toggle_bg('white')

    def select(self):
        self._toggle_bg('green')

    def _click(self, e):
        GlyphCell.selected = self
        self.is_activate = not self.is_activate

    def update_data(self, name: str, data: list):
        self.name = name
        self.data = data
        self._name.config(text=self.name)
        self._update_image()

    def _update_image(self):
        data = glyph_list_to_np_matrix(self.data)
        image = Image.fromarray(data, mode='RGB')
        image = image.resize((self._img_width, self._img_height),
                             Image.NEAREST)
        self._image = ImageTk.PhotoImage(image)
        self.image.config(image=self._image)


class GlyphHandler(tk.LabelFrame):

    def __init__(self, master, app, width, height,
                 filepath: str = GLYPH_FILEPATH):
        super().__init__(master, text='Glyphs')
        self._select_cb = app.cb_select
        self._save_cb = app.cb_save

        self.content = ScrollableFrame(self, width, height)

        self.btn_container = tk.Frame(self)
        self.add_btn = tk.Button(self.btn_container, text='New glyph',
                                 command=self._add)
        self.del_btn = tk.Button(self.btn_container, text='Delete glyph',
                                 command=self._del)
        self.save_btn = tk.Button(self.btn_container, text='Save',
                                  command=self._save)

        self.add_btn.pack(side='left')
        self.del_btn.pack(side='left')
        self.save_btn.pack(side='left')

        self.content.pack()
        self.btn_container.pack()

        self._active_glyph = None

        self.filepath = filepath
        self.glyphs = []
        self.open()

    def _click(self, glyph):
        if self._active_glyph is not None:
            self._active_glyph.deselect()
        self._active_glyph = glyph
        self._active_glyph.select()
        self._select_cb(self._active_glyph)

    def _find_active_glyph(self) -> GlyphCell:
        for glyph in self.glyphs:
            if glyph.is_activate:
                return glyph
        return None

    def _save(self) -> None:
        if self._active_glyph is not None:
            self._save_cb(self._active_glyph)

    def _del(self) -> None:
        if self._active_glyph is not None:
            self.glyphs.remove(self._active_glyph)
            self._active_glyph.destroy()
            self.save()
            self._active_glyph = None

    def _add(self) -> None:
        self.add(GlyphCell(self.content(), self._click,
                 default_names(self.glyphs),
                 default_values()))
        threading.Thread(target=self.save).start()

    def get_glyphs(self) -> list:
        return self.glyphs

    def open(self) -> None:
        self.data = {}
        try:
            with open(self.filepath, 'r') as f:
                self.data = json.load(f)
                for name, data in self.data.items():
                    self.add(GlyphCell(self.content(), self._click, name,
                             data))
        except Exception:
            print(f'Failed to open file {self.filepath}. Creating new...')
            self.data = {}
            self.save()

    def add(self, glyph: GlyphCell) -> None:
        self.glyphs.append(glyph)
        glyph.pack()

    def save(self):
        data = {}
        for g in self.glyphs:
            data[g.name] = g.data

        with open(self.filepath, 'w') as f:
            json.dump(data, f, indent=4)
