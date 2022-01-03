from PIL import Image
from PIL import ImageChops
import os
path = input("path:")
names = os.listdir(path)
cnt = len(names)

def hsh(name):
    lim = 10
    img = Image.open(path + "/" +  name)
    img = img.convert("RGB")
    w = img.size[0]
    h = img.size[1]
    m = []
    num = []
    for i in range(lim):
        m += [[0, 0 , 0]]
        num += [0]
    sz = w * h
    cnt = 0
    for x in range(w):
        for y in range(h):
            p = img.getpixel((x , y))
            ls = cnt * lim // sz
            num[ls] += 1
            for i in range(3):
                try:
                    m[ls][i] += p[i]
                except:
                    print(p)
                    print(name)
                    os.exit()
            cnt += 1
    for i in range(lim):
        for j in range(3):
            m[i][j] /= num[i]
    img.close()
    return m

def Sz(name):
    img = Image.open(path + "/" +  name)
    w = img.size[0]
    h = img.size[1]
    img.close()
    return w * h

h = []

for i in range(cnt):
    print(i , "/" , cnt, "   ", int(i/cnt*100) , "%")
    
    h += [hsh(names[i])]

def eq(h1 ,h2):
    lim = len(h1)
    for i in range(lim):
        for j in range(3):
            if((h1[i][j] - h2[i][j])**2 > 4):
                return False
    return True

todel = []
sz = []
for i in range(cnt):
    todel += [0]
    sz += [Sz(names[i])]

for i in range(cnt):
    if(todel[i]):
        pass
    for j in range(i):
        if(todel[j]):
            pass
        if(eq(h[i] , h[j])):
            if(sz[i] > sz[j]):
                todel[j] = 1
            else:
                todel[i] = 1
            
            
for i in range(cnt):
    if(todel[i]):
        os.remove(path + "/" + names[i])
