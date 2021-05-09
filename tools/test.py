import tkinter as tk

root = tk.Tk()
k = tk.LabelFrame(root, bg='blue')

class K(tk.LabelFrame):

    def __init__(self, master):
        super().__init__(master, bg='blue')


k = K(root)
