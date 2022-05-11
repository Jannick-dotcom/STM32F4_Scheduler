import math
import os
import pandas as pd
import glob

endl = "\n"
tab = "\t"

read_file = pd.read_excel (glob.glob('StallardOS_2021/CAN_System_Design_2021/*.xlsx')[0])
read_file.to_csv (r'StallardOS_2021/CAN_System_Design_2021/Masterlist.csv', index = None, header=True)

infile = open("StallardOS_2021/CAN_System_Design_2021/Masterlist.csv", "r") #the excel exported as csv with the Information
outfileDefs = open("StallardOS_2021/lib/CAN/StallardOScanIDs.h", "w") #the output for IDs
outfileStructs = open("StallardOS_2021/lib/CAN/StallardOScanStructs.hpp", "w") #the output for structs

outfileStructs.write("#ifndef StallardOScanStructs_hpp\n#define StallardOScanStructs_hpp\n")
outfileStructs.write('#include "stdint.h"\n#include "StallardOScanTypes.hpp"\n#include <math.h>\n#include "StallardOScanIDs.h"\n') #include the integer types to the struct file

def genConstructor(prevMSGName, bitcountInMsg):
    tempstr = ""
    tempstr += "\tSTOS_CAN_PDU_" + prevMSGName + "() \n\t{\n\t\tID = _id;\n"
    tempstr += "\t\tuint8_t temp = " + bitcountInMsg + ";\n"
    tempstr += "\t\tif(temp % 8 != 0) temp = temp / 8 + 1;\n\t\telse temp = temp / 8;\n"
    tempstr += "\t\tif(temp > 8) temp = 8;\n"
    tempstr += "\t\t_size = dlc = temp;\n\t}\n"
    return tempstr

def roundBitcount(bitcountIn):
    if(bitcountIn <= 8):
        bitcount = 8
    elif(bitcountIn <= 16):
        bitcount = 16
    elif(bitcountIn <= 32):
        bitcount = 32
    elif(bitcountIn <= 64):
        bitcount = 64
    else:
        print("Wrong bit count in " + msgname +" !\n")
    return bitcount

infileText = infile.read(-1) #read all stuff from the csv
infileArray = infileText.split(endl) #split the text into an array containing the lines
prevMSGName = "" #variable for saving the previous Message name
prevSigName = "" #variable for saving the previous signal name
bitcountInMsg = "" #number of bits in the message
bitcountWholeMessage = 0 #number of resulting bits in message
strFunc = "" #unbuild function
signamesInMessage = "" #variable for printing in the build function

for line in infileArray: #Go through every line
    if(line > ""): #if there is something in the line
        lineArray = line.split(",") #split the line into columns
        id = str(lineArray[6])  #get the id of the message
        msgname = str(lineArray[7]) #get the name of the message
        rowcounter = str(lineArray[8]) #rowcounter from ms4
        if("= 0x" in rowcounter):
            rowcounter = rowcounter.split("= ")[1]
        else:
            rowcounter = "0"

        signame = str(lineArray[9]) #get the name of the signal in the message
        if(" " in signame):
            signame = signame.replace(" ", "_")
        initVal = str(lineArray[14]) #get initial Value of the Signal
        signed = str(lineArray[13])  #is the signal signed or unsigned?
        startingAtBit = str(lineArray[10]) #get the Bit at which the signal starts
        byteOrder = str(lineArray[12])
        factor = str(lineArray[15])
        offset = str(lineArray[16])
        byteOrderBool = 0

        if(msgname > "" and id > "" and id.startswith("0x")): #if valid message with valid id?
            bitcountIn = int(str(lineArray[11]))
            bitcount = roundBitcount(bitcountIn)

            if(prevMSGName != msgname): #New Message?
                outfileDefs.write("#define STOS_CAN_ID_" + msgname + " " + id + endl) #write a new define for the id
                if(bitcountWholeMessage > 64):
                    print("Something is wrong with size of PDU:" + prevMSGName)
                bitcountWholeMessage = 0

                if(prevMSGName != ""): #if this is not the first message name?
                    outfileStructs.write(genConstructor(prevMSGName, bitcountInMsg))
                    bitcountInMsg = ""

                    outfileStructs.write("\tvoid build() {\n\t\tVal = " + signamesInMessage + ";\n\t\tID = _id;\n\t}\n") #build function
                    outfileStructs.write(strFunc + "\t}\n") 
                    outfileStructs.write("\n};\n")

                strFunc = "\tvoid unbuild()\n\t{\n" #unbuild function

                outfileStructs.write("struct STOS_CAN_PDU_" + msgname + " : public StallardOSCanMessage \n{\npublic:\n") #write the first struct
                outfileStructs.write("\tstatic const uint16_t _id = STOS_CAN_ID_" + msgname + ";\n")
                outfileStructs.write("\tuint16_t _size;\n")

                prevMSGName = msgname #set new previous name
                signamesInMessage = ""

            if(prevSigName != signame): #if new signal

                bitcountWholeMessage += bitcountIn
                if(byteOrder == "Motorola" and bitcountIn % 8 == 0 and bitcountIn > 8):
                    startingAtBit = int(startingAtBit) - int(bitcountIn - 8)
                    byteOrderBool = 1

                if(int(startingAtBit) + bitcountIn > 64):
                    print("Something is wrong with bit positions of PDU:" + msgname)

                if(rowcounter != "0"):
                    strFunc += "\t\tif((Val & 0xFF) == " + rowcounter + ") //If the rowcounter points to this row \n\t"
                strFunc += "\t\t" + signame + ".unbuild(Val);\n"

                if(signamesInMessage != ""):
                    signamesInMessage = signamesInMessage + " | "
                signamesInMessage = signamesInMessage + signame + ".build()"

                if(bitcountInMsg != ""):
                    bitcountInMsg = bitcountInMsg + " + "
                bitcountInMsg = bitcountInMsg + str(signame) + ".countOfBits"

                outfileStructs.write("\tCAN_Signal<")
                if(signed == "Unsigned"):      #is unsigned?
                    outfileStructs.write("u")
                outfileStructs.write("int"+ str(bitcount) + "_t> ")
                outfileStructs.write(signame + " = {" + initVal + ", " + str(bitcountIn) + ", " + str(startingAtBit) + ", " + str(rowcounter) + ", " + str(byteOrderBool) + ", " + str(factor) + ", " + str(offset) + "};//init,bitcount,startbit,rowcount,isMotorola,factor,offset \n") #write a signal
                prevSigName = signame
            else:
                print("Something is wrong with Signal: " + signame + " of PDU:" + msgname + "!!! (Duplicate)")

outfileStructs.write(strFunc + "\t}\n")

outfileStructs.write("\tSTOS_CAN_PDU_" + prevMSGName + "() \n\t{\n\t\tID = _id;\n")
outfileStructs.write("\t\tuint8_t temp = " + bitcountInMsg + ";\n")
outfileStructs.write("\t\ttemp = (temp + 8 - (temp % 8)) / 8;\n")
outfileStructs.write("\t\tif(temp > 8) temp = 8;\n")
outfileStructs.write("\t\t_size = dlc = temp;\n\t}\n")

outfileStructs.write("\tvoid build() {\n\t\tVal = " + signamesInMessage + ";\n\t\tID = _id;\n\t}\n")
outfileStructs.write(";\n}; \n\n#endif")

infile.close() #close the files
outfileDefs.close()
outfileStructs.close()

os.remove('StallardOS_2021/CAN_System_Design_2021/Masterlist.csv')