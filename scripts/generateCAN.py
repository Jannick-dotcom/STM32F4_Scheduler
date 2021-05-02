infile = open("scripts/Masterlist.csv") #the excel exported as csv with the Information
outfileDefs = open("lib/CAN/StallardOScanIDs.h", "w") #the output for IDs
outfileStructs = open("lib/CAN/StallardOScanStructs.hpp", "w") #the output for structs
outfileStructs.write('#include "stdint.h"\n') #include the integer types to the struct file

infileText = infile.read(-1) #read all stuff from the csv
infileArray = infileText.split("\n") #split the text into an array containing the lines
prevName = "" #variable for saving the previous Message name

for x in infileArray: #Go through every line
    if(x > ""): #if there is something in the line
        lineArray = x.split(",") #split the line into columns
        id = str(lineArray[9])  #get the id of the message
        msgname = str(lineArray[10]) #get the name of the message
        signame = str(lineArray[12]) #get the name of the signal in the message
        if(msgname > "" and id > "" and id.startswith("0x")): #if valid message with valid id?
            if(prevName != msgname): #if the name of the previous message is different than this name
                outfileDefs.write("#define " + msgname + " " + id + "\n") #write a new define for the id

                if(prevName != ""): #if this is not the first message name?
                    outfileStructs.write("};\n\nstruct STOS_CAN_DAT_" + msgname + "{\n") #write struct after the struct before
                else:   #otherwise
                    outfileStructs.write("struct STOS_CAN_DAT_" + msgname + "{\n") #write the first struct
                
                prevName = msgname #set new previous name

            outfileStructs.write("\tuint8_t " + signame + ";\n") #write a signal

outfileStructs.write("};") #write the closing stuff

infile.close() #close the files
outfileDefs.close()
outfileStructs.close()