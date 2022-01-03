import os, shutil
from tkinter import Tk
from tkinter.filedialog import askdirectory

Tk().withdraw()
path = askdirectory()

names = os.listdir(path)

open(path + "/.nomedia", "w").close()

for name in names:
    if name[0] == '_':
        p = path + "/" + name
        inside = os.listdir(p)
        for ins in inside:
            if ins[0] != '.':
                shutil.move(p + "/" + ins , path + "/" + ins)
        shutil.rmtree(p)
