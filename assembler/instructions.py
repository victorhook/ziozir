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
    MOV = 18
    PUSH = 19
    POP = 20
    INC = 21
    DEC = 22
    EI = 23
    DI = 24
    SET = 25
    RES = 26
    CALL = 27
    RET = 28
    RETI = 29
    JUMP = 30
    JUMPZ = 31
    JUMPEQ = 32
    JUMPNEQ = 33
    JUMPGT = 34
    JUMPGTE = 35
    JUMPLT = 36
    JUMPLTE = 37
    NOP = 38
    HALT = 39
    UNKNOWN = 40

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
    "MOV": 18,
    "PUSH": 19,
    "POP": 20,
    "INC": 21,
    "DEC": 22,
    "EI": 23,
    "DI": 24,
    "SET": 25,
    "RES": 26,
    "CALL,": 27,
    "RET,": 28,
    "RETI,": 29,
    "JUMP": 30,
    "JUMPZ": 31,
    "JUMPEQ": 32,
    "JUMPNEQ": 33,
    "JUMPGT": 34,
    "JUMPGTE": 35,
    "JUMPLT": 36,
    "JUMPLTE": 37,
    "NOP": 38,
    "HALT": 39,
    "UNKNOWN": 40
}


class Instruction:
    
    def __init__(self, line: Line):
        self.line = line
        self.tokens = line.tokens
        self.is_valid = True

    def __repr__(self):
        return f' '.join(str(tok) for tok in self.tokens)

    def set_args(self, args: list) -> None:
        pass

    def valid_args(self) -> bool:
        pass

    def expected() -> str:
        pass


class InvalidInstruction(Instruction):

    def __init__(self, msg, *args):
        self.is_valid = False
        self.msg = msg


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