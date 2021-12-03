
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

env.Append(
    LINKFLAGS=[
        "-mthumb", 
        "-mcpu=cortex-m4", 
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16", 
        "-fsingle-precision-constant",
        "-u_printf_float"
    ]
)

env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(" ".join([
        "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
        "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
    ]), "Building $BUILD_DIR/${PROGNAME}.hex")
)