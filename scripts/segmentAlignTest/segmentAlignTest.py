
import os
from elf_size_analyze import get_sections

Import("env", "projenv")


def after_build(source, target, env):
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

    invalid_segments = list(filter(lambda s: s.address%s.size != 0, ram_only))  # easy check for aligment, using a%b==0
    invalid_segments = list(filter(lambda s: s.name not in ignore_sections, invalid_segments))  # apply whitelist

    if invalid_segments:
        print('ERROR: misaligned segments detected')
        for segment in invalid_segments:
            print(f'{segment.name} ({segment.flags}): start address 0x{segment.address:x} not aligned to its size 0x{segment.size:x}')
        return -1

    print('IONF: alignment is OK')
    return 0

env.AddPostAction("buildprog", after_build)