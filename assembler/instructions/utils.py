import re


_RE_IS_REG = re.compile('[rR][0-8]')


def is_register(reg: str) -> bool:
    return _RE_IS_REG.match(reg)
