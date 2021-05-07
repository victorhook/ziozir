import tkinter as tk


class ScrollableFrame(tk.Frame):
    """ Wrapper class that allows a frame to be scrollable. """

    def __init__(self, master, width, height, *args, **kwargs):
        super().__init__(master, *args, **kwargs)

        self._canvas = tk.Canvas(self, width=width, height=height)
        self._scroll = tk.Scrollbar(self, orient='vertical',
                                    command=self._canvas.yview)

        self._scrollable_frame = tk.Frame(self._canvas)
        self._scrollable_frame.bind('<Configure>',
                                    lambda e: self._canvas.configure(
                                        scrollregion=self._canvas.bbox('all'))
                                    )

        self._canvas.create_window((0, 0), window=self._scrollable_frame,
                                    anchor='nw')
        self._canvas.configure(yscrollcommand=self._scroll.set)

        self._canvas.pack(side="left", fill="both", expand=True)
        self._scroll.pack(side="right", fill="y")

    def __call__(self) -> tk.Frame:
        return self._scrollable_frame

    def frame(self) -> tk.Frame:
        return self._scrollable_frame

if __name__ == '__main__':
    root = tk.Tk()
    f = ScrollableFrame(root)
    for i in range(30):
        t = tk.Label(f(), text='ajdslahsd')
        t.pack()

    f.pack()
    root.mainloop()