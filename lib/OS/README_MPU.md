## **Stallardo Operating System**
**StallardOS_MPU**

The memory protection unit (MPU) allows to restrict access to certain memory regions, for unprivileged tasks.

The MPU is configired in a *whitelist*-mode, which means access to memory must be explicitly granted.

_________________________________________________________________________________________

### Memory Layout

The STM32F4 uses the following memory loadout

```
+---------------------------------------+
|                           0xFFFF FFFF |
|   Vendor-specific memory       511 MB |   not used
|                           0xE010 0000 |
+---------------------------------------+
|                           0xE00F FFFF |
|   Private peripheral bus         1 MB |
|                           0xE000 0000 |
+---------------------------------------+
|                           0xDFFF FFFF |
|   External device                1 GB |   not used
|                           0xA000 0000 |
+---------------------------------------+
|                           0x9FFF FFFF |
|   External RAM                   1 GB |   not used
|                           0x6000 0000 |
+---------------------------------------+
|                           0x5FFF FFFF |
|   Peripheral                   0.5 GB |
|                           0x4000 0000 |
+---------------------------------------+
|                           0x3FFF FFFF |
|   SRAM                         0.5 GB |
|                           0x2000 0000 |
+---------------------------------------+
|                           0x1FFF FFFF |
|   Code                         0.5 GB |
|                           0x0000 0000 |
+---------------------------------------+
```
_________________________________________________________________________________________
### Configuration

The STM32 MPU is organized in up to 8 different regions. Each region can be configured with different access parameters (address, size, permissions, other stuff).

On overlapping regions, the highest region number determins the effective permissions.


**Global Values**

At startup in `StallardOS.cpp`, all static memory regions are configured.

* Flash: RO
* SRAM: RW for .data/.bss
* Peripheral: RW

The, the MPU is enabled


**Task Values**

At each context switch, the MPU is reconfigured to protect the new task stack
This is done in the `PendSV_Handler`.

The new stack area is marked as RW.

_________________________________________________________________________________________

### Alignment

STM32 MPUs can only protect specifically aligned memory region.
**Each region must be aligned to its size**

This means, a region of the size of 1024, must have a baseadress to a mutliple of 1024.
This puts many constaints on the memory layout for the used system


**.text**
The flash memory starts at an aligned base address. As the flash memory is protected as a single unit, no further alignment constarints need to be considered.

**.data/.bss**

The linker script is adjusted to guarantee correct alignment.
A post-build script then analyzes the resulting `.elf` file, to detect any misaligned regions.

**stack (heap)**

The allocator in `addFunction` uses `memalign` instead of `malloc` to guarantee aligned stack memory.


_________________________________________________________________________________________

### Region Size

The region size must be within the range of [32..4G]B.
It must be a power of 2 (-> only 1 bit in the number is set)

The `addFunction` method checks this constraints and aborts function allocation if not met.


