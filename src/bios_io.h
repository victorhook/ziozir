#ifndef BIOS_IO_H
#define BIOS_IO_H

/* Clears stdout */
void bios_clear_stdout();

/* Writes a character c to stdout. */
void bios_write(const char c);

/* Writes a null-terminated stirng to stdout. */
void bios_write_string(const char* s);

/* Reads a character from stdin and returns the value.
   This function blocks until a character has been read.
*/
char bios_read();


#endif /* BIOS_IO_H */
