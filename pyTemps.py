'''

Simple script to read a line of data from a serial device

Can accept two optional arguments, the first being the serial device to use and the
second being the baudrate. These default to "/dev/ttyUSB0" and 9600 respectively.

Assumes that the data consists of 6 fields, the first of which being an integer
which starts at zero. This is used to skip any crap left over from a previous
run.

There is lots of scope for improvement but then, it's probably not worth it...

'''
import serial
import sys
import time

try:
    device = sys.argv[1]
except IndexError:
    device = "/dev/ttyUSB0"

try:
    speed = int(sys.argv[2])
except IndexError:
    speed = 115200

ser = serial.Serial(device, baudrate=speed, timeout=120)
# Reset the device
ser.DTR = False
time.sleep(0.1)
ser.DTR = True
time.sleep(0.2)

ser.flush()

def readln():
    while True:
        result = ser.readline()
        if result:
            break
    return result.strip()


fd = open("temperatures.dat", "w")

while True:
    data = readln()
    try:
        fields = data.split()
        time = int(fields[0])
    except ValueError:
        time = 1
    if time == 0 and len(fields) == 6:
        fd.write(data + "\n")
        print data
        break

while True:
    data = readln()
    fd.write(data + "\n")
    fd.flush()
    print data

