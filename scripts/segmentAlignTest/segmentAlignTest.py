
import os
import re
import math
from elf_size_analyze import get_sections

Import("env", "projenv")

def get_defines(header_file):
    """extract defines of file into dict
       ignores all ifdef blocks
       // within strings will breake the parser
    """

    if not os.path.exists(header_file):
        print(f'WARN: header file not found {header_file}')
        return {}

    content = ''.join(open(header_file, 'r').readlines())

    # remove all block comments
    content = re.sub(r'\/\*(\*(?!\/)|[^*])*\*\/', '', content, flags=re.M)
    # single line comments, must only be matched after block comments
    content = re.sub(r'\/\/.*$', '', content, flags=re.M)

    # ifdefs are not supported, just remove all of them for now
    content = re.sub(r'#ifdef(.*\n)*?#endif', '', content, flags=re.M)

    def_list = list(filter(lambda l: l!='\n', content.split('#define ')))

    defs = {}

    for define in def_list:
        split = define.replace('\n', '').split(' ')
        key = split[0]

        if len(split) == 1:
            defs[key] = True
        else:
            val = split[1]

            try: val = int(val) 
            except ValueError: pass

            if val == 'true':
                val = True
            elif val == 'false':
                val = False

            defs[key] = val
        
    return defs


def nextPow2(n):
    p = 1
    if (n and not(n & (n - 1))):
        return n
 
    while (p < n):
        p <<= 1
         
    return p


def after_build(source, target, env):
    
    defs = get_defines('ECU_Defines/StallardOSconfig.h')
    if 'useMPU' not in defs or not defs['useMPU']:
        print('INFO: MPU config disabled, skipping alignment checks')
        return

    print('checking .data/.bss alignment...')
    
    build_env = env['PIOENV']
    ignore_sections = ['._user_heap_stack']  # ignore heap alignment
    elf_name = 'firmware.elf'

    if not build_env:
        print(f'ERROR: build environment "PIOENV" is "None"')
        return -1
    else:
        print(f'INFO: detected build env is "{build_env}"')

    build_path = f'.pio/build/{build_env}'
    if not os.path.exists(f'{build_path}/{elf_name}'):
        print(f'ERROR: {elf_name} not found in {build_path}')    
        return -1

    # -------------------------------------------------------
    # file is build and stored in expected location, 
    # continue with analyzing the file...

    sections = get_sections(f'{build_path}/{elf_name}')

    ram_only = list(filter(lambda s: s.address >= 0x20000000, sections))  # filter for RAM adress range
    ram_only = list(filter(lambda s: s.name not in ignore_sections, ram_only))  # filter out ignored elements

    invalid_segment_size = list(filter(lambda s: not math.log2(s.size).is_integer(), ram_only))  # invalid segment size overwrites align error
    invalid_segment_align = list(filter(lambda s: s.address%s.size != 0, ram_only))  # easy check for aligment, using a%b==0


    error = False

    if invalid_segment_size:
        error = True
        print('ERROR: invalid segment size detected')
        for segment in invalid_segment_size:
            print(f'{segment.name}: size 0x{segment.size:x} is not power of 2, try ".=ALIGN({nextPow2(segment.size)})" in {segment.name}')

    if invalid_segment_align:
        error = True
        print('ERROR: misaligned segments detected')
        for segment in invalid_segment_align:
            print(f'{segment.name}: start address 0x{segment.address:x} not aligned to its size 0x{segment.size:x}')


    for seg in sections:
        print(f'{seg.name} from {seg.address:x} to {(seg.address + seg.size):x}')

    if error:
        return -1
    else:
        print('INFO: alignment is OK')
        return 0



env.AddPostAction("checkprogsize", after_build)