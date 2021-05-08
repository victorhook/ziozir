from glyph import GlyphCell


STRUCT_NAME = format('__GLYPH_{}')


def _wrap_as_headerfile(filename: str, data: str) -> str:
    """ Wraps the data content as a header fileformat, with ifdef-guards. """
    defguard = filename.split('.h')[0]
    defguard = defguard.upper()
    defguard += '_H'

    output = f'#ifndef {defguard}\n'
    output += f'#define {defguard}\n'
    output += data
    output += '#endif'

    return output


def generate_source_code(filename: str, glyphs: list) -> str:
    """ Generates source code from a list of glyphs. """
    output = ''
    for glyph in glyphs:
        # 8x8 Matrix
        output += '\n'
        output += STRUCT_NAME.format(glyph.name)
        output += ' = { \n'
        for row in range(8):
            output += '    '
            for col in range(8):
                value = glyph.data[row][col]
                output += f'{value}, '
            output += '\n'
        output += '};\n'

    return _wrap_as_headerfile(filename, output)
