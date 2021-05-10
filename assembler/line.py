from dataclasses import dataclass

@dataclass
class Line:
    """ Each line of source code is represented as:
          Real line nbr
          Code (content) line nbr
          Content tokens.
    """
    real_line: int
    code_line: int
    tokens: list = None

    def __repr__(self):
        if self.tokens is None:
            return f'{self.real_line}: None'
        return f'{self.real_line}: {self.code_line} - {self.tokens}'
