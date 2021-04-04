import pyautogui as ms
import time

l , r = tuple(map(int, input("L R:").split()))

def add():
    time.sleep(4)
    pos = ms.locateCenterOnScreen('rep.png')
    ms.moveTo(pos.x , pos.y - 80 , 0.5)
    ms.click()
    time.sleep(2)
    pos = ms.locateCenterOnScreen('dl.png')
    ms.moveTo(pos.x, pos.y , 0.5)
    ms.click()
    time.sleep(2)
    pos = ms.locateCenterOnScreen('start.png')
    ms.moveTo(pos.x, pos.y , 0.5)
    ms.click()
    time.sleep(3)
    ms.hotkey("ctrlleft", "w")
    pos = ms.locateCenterOnScreen('nxt.png')
    ms.moveTo(pos.x, pos.y)
    ms.click()

for i in range(l , r+1):
    add()
