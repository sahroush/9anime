import pygame, os, sys, random, time
from pygame.locals import *
from PIL import Image 

W, H = 1404, 1872
grey = (119,136,153)
white = (255, 255, 255)

pygame.init()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((W, H))

a = open("a.txt", 'r')
a = a.readlines()
i = 0

images = []

cnt = 0

while True:
    screen.fill(white)
    screenshot = pygame.Surface((W, H))
    for j in range(17):
        while(i < len(a) and len(a[i]) < 5):
            i += 1
        if(i == len(a)):
            break
        font = pygame.font.Font("font.ttf", 40)
        txt_surface = font.render(a[i][:-1], True, grey)
        screen.blit(txt_surface, (200, 100 + 100*j))
        i += 1
    pygame.display.update()
    screenshot.blit(screen, (0, 0))
    pygame.image.save(screenshot, "screenshot%d.jpg"%cnt)
    images.append(Image.open("screenshot%d.jpg"%cnt))
    cnt += 1
    if(i == len(a)):
        break

images[0].save("res.pdf", "PDF" ,resolution=100.0, save_all=True, append_images=images[1:])
for i in range(cnt):
    os.remove("screenshot%d.jpg"%i)
