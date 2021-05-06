import tkinter as tk
from tkinter import filedialog
import threading
import os
from dataclasses import dataclass

WIDTH = 800
HEIGHT = 600


class MemoryFrame(tk.LabelFrame):
    def __init__(self, master, title, *args, **kwargs):
        super().__init__(*args, master=master, text=title, **kwargs)
        self.scroll = tk.Scrollbar(self, orient='vertical')
        self.scroll.pack(side='right', fill='y')
        
        
        


class Cell(tk.Frame):
    def __init__(self, master, address):
        super().__init__(master)
        self._address = address
        self._value = '0'
        self.address = tk.Label(self, text=self._address, width=6)
        self.value = tk.Label(self, text=self._value, width=10)
        self.address.pack(side='left')
        self.value.pack(side='left')


class RamFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'RAM', *args, **kwargs)
        self._ram = [Cell(self, str(addr)) for addr in range(50)]
        for cell in self._ram:
            cell.pack()

class FlashFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'Flash', *args, **kwargs)



class RegFrame(MemoryFrame):
    def __init__(self, master, *args, **kwargs):
        super().__init__(master, 'Registers', *args, **kwargs)

        self._regs = [
            self.Register(self, 'R0'),
            self.Register(self, 'R1'),
            self.Register(self, 'R2'),
            self.Register(self, 'R3'),
            self.Register(self, 'R4'),
            self.Register(self, 'R5'),
            self.Register(self, 'R6'),
            self.Register(self, 'R7'),
            self.Register(self, 'SP'),
            self.Register(self, 'PC'),
            self.Register(self, 'REG')
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

        self.frame = tk.Frame(self)
        self.tools = ToolMenu(self)

        self.f_ram = RamFrame(self.frame)
        self.f_reg = RegFrame(self.frame)
        self.f_flash = FlashFrame(self.frame)
        

        self.tools.pack()
        
        self.f_ram.pack(side='left')
        self.f_reg.pack(side='left')
        self.f_flash.pack(side='left')

        self.frame.pack()


if __name__ == '__main__':
    app = App()
    app.mainloop()
