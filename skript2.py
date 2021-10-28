import pyautogui as ms
import time

l , r = tuple(map(int, input("L R:").split()))

dlbutton = 0
nextbutton = 0
prcbutton = 0

def add():
    time.sleep(1)
    ms.moveTo(dlbutton.x , dlbutton.y - 80 , 0.5)
    ms.keyDown("ctrlleft")
    ms.click()
    ms.keyUp("ctrlleft")
    ms.moveTo(nextbutton.x, nextbutton.y)
    ms.click()    

def prc():
    time.sleep(1)
    ms.click()
    ms.hotkey("ctrlleft", "tab")
    

time.sleep(4)

dlbutton = ms.Point(x=1198, y=859)#ms.locateCenterOnScreen('rep.png')
nextbutton = ms.Point(x=729, y=823)#ms.locateCenterOnScreen('nxt.png')

for i in range(l , r+1):
    add()

time.sleep(1)
ms.hotkey("ctrlleft", "tab")
prcbutton = ms.Point(x=931, y=505)#ms.locateCenterOnScreen('dl.png')
ms.moveTo(prcbutton.x, prcbutton.y)

for i in range(l , r+1):
    prc()

ms.hotkey("ctrlleft", "tab")
dlbutton = ms.Point(x=1315, y=566)#ms.locateCenterOnScreen('start.png')
ms.moveTo(dlbutton.x , dlbutton.y , 0.5)

for i in range(l , r+1):
    prc()

for j in range(5):
    time.sleep(5)
    ms.hotkey("ctrlleft", "tab")
    for i in range(l , r+1):
        ms.click()
        time.sleep(2)
        ms.hotkey('f5' , 'enter')
        time.sleep(1)
        ms.hotkey('ctrlleft', 'tab')

ms.hotkey("ctrlleft", "tab")    
for i in range(l, r + 1):
    ms.hotkey("ctrlleft", "w")


