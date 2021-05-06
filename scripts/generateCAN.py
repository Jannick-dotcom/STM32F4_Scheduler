import math

infile = open("scripts/Masterlist.csv") #the excel exported as csv with the Information
outfileDefs = open("lib/CAN/StallardOScanIDs.h", "w") #the output for IDs
outfileStructs = open("lib/CAN/StallardOScanStructs.hpp", "w") #the output for structs

outfileStructs.write("#ifndef StallardOScanStructs_hpp\n#define StallardOScanStructs_hpp\n")
outfileStructs.write('#include "stdint.h"\n#include "StallardOScanTypes.hpp"\n') #include the integer types to the struct file

infileText = infile.read(-1) #read all stuff from the csv
infileArray = infileText.split("\n") #split the text into an array containing the lines
prevMSGName = "" #variable for saving the previous Message name
prevSigName = ""
bitcountInMsg = ""
adCAN = "struct AD_CAN_STRUCT{\n"
msCAN = "struct MS_CAN_STRUCT{\n"
signamesInMessage = "" #variable for printing in the build function

for x in infileArray: #Go through every line
    if(x > ""): #if there is something in the line
        lineArray = x.split(",") #split the line into columns
        id = str(lineArray[9])  #get the id of the message
        msgname = str(lineArray[10]) #get the name of the message
        signame = str(lineArray[12]) #get the name of the signal in the message
        initVal = str(lineArray[17]) #get initial Value of the Signal
        signed = str(lineArray[16])  #is the signal signed or unsigned?
        startingAtBit = str(lineArray[13]) #get the Bit at which the signal starts
        canType = str(lineArray[8])

        if(msgname > "" and id > "" and id.startswith("0x")): #if valid message with valid id?
            bitcountIn = int(str(lineArray[14]))

            if(bitcountIn <= 8):
                bitcount = 8
            elif(bitcountIn <= 16):
                bitcount = 16
            elif(bitcountIn <= 32):
                bitcount = 32
            elif(bitcountIn <= 64):
                bitcount = 64
            else:
                bitcount = 128
            

            if(prevMSGName != msgname): #New Message?
                outfileDefs.write("#define STOS_CAN_ID_" + msgname + " " + id + "\n") #write a new define for the id

                if(canType == "MS CAN"): #is on MS CAN?
                    msCAN = msCAN + "\tSTOS_CAN_PDU_" + msgname + " " + msgname + ";\n"
                elif(canType == "AD CAN"): #is on AD CAN?
                    adCAN = adCAN + "\tSTOS_CAN_PDU_" + msgname + " " + msgname + ";\n"

                if(prevMSGName != ""): #if this is not the first message name?
                    outfileStructs.write("\tvoid build() {\n\t\t*Val = " + signamesInMessage + ";\n\t}\n")
                    outfileStructs.write("\tuint16_t _size = dlc = " + bitcountInMsg + ";\n")
                    outfileStructs.write("};\n\n") #write struct after the struct before
                    bitcountInMsg = ""

                outfileStructs.write("struct STOS_CAN_PDU_" + msgname + " : public StallardOSCanMessage \n{\npublic:\n") #write the first struct
                outfileStructs.write("\tuint16_t _id = ID = " + id + ";\n")

                prevMSGName = msgname #set new previous name
                signamesInMessage = ""

            if(prevSigName != signame): #if new signal
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

outfileStructs.write("\tvoid build() {\n\t\t*Val = " + signamesInMessage + ";\n\t}\n")
outfileStructs.write("\tuint16_t _size = " + bitcountInMsg + ";\n}; \n\n") #write the closing stuff

# outfileStructs.write(adCAN + "};\n\n")
# outfileStructs.write(msCAN + "};\n")

outfileStructs.write("#endif")

infile.close() #close the files
outfileDefs.close()
outfileStructs.close()