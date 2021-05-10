import tkinter as tk
from tkinter import filedialog
import numpy as np
import threading
import os
from PIL import Image, ImageTk


SCREEN_WIDTH = 600
SCREEN_HEIGHT = 600


def on_file_load(asd):
    print(asd)


class Screen(tk.Canvas):

    def __init__(self, width, height, *args, **kwargs):
        super().__init__(*args, width=width, height=height, **kwargs)
        self._image = None
        self.width = width
        self.height = height

    def refresh(self, data: np.ndarray) -> None:
        image = Image.fromarray(data)
        self._image = ImageTk.PhotoImage(image)
        self.create_image((self.width/2, self.height/2), image=self._image)


class ToolMenu(tk.Frame):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._btn_load = tk.Button(self, text='Load program',
                                   command=lambda: on_file_load(filedialog.askopenfile(mode='r')))
        self._btn_load.pack()


class FileWatcher(threading.Thread):
    def __init__(self, filepath, on_change):
        super().__init__(daemon=True)
        if not os.path.exists(filepath):
            raise FileExistsError(f'Can\'t find filepath: {filepath}!')

        self._filepath = filepath
        self._on_change = on_change

    def run(self) -> None:
        """ Starts watching for changes on the given filepath.
            When a change has been made to the file, the data from the
            file is read and sent to the callback method on_change.
        """
        last_change = os.stat(self._filepath).st_mtime

        while 1:
            m_time = os.stat(self._filepath).st_mtime
            if m_time != last_change:
                self._notify_changes()
                last_change = m_time

    def _notify_changes(self) -> None:
        with open(self._filepath, 'rb') as f:
            self._on_change(f.read())


class MainWindow(tk.Tk):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.title('ZioZir')

        self.data = np.zeros([SCREEN_WIDTH, SCREEN_HEIGHT, 3], dtype=np.uint8)

        self.frame = tk.Frame(self)

        self.title_label = tk.Label(self.frame, text='ZioZor - Virtual Machine')
        self.title_label.pack()

        self.toolbox = ToolMenu(self.frame)
        self.toolbox.pack()

        self.screen = Screen(SCREEN_WIDTH, SCREEN_HEIGHT, master=self.frame,)
        self.screen.refresh(self.data)
        self.screen.pack()

        self.frame.pack(fill=tk.BOTH, expand=True)

        f = FileWatcher('test', lambda data: print(data))
        f.start()


if __name__ == '__main__':
    window = MainWindow()
    window.mainloop()
