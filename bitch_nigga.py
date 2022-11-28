import serial
from tkinter import *
import tkinter as tk
import time

ser = serial.Serial('COM5', baudrate=9600, timeout=.001)
time.sleep(1)
# there is a problem with the data that has been received by arduino, (takes too much time to analyze input..)
def turnOnLED():
    ser.write(b'on')
    time.sleep(1)
    # i=0
    while True:
    #     i+=2
    #     print(f"Loding... number of checks for serial input:~=[{i}]")
        if ser.in_waiting:
            text1 = ser.readline().decode('utf')
            break
    my_var.set(str(text1))


def turnOffLED():
    ser.write(b'off')
    time.sleep(1)
    # i=0
    while True:
    #     i += 2
    #     print(f"Loding... number of checks for serial input:~=[{i}]")
        if ser.in_waiting:
            text1 = ser.readline().decode('utf')
            break
    my_var.set(str(text1))

# creating TK-inter window
root = Tk()
root.title('Blink GUI')
text1="initial value"
my_var = tk.StringVar()
my_var.set("First click")

btn_On = tk.Button(root,name="btn_On1", text="on", command=turnOnLED)
btn_On.grid(row=0,column=0)

label = tk.Label(root, textvariable=my_var, fg="red")
label.grid(row=1,column=0)
btn_Off = tk.Button(root, text="off", command=turnOffLED)
btn_Off.grid(row=0,column=1)

root.geometry("350x350")
root.mainloop()

## firstCode
# numPoints = 5
# dataList = [0] * numPoints
#
#
# def getValues():
#     ser.write(b'g')
#     arduinoData = ser.readline().decode('ascii')
#     return arduinoData
#
#
# while True:
#     userInput = input('Get data point?')
#     if userInput == 'y':
#         for i in range(0,len(dataList),1):
#             data = getValues()
#             dataList[i]=data
#         print(dataList)
