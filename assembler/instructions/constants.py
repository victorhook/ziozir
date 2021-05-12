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
    CALL = 30
    RET = 31
    RETI = 32
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
