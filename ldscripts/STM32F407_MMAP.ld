MEMORY
{
  SHARED  (xrw)   : ORIGIN = 0x2001FFC0, LENGTH = 64 /* adjust MPU config on modification */
  CCMRAM    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K-64
  FLASH  (rx)    : ORIGIN = 0x8000000, LENGTH = 512K
}


__approm_start__ = ORIGIN(FLASH);
__approm_size__ = LENGTH(FLASH);