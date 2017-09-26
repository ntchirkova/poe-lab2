#!/usr/local/bin/python

from serial import Serial, SerialException

cxn = Serial('/dev/cu.usbmodem1411', baudrate=9600)

ver_pos = []
hor_pos = []
dist = []
run = 1

def get_ver_pos(s):
    result = s[0:s.index(',')]                     
    return int(result)

def get_hor_pos(s):
    result = s[(s.index(',')+1): (s.rindex(','))]
    return int(result)

def get_dist(s):
    result = s[(s.rindex(',')+1):]
    return int(result)

#Loop for when reading values from Arduino
while(True):
    #run = input("Press 1 to start, Press 2 to stop: ")
    #reading = cxn.readline()
    #run = 1
    #if (run == 1):
        #cxn.write([run])
        #print(run)
    if (run == 2):
        break
    while(run == 1):
        while cxn.inWaiting() < 1:
            pass
        reading = cxn.readline();
        print(reading)
        ver = get_ver_pos(reading)
        hor = get_hor_pos(reading)
        distance = get_dist(reading)
        ver_pos.append(ver)
        hor_pos.append(hor)
        dist.append(distance)
        if (ver == 0 and hor == 0 and dist == 0):
            run = 2
            break
        
print(hor_pos)


