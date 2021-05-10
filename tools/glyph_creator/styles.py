_FONT = ('Courier, 16')
_PRIMARY_BG = 'white'
_SECONDARY_BG = '#4EFF1E'
_PRIMARY_FG = 'black'
_SECONDARY_FG = '#4EFF1E'


STYLE_FRAME = {
    'bg': _PRIMARY_BG,
    'relief': 'ridge',
    'bd': 1
}

STYLE_LABEL = {
    'bg': _PRIMARY_BG,
    'fg': _PRIMARY_FG,
    'font': _FONT
}

STYLE_BUTTON = {
    'bg': 'black',
    'fg': _SECONDARY_FG,
    'font': _FONT,
    'padx': 5,
    'pady': 5,
    'activeforeground': _PRIMARY_FG,
    'activebackground': _SECONDARY_BG
}