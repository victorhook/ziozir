import tkinter as tk
from tkinter import ttk

from styles import STYLE_LABEL, STYLE_FRAME


class Param(tk.Frame):

    def __init__(self, master, text, *args, value=None, **kwargs):
        super().__init__(master, **STYLE_FRAME)
        self.label = tk.Label(self, text=text, **STYLE_LABEL)
        self.entry = tk.Entry(self)
        if value is not None:
            self.entry.insert(0, value)

        self.label.pack(side='left', padx=2, pady=2)
        self.entry.pack(side='left', padx=2, pady=2)

    def get_value(self) -> str:
        return self.entry.get()

    def set_value(self, value: str):
        self.entry.delete(0, 'end')
        self.entry.insert(0, value)


class ParamHolder(tk.LabelFrame):
    def __init__(self, master, title, *args, **kwargs):
        super().__init__(master, *args, text=title, **kwargs, **STYLE_FRAME)
        self.params = {}

    def add(self, name: str, value=None):
        new_param = Param(self, name, value=value)
        new_param.pack(side='left')
        self.params[name] = (new_param)

    def read(self, name: str) -> str:
        return self.params[name].entry.get()
