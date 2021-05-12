## Instruction format

Each instruction is 32 bits wide.
The generic format for most instructions are as follows:

- opcode : 6 bits
- regdst : 4 bits
- op2/val: 22 bits

### Arithmetic

Arithmetic and binary instructions are formatted as follows:

|   0-5   | 6-9  | 10-13 | 14-31 |
|---------|------|-------|-------|
|  opcode | op1  |  op2  |  op3  |

where `op1` is the destination register, `op2` the source register, and `op3`
can either be a register or a value, with *imidiate* operations.
Example:

- `ADD R1 R2 R3` -> R1 = R2 + R3
- `ADDI R1 R2 3` -> R1 = R2 + 3

#### NOT
|   0-5   | 6-9  | 10-31 |
|---------|------|-------|
|  opcode | op1  |  op2  |

#### LD
|   0-5   | 6-9  | 10-31  |
|---------|------|--------|
|  opcode | dst  |  addr  |

where `op2` can be either a register or an address.
- `LD R1 Label` -> R1 = $[Label]
- `LDI R1 2` -> R1 = $[2]

#### ST
|   0-5   | 6-9  | 10-31 |
|---------|------|-------|
|  opcode | src  |  dst  |

- `ST R1 Label` -> $[Label] = R1
- `ST R1 2` -> $[2] = R1


#### MOV
|   0-5   | 6-9  |  10-31  |
|---------|------|---------|
|  opcode | src  |   dst   |

where *dst* can be either a register or a constant.

#### PUSH
|   0-5   | 6-9  | 10-31 |
|---------|------|-------|
|  opcode | reg  |  N/A  |

#### POP
|   0-5   | 6-9  | 10-31 |
|---------|------|-------|
|  opcode | reg  |  N/A  |

#### INC & DEC
|   0-5   | 6-9  | 10-31 |
|---------|------|-------|
|  opcode | reg  |  N/A  |

#### EI & DI
|   0-5   | 6-31  |
|---------|-------|
|  opcode |  N/A  |

#### SET & RES
|   0-5   | 6-9  | 10-13 |  14-31 |
|---------|------|-------|--------|
|  opcode | bit  |  reg  |   N/A  |

#### CALL
|   0-5   | 6-31   |
|---------|--------|
|  opcode |  Addr  |

#### RET
|   0-5   | 6-31  |
|---------|-------|
|  opcode |  N/A  |

#### RETI
