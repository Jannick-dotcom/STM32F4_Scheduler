
from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

env.Append(
    LINKFLAGS=[
        "-mthumb", 
        "-mcpu=cortex-m4", 
        "-mfpu=fpv4-sp-d16", 
        "-mfloat-abi=hard"
    ]
)