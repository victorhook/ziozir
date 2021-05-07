#ifndef GLYPHS_H
#define GLYPHS_H

#define GLYPH_SIZE 8

typedef char glyph_t[64];

/* Returns the glyph representing the character c.
   If the character can't be recognized, a default glyph is returned. */
glyph_t* get_glyph(const char c);

/* Returns a 1 or 0 at the given row and col for the glyph. */
int get_glyph_value(const glyph_t* g, const int row, const int col);

#endif /* GLYPHS_H */
