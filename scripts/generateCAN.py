import math

infile = open("CAN_System_Design_2021/Masterlist.csv", "r") #the excel exported as csv with the Information
outfileDefs = open("lib/CAN/StallardOScanIDs.h", "w") #the output for IDs
outfileStructs = open("lib/CAN/StallardOScanStructs.hpp", "w") #the output for structs

outfileStructs.write("#ifndef StallardOScanStructs_hpp\n#define StallardOScanStructs_hpp\n")
outfileStructs.write('#include "stdint.h"\n#include "StallardOScanTypes.hpp"\n#include <math.h>\n\n') #include the integer types to the struct file

infileText = infile.read(-1) #read all stuff from the csv
infileArray = infileText.split("\n") #split the text into an array containing the lines
prevMSGName = "" #variable for saving the previous Message name
prevSigName = ""
bitcountInMsg = ""
strFunc = ""
signamesInMessage = "" #variable for printing in the build function

# messagesClass = "class STOS_CAN_Messages {\n"

for x in infileArray: #Go through every line
    if(x > ""): #if there is something in the line
        lineArray = x.split(",") #split the line into columns
        id = str(lineArray[6])  #get the id of the message
        msgname = str(lineArray[7]) #get the name of the message
        signame = str(lineArray[9]) #get the name of the signal in the message
        initVal = str(lineArray[14]) #get initial Value of the Signal
        signed = str(lineArray[13])  #is the signal signed or unsigned?
        startingAtBit = str(lineArray[10]) #get the Bit at which the signal starts
        canType = str(lineArray[5])

        if(msgname > "" and id > "" and id.startswith("0x")): #if valid message with valid id?
            bitcountIn = int(str(lineArray[11]))

            if(bitcountIn <= 8):
                bitcount = 8
            elif(bitcountIn <= 16):
                bitcount = 16
            elif(bitcountIn <= 32):
                bitcount = 32
            elif(bitcountIn <= 64):
                bitcount = 64
            else:
                print("Wrong bit count!\n")

            if(prevMSGName != msgname): #New Message?
                outfileDefs.write("#define STOS_CAN_ID_" + msgname + " " + id + "\n") #write a new define for the id
                
                if(prevMSGName != ""): #if this is not the first message name?
                    outfileStructs.write(strFunc + "\t}\n")
                    
                    outfileStructs.write("\tvoid build() {\n\t\t*Val = " + signamesInMessage + ";\n\t\tID = _id;\n\t}\n")
                    outfileStructs.write("\tuint16_t _size = dlc = " + bitcountInMsg + ";\n")
                    outfileStructs.write("};\n\n")
                    bitcountInMsg = ""

                strFunc = "\tvoid unbuild()\n\t{\n"

                outfileStructs.write("struct STOS_CAN_PDU_" + msgname + " : public StallardOSCanMessage \n{\npublic:\n") #write the first struct
                outfileStructs.write("\tSTOS_CAN_PDU_" + msgname + "() {\n\t\tID = _id;\n\t}\n")
                outfileStructs.write("\tstatic const uint16_t _id = " + id + ";\n")
                
                # messagesClass += "\tSTOS_CAN_PDU_" + msgname + " elem" + id + ";\n"

                prevMSGName = msgname #set new previous name
                signamesInMessage = ""

            if(prevSigName != signame): #if new signal
                strFunc += "\t\t" + signame + ".value = *Val & ~(uint64_t(pow(2, " + signame + ".startbit)-1)) & (uint64_t(pow(2, " + signame + ".countOfBits)-1) << " + signame + ".startbit);\n"
                if(signamesInMessage != ""):
                    signamesInMessage = signamesInMessage + " | "
                signamesInMessage = signamesInMessage + signame + ".build()"

                if(bitcountInMsg != ""):
                    bitcountInMsg = bitcountInMsg + " + "
                bitcountInMsg = bitcountInMsg + "sizeof(" + str(signame) + ".value)"

                outfileStructs.write("\tCAN_Signal<")
                if(signed == "Unsigned"):      #is unsigned?
                    outfileStructs.write("u")
                outfileStructs.write("int"+ str(bitcount) + "_t> ")
                outfileStructs.write(signame + " = {" + initVal + ", " + str(bitcountIn) + ", " + startingAtBit + "};//init,bitcount,startbit \n") #write a signal
                prevSigName = signame
            else:
                print("Someting is wrong with " + signame + "!!!\n")

# messagesClass += "\tvoid *pointerToCorrectOne;\n};\n"

outfileStructs.write(strFunc + "\t}\n")
outfileStructs.write("\tvoid build() {\n\t\t*Val = " + signamesInMessage + ";\n\t\tID = _id;\n\t}\n")
outfileStructs.write("\tuint16_t _size = " + bitcountInMsg + ";\n}; \n\n") #write the closing stuff

# outfileStructs.write(messagesClass)

outfileStructs.write("#endif")

infile.close() #close the files
outfileDefs.close()
outfileStructs.close()