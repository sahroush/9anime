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

import imdb

dire = list(map(str, path.split('/')))[-1][:-6]

ia = imdb.Cinemagoer()
movies = ia.search_movie(dire)
a = 0
for i in movies:
    a += 1
    print(a, end = ". ")
    print(i['title'])
if(len(movies) == 0):
    exit(0)
x = int(input())
mv = movies[x - 1]

img_url = mv['full-size cover url']
import urllib.request

urllib.request.urlretrieve(img_url, path+"/"+"cover.jpg")


