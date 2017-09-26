#!/usr/local/bin/python

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from serial import Serial, SerialException
import math

# The Serial constructor will take a different first argument on
# Windows. The first argument on Windows will likely be of the form
# 'COMX' where 'X' is a number like 3,4,5 etc.
# Eg.cxn = Serial('COM5', baudrate=9600
#
# NOTE: You won't be able to program your Arduino or run the Serial
# Monitor while the Python script is running.
cxn = Serial('/dev/cu.usbmodem1411', baudrate=9600)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ver_pos = []
hor_pos = []
dist = []
readings = []
run = 1

def get_ver_pos(s):
    result = s[0:s.index(',')]                     
    return int(result)

def get_hor_pos(s):
    result = s[(s.index(',')+1): (s.rindex(','))]
    return int(result)

def get_dist(s):
    result = s[(s.rindex(',')+1):]
    return float(result)

while(True):
    try:
        cmd_id = int(input("Please enter a command ID (1 - start, 2 - do nothing: "))
        if int(cmd_id) > 2 or int(cmd_id) < 1:
            print("Values other than 1 or 2 are ignored.")
        else:
            cxn.write([int(cmd_id)])
            while cxn.inWaiting() < 1:
                pass
            for i in range(0, 900):
                reading = cxn.readline();
                print(reading)
                #reading = reading.decode();
                #print(reading)
                readings.append(reading)
            break
    except ValueError:
        print("You must enter an integer value between 1 and 2.")

for reading in readings:
    reading = reading.decode()
    reading = reading.replace("\r\n", "")
    ver = get_ver_pos(reading)
    hor = get_hor_pos(reading)
    distance = get_dist(reading)
    ver_pos.append(math.radians(ver))
    hor_pos.append(math.radians(hor))
    dist.append(distance)
x = []
y = []
z = []
for i in range(0, len(dist)-1):
    if (dist[i] >= 12 and dist[i] <= 36):
        x.append(dist[i]*math.cos(ver_pos[i])*math.cos(hor_pos[i]))
        y.append(dist[i]*math.cos(ver_pos[i])*math.sin(hor_pos[i]))
        z.append(dist[i]*math.sin(ver_pos[i]))
print(x)

plt.scatter(x, y, z)
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
