import serial
import time
import json
from tkinter import *
import tkinter as tk

# import json



root = Tk() # creating TK-inter window
root.title('SmartMail-[BOX]')
root.geometry("350x350")
root.configure(bg="#141414")
text1 = "initial value"
my_var = tk.StringVar()
mail0_var = tk.StringVar()
mail1_var = tk.StringVar()
mail2_var = tk.StringVar()
mail3_var = tk.StringVar()

my_var.set("First click")

ser = serial.Serial('COM5', baudrate=57600, timeout=.01)  # set to the overflow ceiling of arduino nano, I think..
time.sleep(1)

DataDict = {"command": "", "leds": [-1, -1, -1, -1]}
DataInput = {}
Flag = {"leds":False}
index = {"times": 1}
def getJson():
    DataInput = json.loads(f"{ser.readline().decode('utf')}")
    my_var.set(DataInput["msg"])
    if DataInput["ir"]!=[mail0_var,mail1_var,mail2_var,mail3_var]:
        for n in range(len(DataInput["ir"])):
            globals()[f'mail{n}_var'].set(DataInput["ir"][n])
            if DataInput["ir"][n]:
                globals()[f'mail{n}'].config(bg="green")
            else:
                globals()[f'mail{n}'].config(bg="grey")
    return

def clock():
    hour = time.strftime("%H")
    minute = time.strftime("%M")
    second = time.strftime("%S")
    if ser.in_waiting: getJson()


    label1.config(text=hour+":"+minute+":"+second)
    label1.after(10,clock)
def writeJsonHandler(name, values):
    DataDict[name] = values
    ser.write(f"{DataDict}\r\n".encode())  # write to arduino in a json structure format.
    DataDict["command"] = ""  # reset commands.

def turnOnLED():
    if DataDict["leds"] == [1, 0, 1, 0]: return
    writeJsonHandler("leds", [1, 0, 1, 0])
    Flag["leds"]=True

def turnOffLED():
    if DataDict["leds"] == [0, 0, 0, 0]: return
    writeJsonHandler("leds", [0, 0, 0, 0])
    Flag["leds"]=True

def turnOnOffLED():
    DataDict["leds"] = [-1, -1, -1, -1]
    writeJsonHandler("command", "triggerLed")
    Flag["leds"]=True



def update():
    index["times"]+=1
    label1.config(text=index["times"])
    label1.after(1,update)


#if
    # text1 = ser.readline().decode('utf')
    # break

tk.Button(root, name="btn_On", text="on", width=10, command=turnOnLED).grid(row=0, column=0)
tk.Button(root, name="btn_Off",text="off", width=10, command=turnOffLED).grid(row=0, column=1)
tk.Button(root, name="btn_Trig",text="Trigger", width=10, command=turnOnOffLED).grid(row=0, column=2)
label1 = tk.Label(root, name="btn_loop",text="1", width=10,fg="green",bg="black")
label1.grid(row=0, column=3)
mail0 = tk.Label(root, name="mail1",textvariable=mail0_var, width=10,fg="black",bg="black")
mail0.grid(row=3, column=0)
mail1 = tk.Label(root, name="mail2",textvariable=mail1_var, width=10,fg="black",bg="black")
mail1.grid(row=3, column=1)
mail2 = tk.Label(root, name="mail3",textvariable=mail2_var, width=10,fg="black",bg="black")
mail2.grid(row=3, column=2)
mail3 = tk.Label(root, name="mail4",textvariable=mail3_var, width=10,fg="black",bg="black")
mail3.grid(row=3, column=3)
tk.Label(root,name="prompt_label", textvariable=my_var, width=50, fg="red").grid(row=1, column=0, columnspan=4,rowspan=2)
#label1.after(1000,update)

clock()

root.mainloop()