
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

env.Append(
    LINKFLAGS=[
        "-mthumb", 
        "-mcpu=cortex-m4", 
        "-mfloat-abi=hard",
        "-mfpu=fpv4-sp-d16", 
        "-fsingle-precision-constant"
    ]
)

#add a define to check wether this is a debug build or release build (for breakpoints)
env.Append(
    BUILD_FLAGS=[
        "-DBuildType=" + str(env.GetBuildType())
    ]
)

env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(" ".join([
        "$OBJCOPY", "-O", "ihex", "-R", ".eeprom",
        "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
    ]), "Building $BUILD_DIR/${PROGNAME}.hex")
)