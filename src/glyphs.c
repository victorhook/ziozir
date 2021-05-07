#include "glyphs.h"


glyph_t __GLYPH_A = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};


glyph_t* get_glyph(const char c)
{
    switch (c)
    {
    case 'a':
    case 'A':
        return &__GLYPH_A;
    default:
        break;
    }
}

int get_glyph_value(const glyph_t* g, const int row, const int col)
{
    return (int) *g[row * GLYPH_SIZE + col];
}