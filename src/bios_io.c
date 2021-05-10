#include "bios_io.h"
#include "ascii_driver.h"

struct cursor {
    int row;
    int col;
} cursor;

void bios_clear_stdout()
{

}

void bios_write(const char c)
{
    display_write_char(cursor.row, cursor.col, c);
}

void bios_write_string(const char* s)
{

}

char bios_read()
{

}
