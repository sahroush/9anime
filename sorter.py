from PIL import Image
from PIL import ImageChops
import os
import shutil
path = input("path:")
names = os.listdir(path)
cnt = len(names)

ret = 0.1

def ratio(name):
    global ret
    img = Image.open(path + "/" +  name)
    w = img.size[0]
    h = img.size[1]
    img.close()
    return int((h/w)//ret)

mn = 100000000
mx = -mn

r = []

for name in names:
    mx = max(mx , ratio(name))
    mn = min(mn , ratio(name))
    r.append(ratio(name))

for i in range(mn , mx + 1):
    if i in r:
        os.makedirs(path + "/" + str(i))
for name in names:
    im = Image.open(path + "/" + name)
    im = im.convert("RGB")
    r = ratio(name)
    im = im.resize((1240 , int((1240 * ret) * r)))
    im.save(path + "/" + name)
    shutil.move(path + "/" + name, path + "/" + str(r) + "/" + name)
