#ifndef MEMORY_H
#define MEMORY_H

#include "emulator.h"

extern word ram[RAM_SIZE];
extern word bios[BIOS_SIZE];
extern word flash[FLASH_SIZE];


/* --- RAM --- */
word readReg(reg reg);
void writeReg(reg reg, word value);


/* --- Flash --- */

/* Reads from flash memory at address addr. */
word readMemory(memoryAddress addr);

/* Writes value into flash memory at address addr. */
int writeMemory(memoryAddress addr, word value);


/* --- Bios --- */

/* Reads from flash memory at address addr. */
word readBios(memoryAddress addr);

/* Writes value into flash memory at address addr. */
int writeBios(memoryAddress addr, word value);


#endif /* MEMORY_H */
