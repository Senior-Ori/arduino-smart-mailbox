import serial
from tkinter import *
import tkinter as tk
import time

# import json
ser = serial.Serial('COM5', baudrate=57600, timeout=.01)
time.sleep(1)

DataDict = {"command": "", "leds": [-1, -1, -1, -1]}


# DataDict = {"command": "", "leds": [-1, -1, -1, -1]}
# DataDict["command"]="triggerLed"
# print(f"{DataDict}\r\n".encode())

def writeJsonHandler(name, values):
    DataDict[name] = values
    # if name=="triggerLed": DataDict["leds"] = [-1,-1,-1,-1]
    # {"command":"triggerLed","leds":[-1,-1,-1,-1]}
    ser.write(f"{DataDict}\r\n".encode())
    DataDict["command"] = ""
    return


def turnOnLED():
    if DataDict["leds"] == [1, 0, 1, 0]:
        return
    writeJsonHandler("leds", [1, 0, 1, 0])
    while True:
        #     print(f"Loading... number of checks for serial input:~=[{i}]")
        if ser.in_waiting:
            text1 = ser.readline().decode('utf')
            break
    my_var.set(str(text1))


def turnOffLED():
    if DataDict["leds"] == [0, 0, 0, 0]:
        return print(
            "Leds are already ON, therefore no matter how much you will hammer this button it will not do anything")
    writeJsonHandler("leds", [0, 0, 0, 0])

    while True:
        #     print(f"Loading... number of checks for serial input:~=[{i}]")
        if ser.in_waiting:
            text1 = ser.readline().decode('utf')
            break
    my_var.set(str(text1))


def turnOnOffLED():
    DataDict["leds"] = [-1, -1, -1, -1]
    writeJsonHandler("command", "triggerLed")
    while True:
        #     print(f"Loading... number of checks for serial input:~=[{i}]")
        if ser.in_waiting:
            text1 = ser.readline().decode('utf')
            break
    my_var.set(str(text1))


# creating TK-inter window
root = Tk()
root.title('Blink GUI')
root.geometry("350x350")
root.configure(bg="#141414")
text1 = "initial value"
my_var = tk.StringVar()
my_var.set("First click")

tk.Button(root, name="btn_On", text="on", width=10, command=turnOnLED).grid(row=0, column=0)
tk.Button(root, name="btn_Off",text="off", width=10, command=turnOffLED).grid(row=0, column=1)
tk.Button(root, name="btn_Trig",text="Trigger", width=10, command=turnOnOffLED).grid(row=0, column=2)
tk.Label(root,name="prompt_label", textvariable=my_var, width=30, fg="red").grid(row=1, column=0, columnspan=3,rowspan=2)

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
