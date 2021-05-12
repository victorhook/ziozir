class Instruction:

    def __init__(self, operation: str, opcode: int, operands: list = None):
        self.operation = operation
        self.opcode = opcode
        self.operands = operands
        self.is_valid = True

    def __repr__(self):
        return self.operation + ': '+ ' '.join(str(op) for op in self.operands)

    def validate(self) -> bool:
        """ Validates the instruction and sets the is_valid attr thereafter.
            This methods expected a valid opcode and only checks that the
            operands match the operation.
        """
        pass

    def expected() -> str:
        pass


# ------------------------------------------------- #


class InstrThreeOperands(Instruction):
    """ op1-4, op2-4, op3-18 """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True


class InstrTwoOperands(Instruction):
    """
        not, ld, st, mov, cmp
        op1-4, op2-22
    """

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True


class InstrOneOperand(Instruction):
    """
        push, pop, inc, dev, call, jmp*
        op1-4
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True


class InstrTwoOperandRegs(Instruction):
    """
        set, res
        op1-4, op2-4
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True


class InstrNoOperands(Instruction):
    """
        ei, di, ret, nop, halt
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def validate(self) -> None:
        self.is_valid = True
