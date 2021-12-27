import os
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

def before_upload(source, target, env):
    
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
    cmd = 'program {$PROG_PATH} 0x8008000; shutdown;'
    flags[c_idx+1] = cmd
    env['UPLOADERFLAGS'] = flags

    print(f'INFO: uploader command updated {cmd}')
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