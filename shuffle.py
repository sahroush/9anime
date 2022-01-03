import os
import random

path = input("path:")
names = os.listdir(path)

for name in names:
    extention = ""
    for i in name[::-1]:
        extention += i
        if i == '.':
            break
    extention = extention[::-1]
    os.rename(path + "/" + name, path + "/" + str(random.randint(1, 1000000000000000000000)) + extention)
