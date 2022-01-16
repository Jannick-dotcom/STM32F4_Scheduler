import os
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()


def elf_to_bin(build_path):

    print('INFO: creating new .bin from .elf')
    objcopy = f'arm-none-eabi-objcopy -O binary {build_path}\\firmware.elf {build_path}\\firmware.bin'
    ret = os.system(objcopy)

    return ret


def validate_bin(env):
    build_env = env['PIOENV']
    build_path = f'.pio/build/{build_env}'

    if not os.path.exists(f'{build_path}/firmware.bin'):
        print(f'INFO: {build_env}/firmware.bin not found')
        return elf_to_bin(build_path)

    bin_mod = os.path.getmtime(f'{build_path}/firmware.bin')
    elf_mod = os.path.getmtime(f'{build_path}/firmware.elf')

    # allow a differencee of up to 5s, when building on a slow machine
    build_diff = elf_mod-bin_mod
    if(build_diff > 5):
        print(f'INFO: .elf file is {int(build_diff)} seconds newer than .bin file, difference too large.')
        return elf_to_bin(build_path)
    elif(build_diff < -5):
        print(f'ERROR: .elf file is {int(-build_diff)}s older than .bin file, uncertain how to proceed. Delete either of them.')
        return -1

    # no action taken
    return 0



def before_upload(source, target, env):

    ret = validate_bin(env)
    if ret != 0:
        return ret

    env['PROGSUFFIX'] = '.bin'
    f_type = env['PROGSUFFIX']
    print(f'changed filetype to {f_type}')

    flags = env['UPLOADERFLAGS']
    indices = [i for i, x in enumerate(flags) if x == '-c']

    # find the parameter to overwrite
    # -c is appearing mutliple times, but only "-c program..." is the correct index
    c_idx = -1
    for idx in indices:
        if flags[idx+1].startswith('program'):
            c_idx = idx
            break

    if c_idx < 0:
        print('CRITICAL: failed to find openoncd flag "-c program..."')
        return -1


    # write the new upload command
    cmd = 'program {$PROG_PATH} 0x8008000; reset; shutdown;'
    flags[c_idx+1] = cmd
    env['UPLOADERFLAGS'] = flags

    print(f'INFO: uploader command updated to "{cmd}"')
    print('=========================================')

    return 0


env.AddPreAction("upload", before_upload)

# env.AddPostAction(
#     "$BUILD_DIR/${PROGNAME}.elf",
#     env.VerboseAction(" ".join([
#         "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
#         "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
#     ]), "Building $BUILD_DIR/${PROGNAME}.hex")
# )