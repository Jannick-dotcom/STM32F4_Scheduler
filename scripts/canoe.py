import os
import can
import time
import atexit

#Set CAN0 speed to 1M bps
os.system('sudo ip link set can0 up type can bitrate 500000')

can0 = can.interface.Bus(channel = 'can0', bustype = 'socketcan')

def candown():
    os.system('sudo ifconfig can0 down')

atexit.register(candown)

msgarr = []

while(True):
    rcvMessage = can0.recv(10)
    if(rcvMessage != None):
        can0.send(rcvMessage)
        if(len(msgarr) == 0):
            msgarr.append(rcvMessage)
        else:
            for i in range(len(msgarr)):
                if(msgarr[i].arbitration_id == rcvMessage.arbitration_id):
                    msgarr[i] = rcvMessage
                    break
            else:
                msgarr.append(rcvMessage)
        
        os.system("clear")
        for i in msgarr:
            print(i)