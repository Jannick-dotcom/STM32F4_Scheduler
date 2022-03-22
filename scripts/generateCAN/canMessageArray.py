def readStructs():
    stringout = ""
    stringout += "#include \"StallardOScanStructs.hpp\"\n"
    listPDUtype = []
    listPDUname = []
    with open("StallardOS_2021/lib/CAN/StallardOScanStructs.hpp") as structs:
        for line in structs:
            if(line.__contains__("struct")):
                temp = str(line).split(" ")[1]
                listPDUtype.append(temp)
                listPDUname.append(str(temp).replace("STOS_CAN_PDU_", ""))

    for type,name in zip(listPDUtype,listPDUname):
        stringout += f"struct {type} {name};\n"
    
    stringout += "struct StallardOSCanMessage *canarray[] = {\n"
    for i in listPDUname:
        stringout += f"\t&{i},\n"
    stringout += "};\n"
    stringout = stringout.replace(",\n};", "\n};")

    stringout += "uint16_t idarray[] = {\n"
    for i in listPDUname:
        stringout += f"\t{i}.ID,\n"
    stringout += "};\n"
    stringout = stringout.replace(",\n};", "\n};")

    stringout += "uint16_t idToOffset(uint16_t id) {\n"
    stringout += "\tfor(uint16_t i = 0; i < sizeof(idarray) / sizeof(uint16_t); i++) {\n"
    stringout += "\t\tif(idarray[i] == id) return i;\n"
    stringout += "\t}\n"
    stringout += "\treturn -1;\n"
    stringout += "}\n"

    stringout += "void copyToBuffer(const StallardOSCanMessage *msg){\n"
    stringout += "\tif(msg == nullptr) return;\n"
    stringout += "\tuint16_t offset = idToOffset(msg->ID);\n"
    stringout += "\tif(offset < sizeof(canarray) / sizeof(StallardOSCanMessage*)) {\n"
    stringout += "\t\t*(canarray[offset]) = *(msg);\n"
    stringout += "\t}\n"
    stringout += "}\n"


    with open("StallardOS_2021/lib/CAN/StallardOScanArray.cpp", "w") as outfile:
        outfile.write(stringout)

readStructs()