#include "ascii_driver.h"

static void _write_char(int offsetX, int offsetY, const char c)
{
    glyph_t* g = get_glyph(c);
    colorStruct color = {1};

    for (int r = 0; r < GLYPH_SIZE; r++) {
        for (int c = 0; c < GLYPH_SIZE; c++) {
            display_put(
                offsetX + get_glyph_value(g, r, c),
                offsetX + get_glyph_value(g, r, c),
                color
                );
        }
    }
}

void display_write_char(const int row, const int col, const char c)
{
    int offsetX = col * GLYPH_SIZE;
    int offsetY = row * GLYPH_SIZE;
    _write_char(offsetX, offsetY, c);
    return GLYPH_SIZE;
}

void display_write_string(const int row, const int col, const char* string)
{
    int x = col;
    char* c = (char*) string;
    while ((*c++)) {
        display_write_char(row, x, *c);
        x += GLYPH_SIZE;
    }
}
