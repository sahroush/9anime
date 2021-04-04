import pyautogui as ms
import time

l , r = tuple(map(int, input("L R:").split()))

def add():
    pos = ms.locateCenterOnScreen('error.png')
    while(pos != None):
        ms.keyDown('f5')
        ms.keyUp('f5')
        time.sleep(1)
        pos = ms.locateCenterOnScreen('error.png')
    ms.moveTo(1220 , 700 , 0.1)
    ms.click(1220, 700)
    time.sleep(1)
    pos = ms.locateCenterOnScreen('dl.png')
    ms.moveTo(pos.x, pos.y , 0.5)
    ms.click(pos.x, pos.y)
    time.sleep(4)
    ms.hotkey("ctrlleft", "w")
    ms.click(700, 750)
    time.sleep(4)

for i in range(l , r+1):
    add()
