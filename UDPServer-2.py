# importing socket module
import socket
import time

from pynput.keyboard import Key, Controller

keyboard = Controller()
UDP_IP = "<enter master ip>"
UDP_PORT = 8085

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(2)
    msg=data.decode().strip()
    print(msg)
    if msg=="B6":
        keyboard.press(Key.right)
        time.sleep(1)
        keyboard.release(Key.right)
    elif msg=="B3":
        with keyboard.pressed(Key.up):
            keyboard.press(Key.right)
            time.sleep(1)
            keyboard.release(Key.right)
    elif msg=="B2":
        keyboard.press(Key.up)
        time.sleep(1)
        keyboard.release(Key.up)
    elif msg=="B1":
        with keyboard.pressed(Key.up):
            keyboard.press(Key.left)
            time.sleep(1)
            keyboard.release(Key.left)
    elif msg=="B4":
        keyboard.press(Key.left)
        time.sleep(1)
        keyboard.release(Key.left)
    elif msg=="B9":
        with keyboard.pressed(Key.down):
            keyboard.press(Key.right)
            time.sleep(1)
            keyboard.release(Key.right)
    elif msg=="B8":
        keyboard.press(Key.down)
        time.sleep(1)
        keyboard.release(Key.down)
    elif msg=="B7":
        with keyboard.pressed(Key.down):
            keyboard.press(Key.left)
            time.sleep(1)
            keyboard.release(Key.left)
    elif msg=="ZI":
        keyboard.press(Key.page_up)
        time.sleep(1)
        keyboard.release(Key.page_up)
    elif msg=="ZO":
        keyboard.press(Key.page_down)
        time.sleep(1)
        keyboard.release(Key.page_down)
    elif msg=="B*":
        with keyboard.pressed(Key.shift):
            keyboard.press(Key.left)
            time.sleep(1)
            keyboard.release(Key.left)
    elif msg=="B#":
        with keyboard.pressed(Key.shift):
            keyboard.press(Key.right)
            time.sleep(1)
            keyboard.release(Key.right)
    elif msg=="BA":
        with keyboard.pressed(Key.shift):
            keyboard.press(Key.up)
            time.sleep(1)
            keyboard.release(Key.up)
    elif msg=="BB":
        with keyboard.pressed(Key.shift):
            keyboard.press(Key.down)
            time.sleep(1)
            keyboard.release(Key.down)
    elif msg=="BC":
        keyboard.press('n')
        time.sleep(1)
        keyboard.release('n')
    elif msg=="BD":
        keyboard.press('u')
        time.sleep(1)
        keyboard.release('u')
    elif msg=="B5":
        keyboard.press('r')
        time.sleep(1)
        keyboard.release('r')
    elif msg=="ST" or msg=="B0":
        keyboard.press(Key.space)
        time.sleep(1)
        keyboard.release(Key.space)
