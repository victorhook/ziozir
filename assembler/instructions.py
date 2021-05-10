from line import Line


class Instruction:
    
    def __init__(self, line: Line):
        self.line = line
        self.tokens = line.tokens
        self.is_valid = True

    def __repr__(self):
        return f' '.join(str(tok) for tok in self.tokens)


class InvalidInstruction(Instruction):

    def __init__(self, *args):
        self.is_valid = False


class ValidInstruction(Instruction):

    def __init__(self, line: Line):
        super().__init__(line)


class InstructionFactory:

    @staticmethod
    def build_instruction(line: Line) -> Instruction:
        return ValidInstruction(line)
