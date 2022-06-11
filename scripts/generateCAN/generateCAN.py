import math
import os
from webbrowser import UnixBrowser
import pandas as pd
import glob
import cantools

endl = "\n"
tab = "    "

def genConstructor(prevMSGName, bitcountInMsg):
        tempstr = ""
        tempstr += f"{tab}STOS_CAN_PDU_{prevMSGName}() {endl}{tab}{{{endl}{tab}{tab}ID = _id;{endl}"
        tempstr += tab + "}" + endl
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
    return bitcount

def main():
    db1 = cantools.database.load_file('StallardOS_2021/CAN_System_Design_2021/Masterlist_ADCAN1.dbc')
    db2 = cantools.database.load_file('StallardOS_2021/CAN_System_Design_2021/MS4Sport_CAN2.dbc')

    messages = db1.messages+db2.messages

    outfileDefs = open("StallardOS_2021/lib/CAN/StallardOScanIDs.h", "w") #the output for IDs
    outfileStructs = open("StallardOS_2021/lib/CAN/StallardOScanStructs.hpp", "w") #the output for structs

    outfileStructs.write(f"#ifndef StallardOScanStructs_hpp{endl}#define StallardOScanStructs_hpp{endl}")
    outfileStructs.write(f'#include "stdint.h"{endl}#include "StallardOScanTypes.hpp"{endl}#include <math.h>{endl}#include "StallardOScanIDs.h"{endl}{endl}') #include the integer types to the struct file

    for msg in messages: #Go through every message
        msgname = msg.name.replace(' ', '_')
        outfileDefs.write(f"#define STOS_CAN_ID_{msgname} 0x{msg.frame_id:X}{endl}") #write a new define for the id

        outfileStructs.write(f"struct STOS_CAN_PDU_{msgname} : public StallardOSCanMessage {endl}{{{endl}public:{endl}") #write the first struct
        outfileStructs.write(f"{tab}static constexpr uint16_t _id = STOS_CAN_ID_{msgname};{endl}")
        outfileStructs.write(f"{tab}const uint16_t _size = {msg.length};{endl}")

        build_str = f"{tab}void build(){endl}{tab}{{"
        unbuild_str = f"{tab}void unbuild(){endl}{tab}{{{endl}"

        if msg.signals:
            build_str += f'{endl}{tab}{tab}Val = 0;{endl}'

        for signal in msg.signals:
            signame = signal.name.replace(' ', '_')

            sign = 'u' if not signal.is_signed else ''
            dtype = f'{sign}int{roundBitcount(signal.length)}_t'

            init = signal.initial or 0
            bcnt = signal.length
            sbit = signal.start
            rCnt = f'0x{signal.multiplexer_ids[0]:X}' if signal.multiplexer_ids else 0 # int=0 will evaluate to False later on
            isMotorola = 1 if (signal.byte_order=='big_endian') else 0
            factor = signal.scale
            offset = signal.offset

            # declaration
            outfileStructs.write(f"{tab}CAN_Signal<{dtype}> {signame} = {{{init}, {bcnt}, {sbit}, {rCnt}, {isMotorola}, {factor}, {offset}}};  // {{init,bitcount,startbit,rowcount,isMotorola,factor,offset}}  [{signal.minimum or 0}|{signal.maximum or 0}]{endl}")
            # build
            if rCnt:
                build_str += f'{tab}{tab}if({signal.multiplexer_signal}.physValue=={rCnt}){{{endl}'
                build_str += f'{tab}{tab}{tab}Val |= {signame}.build();'
                build_str += f'{endl}{tab}{tab}}}{endl}'
            else:
                build_str += f'{tab}{tab}Val |= {signame}.build();{endl}'
            # unbuild
            if rCnt:
                unbuild_str += f'{tab}{tab}if({signal.multiplexer_signal}.physValue=={rCnt}){{{endl}'
                unbuild_str += f'{tab}{tab}{tab}{signame}.unbuild(Val);{endl}'
                unbuild_str += f'{tab}{tab}}}{endl}'
            else:
                unbuild_str += f'{tab}{tab}{signame}.unbuild(Val);{endl}'

        outfileStructs.write(genConstructor(msgname, msg.length))

        build_str += f'{endl}{tab}}}{endl}'
        unbuild_str += f'{tab}}}{endl}'

        outfileStructs.write(build_str)
        outfileStructs.write(unbuild_str)

        outfileStructs.write(f'}};{endl}')

    outfileStructs.write('#endif  // StallardOScanStructs_hpp')

    outfileDefs.close()
    outfileStructs.close()

if __name__ == '__main__':
    main()