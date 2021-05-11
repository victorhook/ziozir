import tkinter as tk


STYLE_FRAME = {
    'bg': 'white',
    'relief': 'ridge'
}

STYLE_LABEL = {
    'bg': 'white',
    'fg': 'black',
    'font': ('Courier', 16)
}

DEFAULT_PADDING = {
    'padx': 10,
    'pady': 10
}


class Cell(tk.Entry):

    def __init__(self, master):
        super().__init__(master, **STYLE_LABEL)


class Label(tk.Label):

    def __init__(self, master):
        super().__init__(master, **STYLE_LABEL)


class TableContainer(tk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, text='Tables', **STYLE_FRAME)
        self.cells = self._build_default_cells()
        self.labels = []

        self.t = tk.Button(self, text='Test',command= lambda *e: self.add_row())
        self.t.grid(row=4, column=4)
        self.t = tk.Button(self, text='Test2',command= lambda *e: self.add_col())
        self.t.grid(row=4, column=5)
        
    def _add_label(self, row, col):
        label = Label(self, text=str(row), **STYLE_LABEL)
        label.grid(row=row, column=0)

    def add_row(self):
        row = len(self.cells)
        self.cells.append([])
        for col in range(len(self.cells[0])):
            new_cell = Cell(self)
            self.cells[row].append(new_cell)
            new_cell.grid(row=row, column=col+1)

    def add_col(self):
        col = len(self.cells[0])
        for row in range(len(self.cells)):
            new_cell = Cell(self)
            self.cells[row].append(new_cell)
            new_cell.grid(row=row+1, column=col)

    def del_row(self):
        pass
    def del_col(self):
        pass
    
    def _build_default_cells(self):
        cells = []

        for row in range(3):
            cells.append([])
            for col in range(3):
                new_cell = Cell(self)
                cells[row].append(new_cell)
                new_cell.grid(row=row+1, column=col+1)

        return cells


class Ouput(tk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, text='Output', **STYLE_FRAME)
        self.text = tk.Text(self)
        
        self.frame_btns = tk.Frame(self)
        self.btn_copy = tk.Button(self.frame_btns, text='Copy', 
                                  command=self.copy)
        self.btn_save = tk.Button(self.frame_btns, text='Save', 
                                  command=self.save)
        self.text.pack()
        self.frame_btns.pack()

    def copy(self):
        pass

    def save(self):
        pass


class App(tk.Tk):

    def __init__(self):
        super().__init__()
        self.title('Table-To-Markdown')
        self.config(bg='white')

        self.table = TableContainer(self)
        self.output = Ouput(self)

        self.table.grid(row=0, column=0, **DEFAULT_PADDING)
        self.output.grid(row=0, column=1, **DEFAULT_PADDING)


if __name__ == '__main__':
    app = App()
    app.mainloop()