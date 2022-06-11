import cantools

def readStructs():
    db1 = cantools.database.load_file('StallardOS_2021/CAN_System_Design_2021/Masterlist_ADCAN1.dbc')
    db2 = cantools.database.load_file('StallardOS_2021/CAN_System_Design_2021/MS4Sport_CAN2.dbc')

    messages = db1.messages+db2.messages

    stringout = ""
    structlist = ""
    canarray = ""
    idarray = ""

    stringout += "#include \"StallardOScanStructs.hpp\"\n\n"
    
    for msg in messages:
        msgname = msg.name.replace(' ', '_')
        structlist += f'struct STOS_CAN_PDU_{msgname} {msgname};\n'
        canarray += f'\t&{msgname},\n'
        idarray += f'\t{msgname}.ID,\n'
    
    stringout += structlist
    stringout += '\n'
    
    stringout += "struct StallardOSCanMessage *canarray[] = {\n"
    stringout += canarray
    stringout += "};\n\n"

    stringout += "uint16_t idarray[] = {\n"
    stringout += idarray
    stringout += "};\n\n"


    stringout += "uint16_t idToOffset(uint16_t id) {\n"
    stringout += "\tfor(uint16_t i = 0; i < sizeof(idarray) / sizeof(uint16_t); i++) {\n"
    stringout += "\t\tif(idarray[i] == id) return i;\n"
    stringout += "\t}\n"
    stringout += "\treturn -1;\n"
    stringout += "}\n\n"

    stringout += "void copyToBuffer(const StallardOSCanMessage *msg){\n"
    stringout += "\tif(msg == nullptr) return;\n"
    stringout += "\tuint16_t offset = idToOffset(msg->ID);\n"
    stringout += "\tif(offset < sizeof(canarray) / sizeof(StallardOSCanMessage*)) {\n"
    stringout += "\t\t*(canarray[offset]) = *(msg);\n"
    stringout += "\t}\n"
    stringout += "}\n"


    with open("StallardOS_2021/lib/CAN/StallardOScanArray.cpp", "w") as outfile:
        outfile.write(stringout)

if __name__ == '__main__':
    readStructs()