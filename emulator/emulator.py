import tkinter as tk
from tkinter import ttk
from tkinter import filedialog
import threading
import os
from dataclasses import dataclass

from scrollframe import ScrollableFrame
from client import CpuClient, MemoryType, Action

WIDTH = 800
HEIGHT = 600


client: CpuClient = None


class Cell(tk.Frame):
    def __init__(self, master, address):
        super().__init__(master)
        self.address = tk.Label(self, text=self._address, width=6)
        self.value = tk.Entry(self, width=16)
        self.address.pack(side='left')
        self.value.pack(side='left')

    def update_value(self, new_value: int) -> None:
        self.value.config(text=str(new_value))


class MemoryFrame(tk.LabelFrame):
    def __init__(self, master: tk.Widget, title: str, cells: int = None,
                 *args, **kwargs):
        super().__init__(*args, master=master, text=title, **kwargs)
        self.frame = ScrollableFrame(self, 200, 400)

        if cells is not None:
            self.cells = [Cell(self.frame(), i) for i in range(cells)]
            for cell in self.cells:
                cell.pack()

    def add(self, cell: Cell) -> None:
        """ Adds a new cell to the frame. """
        self.cells.append(cell)

    def update_values(self, new_values: list) -> None:
        """ Updates all cells withing the frame with the new values. """
        for cell, new_value in zip(self.cells, new_values):
            cell.update_value(new_value)

    def pack(self, *args, **kwargs):
        self.frame.pack()
        super().pack(*args, **kwargs)


class RamFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'RAM', *args, **kwargs)


class FlashFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'Flash', *args, **kwargs)


class RegFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'Registers', *args, **kwargs)

        self._regs = [
            self.Register(self.frame(), 'R0'),
            self.Register(self.frame(), 'R1'),
            self.Register(self.frame(), 'R2'),
            self.Register(self.frame(), 'R3'),
            self.Register(self.frame(), 'R4'),
            self.Register(self.frame(), 'R5'),
            self.Register(self.frame(), 'R6'),
            self.Register(self.frame(), 'R7'),
            self.Register(self.frame(), 'SP'),
            self.Register(self.frame(), 'PC'),
            self.Register(self.frame(), 'REG')
        ]
        for reg in self._regs:
            reg.pack()

    class Register(tk.Frame):
        def __init__(self, master, name):
            super().__init__(master)
            self._name = name
            self._value = '0'
            self.name = tk.Label(self, text=self._name, width=6)
            self.value = tk.Label(self, text=self._value, width=10)
            self.name.pack(side='left')
            self.value.pack(side='left')


class ToolMenu(tk.Frame):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._btn_next = tk.Button(self, text='Next instruction')
        self._btn_next.pack(side='left')

        self._btn_run = tk.Button(self, text='Run program')
        self._btn_run.pack(side='left')

        self._btn_pause = tk.Button(self, text='Pause')
        self._btn_pause.pack(side='left')

        self._btn_reset = tk.Button(self, text='Reset')
        self._btn_reset.pack(side='left')


class App(tk.Tk):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title('ZioZir - Emulator')
        self.geometry(f'{WIDTH}x{HEIGHT}')

        self.client = CpuClient()
        self.mem_info = self.client.read_memory_info()

        self.frame = tk.Frame(self)
        self.tools = ToolMenu(self)

        self.f_reg = RegFrame(self.frame, self.mem_info['regs'])
        self.f_ram = RamFrame(self.frame, self.mem_info['ram'])
        self.f_flash = FlashFrame(self.frame, self.mem_info['flash'])

        self.tools.pack()

        self.f_ram.pack(side='left')
        self.f_reg.pack(side='left')
        self.f_flash.pack(side='left')

        self.frame.pack()

        self._read_initial_values()

    def _update(self) -> None:
        """ Reads all values from memory and updates the view. """
        self.f_ram.update_values(
            self.client.read(MemoryType.RAM, 0, self.mem_info['ram'])
        )
        self.f_reg.update_values(
            self.client.read(MemoryType.REGS, 0, self.mem_info['regs'])
        )
        self.f_flash.update_values(
            self.client.read(MemoryType.FLASH, 0, self.mem_info['flash'])
        )


if __name__ == '__main__':
    app = App()
    app.mainloop()
