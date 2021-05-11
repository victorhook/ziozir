import tkinter as tk


STYLE_FRAME = {
    'bg': 'white',
    'relief': 'ridge'
}

STYLE_LABEL = {
    'bg': 'white',
    'fg': 'black',
}

DEFAULT_PADDING = {
    'padx': 10,
    'pady': 10
}


class Label(tk.Label):

    def __init__(self, master):
        super().__init__(master, **STYLE_LABEL)


class App(tk.Tk):

    def __init__(self):
        super().__init__()
        self.title('Table-To-Markdown')
        self.config(bg='white')

        self.entry = tk.Entry(self, **STYLE_LABEL, width=32, font=("Lucida Console", 20))
        self.entry.bind('<Key>', self.key)
        self.label = tk.Entry(self, **STYLE_LABEL, width=32, font=("Lucida Console", 20))

        self.entry.grid(row=0, column=0)
        self.label.grid(row=1, column=0)

    def key(self, key):
        length = len(self.entry.get()) + 1
        indices = ''.join(str(a) for a in range(length))
        #self.label.config(text=indices)

if __name__ == '__main__':
    app = App()
    app.mainloop()