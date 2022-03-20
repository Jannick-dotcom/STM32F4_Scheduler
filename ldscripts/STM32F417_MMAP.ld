MEMORY
{
  SHARED  (xrw)   : ORIGIN = 0x2001FFC0, LENGTH = 64
  CCMRAM    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K-64
  BOOTFLASH (rx)    : ORIGIN = 0x8000000,   LENGTH = 32K
  FLASH  (rx)    : ORIGIN = 0x8008000, LENGTH = 1024K-32K
}

__bootrom_start__ = ORIGIN(BOOTFLASH);
__bootrom_size__ = LENGTH(BOOTFLASH);
__approm_start__ = ORIGIN(FLASH);
__approm_size__ = LENGTH(FLASH);