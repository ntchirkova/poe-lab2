#!/usr/local/bin/python

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import LogNorm
from matplotlib.mlab import bivariate_normal
from serial import Serial, SerialException
import math

cxn = Serial('/dev/cu.usbmodem1411', baudrate=9600)

fig = plt.figure()

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
    ver_pos.append(ver)
    hor_pos.append(hor)
    dist.append(distance)
    
distMatrix = [[0 for _ in range(30)] for _ in range(30)]
d = 0
for h in range(0, 30):
    for v in range(0, 30):
        if d < len(dist):
            distMatrix[v][h] = dist[d]
            d = d+1
     
plt.pcolor(distMatrix)

plt.show()
