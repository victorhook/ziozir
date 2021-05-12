from line import Line


class OpCode:
    ADD = 0
    ADDI = 1
    SUB = 2
    SUBI = 3
    MUL = 4
    MULI = 5
    AND = 6
    ANDI = 7
    OR = 8
    ORI = 9
    XOR = 10
    XORI = 11
    NOT = 12
    NOTI = 13
    LD = 14
    LDI = 15
    ST = 16
    STI = 17
    CMP = 18
    CMPI = 19
    MOV = 20
    MOVI = 21
    PUSH = 22
    POP = 23
    INC = 24
    DEC = 25
    EI = 26
    DI = 27
    SET = 28
    RES = 29
    CALL, = 30
    RET, = 31
    RETI, = 32
    JMP = 33
    JMPZ = 34
    JMPEQ = 35
    JMPNEQ = 36
    JMPGT = 37
    JMPGTE = 38
    JMPLT = 39
    JMPLTE = 40
    NOP = 41
    HALT = 42
    UNKNOWN = 43


OPCODES = {
    "ADD": 0,
    "ADDI": 1,
    "SUB": 2,
    "SUBI": 3,
    "MUL": 4,
    "MULI": 5,
    "AND": 6,
    "ANDI": 7,
    "OR": 8,
    "ORI": 9,
    "XOR": 10,
    "XORI": 11,
    "NOT": 12,
    "NOTI": 13,
    "LD": 14,
    "LDI": 15,
    "ST": 16,
    "STI": 17,
    "CMP": 18,
    "CMPI": 19,
    "MOV": 20,
    "MOVI": 21,
    "PUSH": 22,
    "POP": 23,
    "INC": 24,
    "DEC": 25,
    "EI": 26,
    "DI": 27,
    "SET": 28,
    "RES": 29,
    "CALL,": 30,
    "RET,": 31,
    "RETI,": 32,
    "JMP": 33,
    "JMPZ": 34,
    "JMPEQ": 35,
    "JMPNEQ": 36,
    "JMPGT": 37,
    "JMPGTE": 38,
    "JMPLT": 39,
    "JMPLTE": 40,
    "NOP": 41,
    "HALT": 42,
    "UNKNOWN": 43,
}


class Instruction:

    def __init__(self, tokens: list):
        self.tokens = tokens
        self.is_valid = True

    def __repr__(self):
        return ' '.join(str(tok) for tok in self.tokens)

    def valid_args(self) -> bool:
        pass

    def expected() -> str:
        pass


class Arithmetic(Instruction):

    def __init__(self, tokens: list):
        super().__init__()

        





class InvalidInstruction(Instruction):

    def __init__(self, msg, *args):
        self.is_valid = False
        self.msg = msg
        self.tokens = []


class ValidInstruction(Instruction):

    def __init__(self, line: Line):
        super().__init__(line)


class InstructionFactory:

    @classmethod
    def _get_opcode(cls, token: str) -> OpCode:
        if token in OPCODES:
            return OPCODES[token]
        else:
            return OpCode.UNKNOWN

    @classmethod
    def _get_arguments(cls, tokens: list) -> list:
        if len(tokens) > 1:
            return tokens[1:]
        else:
            return None

    @classmethod
    def build_instruction(cls, line: Line) -> Instruction:
        tokens = line.tokens

        # Get the opcode and ensure its known.
        opcode = cls._get_opcode(tokens[0])
        if opcode is OpCode.UNKNOWN:
            return InvalidInstruction('Unknown operation.')

        # Create an instructions from the opcode.
        instr = Instruction(opcode)

        # Parse the arguments for the instruction.
        args = cls._get_arguments(tokens)
        if not instr.valid_args(args):
            return InvalidInstruction(f'Invalid arguments for {opcode}: '
                                      f'{args}, expected: {instr.expected()}')

        instr.set_args(args)

        return instr