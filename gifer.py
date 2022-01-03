from PIL import Image
from PIL import ImageChops
import os
path = input("path:")
names = os.listdir(path)
cnt = len(names)

img = []
for name in names:
    img.append(Image.open(path + "/" + name))
img[0].save(path + ".gif", save_all=True, append_images = img[1:], optimize = True, duration=20, loop = 0)
