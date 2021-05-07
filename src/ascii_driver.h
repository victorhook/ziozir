#ifndef ASCII_DRIVER_H
#define ASCII_DRIVER_H

#include "emulator.h"
#include "display_driver.h"
#include "glyphs.h"


#define ROWS MONITOR_WIDTH / GLYPH_SIZE
#define COLS MONITOR_HEIGHT / GLYPH_SIZE


/* Writes an ascii character c at row, col on the display. */
void display_write_char(const int row, const int col, const char c);

/* Writes a null-terminated string to the display, starting at row, col. */
void display_write_string(const int row, const int col, const char* string);



#endif /* ASCII_DRIVER_H */
