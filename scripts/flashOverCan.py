import os
import can
import time

#Set CAN0 speed to 1M bps
# os.system('sudo ip link set can0 up type can bitrate 500000')

# can0 = can.interface.Bus(channel = 'can0', bustype = 'socketcan')

# msg = can.Message(arbitration_id=0x222, data=[0x02,0x02], extended_id=False, dlc=2)
# can0.send(msg)
# os.system('sudo ifconfig can0 down')

# rcvMessage = can0.recv(30)
# print(rcvMessage)

os.system('sudo ip link set can0 up type can bitrate 125000')
time.sleep(2)
# os.system("canprog -n can0 stm32 erase -P 0")
os.system("canprog -n can0 -f hex stm32 write .pio/build/debug/firmware.hex")
time.sleep(0.5)

# while(rcvMessage != msg):
#     can0.send(msg)
#     rcvMessage = can0.recv(1)

os.system('sudo ifconfig can0 down')