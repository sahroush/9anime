import fitz
import io
from PIL import Image
import os
import shutil
from tkinter import Tk
from tkinter.filedialog import askopenfilename
Tk().withdraw()
file = askopenfilename()

import random
tmp = str(random.randint(1, 100000000)) + "/"

try:
    os.makedirs(tmp)
except:
    pass
pdf_file = fitz.open(file)
ims = []
for page_index in range(len(pdf_file)):
    page = pdf_file[page_index]
    image_list = page.get_images()
    for image_index, img in enumerate(page.get_images(), start=1):
        xref = img[0]
        base_image = pdf_file.extract_image(xref)
        image_bytes = base_image["image"]
        image_ext = base_image["ext"]
        a = open(tmp+str(page_index)+"."+image_ext,"wb")
        a.write(image_bytes)
        a.close()
        im = Image.open(tmp+str(page_index)+"."+image_ext)
        im = im.convert("RGB")
        #im = im.crop((0, 240, 1080, 1725))#for paradise books
        ims.append(im)
nf = file[:-4]+"_clean.pdf"
ims[0].save(nf, save_all = True, append_images=ims[1:])
for i in ims:
    i.close()
shutil.rmtree(tmp)
try:
    os.rmdir(tmp)
except:
    pass
