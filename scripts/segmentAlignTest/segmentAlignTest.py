
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



def nextPow2(n: int):
    """ceil the given int to the next power of 2
       if n is a power of 2, n is returned

    Args:
        n (int): input number

    Returns:
        int: n ceiled to next pow2, n if n is already pow2
    """
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
    # for most configuration .data, .bss and .shared remain after this section, but could be more


    error = False

    for seg in ram_only:

        if seg.size < 32:
            error = True
            print(f'Size of {seg.name} is too small (min. 32 Byte)')
            continue

        
        is_pow2 = math.log2(seg.size).is_integer()
        next_pow2 = nextPow2(seg.size) # will be seg.size if already pow of 2

        # cannot use subsections on small regions
        if seg.size <= 256:
            if not is_pow2:
                error = True
                print(f'Size of {seg.name} ({seg.size}) is not aligned to pow2')
                # continue

            if seg.address%next_pow2 != 0:
                error = True
                print(f'Addr 0x{seg.address:x} of {seg.name} is not aligned to its size')
        else:
            # pow2 is guaranteed to be divisible by 8
            # as next_pow2 must be greater equals to 256
            sub_size = next_pow2//8
            misalign = seg.address%next_pow2
            offset_section = 0

            if misalign != 0 and misalign%sub_size != 0:
                error = True
                print(f'Addr 0x{seg.address:x} of {seg.name} not aligned. Subregion offset not possible')
                continue
            elif misalign != 0 and misalign%sub_size == 0:
                # try to determin an subregion offset
                # for the new start address
                offset_section = misalign//sub_size
                start_addr = seg.address - (offset_section*sub_size)

                if start_addr%next_pow2 != 0:
                    error = True
                    print(f'Addr 0x{seg.address:x} failed to offset-align to {next_pow2}({seg.size}) for {seg.name}')
                    continue

            
            # get the offset for the end address, based on a potenial start offset
            if offset_section > 0:
                end_section = offset_section + (seg.size/sub_size)-1
                if end_section > 7:
                    error = True
                    print(f'Size of {seg.name} ({seg.size}) doesn\'t fit into a subsection of{next_pow2}')
                    continue


    if error:
        return -1
    else:
        print('INFO: alignment is OK')
        return 0



env.AddPostAction("checkprogsize", after_build)