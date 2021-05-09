#ifndef MEMORY_H
#define MEMORY_H

#include "emulator.h"

extern word ram[RAM_SIZE];
extern word bios[BIOS_SIZE];
extern word flash[FLASH_SIZE];


/* --- RAM --- */
word readRam(address addr);
void writeRam(address addr, word value);


/* --- Flash --- */

/* Reads from flash memory at address addr. */
word readMemory(memoryAddress addr);

/* Writes value into flash memory at address addr. */
int writeMemory(memoryAddress addr, word value);

/* Reads from flash memory into buffer buf with an index offset of offset. */
int loadFlash(word* buf, size_t offset);

/* --- Bios --- */

/* Reads from bios memory at address addr. */
word readBios(memoryAddress addr);

/* Writes value into bios memory at address addr. */
int writeBios(memoryAddress addr, word value);

/* Reads from bios memory into buffer buf. */
int loadBios(word* buf);


#endif /* MEMORY_H */
