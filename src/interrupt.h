#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "emulator.h"

enum Interrupt {
    INT_PUTC,
    INT_GETC,
};

/* Puts the content found in register REG_INT to stdout. */
void intPutc();

/* Reads a character from stdin and puts it in REG_INT.
   This interrupt blocks until a character has been read.
*/
void intGetc();


#endif /* INTERRUPT_H */
