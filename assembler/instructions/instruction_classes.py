import struct
from . import utils


class Instruction:

    def __init__(self, operation: str, opcode: int, operands: list = None):
        self.operation = operation
        self.opcode = opcode
        self.operands = operands
        self.is_valid = True

    def __repr__(self):
        return f'{self.operation}:  ' + \
               ' '.join(str(op) for op in self.operands)

    def validate(self) -> None:
        """ Validates the instruction and sets the is_valid attr thereafter.
            This methods expected a valid opcode and only checks that the
            operands match the operation.
        """
        pass

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        """ Returns the operand in bytes.
            This result is different depending on which instruction.
        """
        pass

    def as_bytes(self) -> bytes:
        data = (self.opcode << 26) | self.get_operand_bytes()

        return struct.pack('I', data)


# ------------------------------------------------- #


class InstrThreeOperands(Instruction):
    """ op1-4, op2-4, op3-18 """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        pass


class InstrTwoOperands(Instruction):
    """
        not, ld, st, mov, cmp
        op1-4, op2-22
    """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        valid = True
        if (len(self.operands) != 2
           or not utils.is_register(self.operands[0])):
            valid = False

        self.is_valid = valid

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        pass


class InstrOneOperand(Instruction):
    """
        push, pop, inc, dev, call, jmp*
        op1-4
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        pass


class InstrTwoOperandRegs(Instruction):
    """
        set, res
        op1-4, op2-4
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        pass


class InstrNoOperands(Instruction):
    """
        ei, di, ret, nop, halt
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True

    def expected(self) -> str:
        pass

    def get_operand_bytes(self) -> bytes:
        pass
