from line import Line

from constants import OpCode, OPCODES
import instruction_classes as instructions


OPCODE_CLASS_TABLE = {
    # Three operands
    "ADD": instructions.InstrThreeOperands,
    "ADDI": instructions.InstrThreeOperands,
    "SUB": instructions.InstrThreeOperands,
    "SUBI": instructions.InstrThreeOperands,
    "MUL": instructions.InstrThreeOperands,
    "MULI": instructions.InstrThreeOperands,
    "AND": instructions.InstrThreeOperands,
    "ANDI": instructions.InstrThreeOperands,
    "OR": instructions.InstrThreeOperands,
    "ORI": instructions.InstrThreeOperands,
    "XOR":  instructions.InstrThreeOperands,
    "XORI":  instructions.InstrThreeOperands,
    # Two operands
    "NOT": instructions.InstrTwoOperands,
    "NOTI": instructions.InstrTwoOperands,
    "LD": instructions.InstrTwoOperands,
    "LDI": instructions.InstrTwoOperands,
    "ST": instructions.InstrTwoOperands,
    "STI": instructions.InstrTwoOperands,
    "CMP": instructions.InstrTwoOperands,
    "CMPI": instructions.InstrTwoOperands,
    "MOV": instructions.InstrTwoOperands,
    "MOVI": instructions.InstrTwoOperands,
    # One operand
    "PUSH": instructions.InstrTwoOperands,
    "POP": instructions.InstrTwoOperands,
    "INC": instructions.InstrTwoOperands,
    "DEC": instructions.InstrTwoOperands,
    "CALL,": instructions.InstrOneOperand,
    "JMP": instructions.InstrOneOperand,
    "JMPZ": instructions.InstrOneOperand,
    "JMPEQ": instructions.InstrOneOperand,
    "JMPNEQ": instructions.InstrOneOperand,
    "JMPGT": instructions.InstrOneOperand,
    "JMPGTE": instructions.InstrOneOperand,
    "JMPLT": instructions.InstrOneOperand,
    "JMPLTE": instructions.InstrOneOperand,
    # No operands
    "EI": instructions.InstrNoOperands,
    "DI": instructions.InstrNoOperands,
    "NOP": instructions.InstrNoOperands,
    "HALT": instructions.InstrNoOperands,
    "RET,": instructions.InstrNoOperands,
    # Two opreand registers
    "SET": instructions.InstrTwoOperandRegs,
    "RES": instructions.InstrTwoOperandRegs,
    # TODO
    "RETI,": 32,
}


class InvalidInstruction:

    def __init__(self, msg, expected):
        self.is_valid = False
        self.msg = msg
        self.expected = expected


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
    def _get_instruction(opcode: int,
                         operands: list) -> instructions.Instruction:

        pass

    @classmethod
    def build_instruction(cls, line: Line) -> instructions.Instruction:
        tokens = line.tokens

        # Get the opcode and ensure its known.
        opcode = cls._get_opcode(tokens[0])
        if opcode == OpCode.UNKNOWN:
            return InvalidInstruction('Unknown operation.')
        elif opcode not in OPCODES:
            return InvalidInstruction(f'Invalid operation {opcode}.')

        operands = line.tokens[1:] if len(line.tokens) > 1 else None
        instr = cls._get_instruction(opcode, operands)

        # Validate the instruction, to ensure operands are OK.
        instr.validate()

        # Parse the arguments for the instruction.
        if not instr.is_valid:
            return InvalidInstruction(f'Invalid arguments for {opcode}: '
                                      f'{args}, expected: {instr.expected()}')

        return instr
