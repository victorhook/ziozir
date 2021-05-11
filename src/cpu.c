#include "cpu.h"
#include "memory.h"
#include <string.h>


reg registers[TOTAL_REGISTERS];     // Register file
StatusReg sReg;                     // Status register

#define READ_SREG_BIT(bit) (registers[SREG] & (1 << bit))
#define WRITE_SREG_BIT(bit) (registers[SREG] &= ~(1 << bit))


/* --- Utils --- */
StatusReg getStatusReg()
{
    return sReg;
}
void updateStatusReg()
{
    sReg.Z = READ_SREG_BIT(STATUS_BIT_Z);
    sReg.OF = READ_SREG_BIT(STATUS_BIT_OF);
    sReg.IF = READ_SREG_BIT(STATUS_BIT_IF);
}
void updateZFlag(word result)
{
    WRITE_SREG_BIT(result == 0 ? 1 : 0);
}
void incPc()
{
    registers[PC]++;
}
void setPc(address value)
{
    registers[PC] = value;
}
void pushStack(word value)
{
    writeRam(registers[PC], value);
    registers[SP]--;
}
void popStack(reg r)
{
    registers[r] = readRam(registers[SP]);
    registers[SP]++;
}
inline word readReg(reg reg)
{
    return registers[reg];
}
inline void writeReg(reg reg, word value)
{
    registers[reg] = value;
}
Instruction fetchInstruction(word instruction)
{
    Instruction instr;
    memset((void*) &instr, 0, sizeof(instr));
    instr.op = (instruction & OPCODE_MASK) >> (32 - (OPCODE_BITS));
    instr.args[0] = (instruction & REG_MASK) >> (32 - (REG_BITS));
    instr.args[1] = (instruction & (32 - OPCODE_BITS - REG_BITS));
    return instr;
}

/* --- IO --- */
void cpuPutc(char c)
{
    putchar(c);
}
char cpuGetc()
{
    return getchar();
}
 

/* --- Instructions --- */
static inline void arithmetic(reg r, word result)
{
    registers[r] = result;
    updateZFlag(result);
    incPc();
}
/* Arithmetic */
void opADD(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] + registers[r2]);
}
void opADDI(reg r, word constant)
{
    arithmetic(r, registers[r] + constant);
}
void opSUB(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] - registers[r2]);
}
void opSUBI(reg r, word constant)
{
    arithmetic(r, registers[r] - constant);
}
void opMUL(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] * registers[r2]);
}
void opMULI(reg r, word constant)
{
    arithmetic(r, registers[r] * constant);
}
void opAND(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] & registers[r2]);
}
void opANDI(reg r, word constant)
{
    arithmetic(r, registers[r] & constant);
}
void opNOT(reg r1, reg r2)
{
    arithmetic(r1, ~registers[r2]);
}
void opNOTI(reg r, word constant)
{
    arithmetic(r, ~constant);
}
void opOR(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] || registers[r2]);
}
void opORI(reg r, word constant)
{
    arithmetic(r, registers[r] || constant);
}
void opXOR(reg r1, reg r2)
{
    arithmetic(r1, registers[r1] ^ registers[r2]);
}
void opXORI(reg r, word constant)
{
    arithmetic(r, registers[r] ^ constant);
}
void opINC(reg r)
{
    registers[r]++;
}
void opDEC(reg r)
{
    registers[r]--;
}
void opSET(uint8_t bit, reg r)
{
    registers[r] |= 1 << bit;
}
void opRES(uint8_t bit, reg r)
{
    registers[r] &= ~(1 << bit);
}
void opLD(reg r, reg from)
{
    registers[r] = readRam(registers[from]);
}
void opLDI(reg r, word value)
{
    registers[r] = readRam(value);
}
void opST(reg r, address to)
{
    writeRam(to, registers[r]);
}

void opSTI(word value, address to)
{
    writeRam(to, value);
}

/* --- Misc --- */
void updateStatusRegister(word result)
{
    sReg.S = (result >> (BITS_PER_WORD - 1));

}


void opCMP(reg r1, reg r2)
{
    updateStatusRegister(registers[r1] - registers[r2]);
}
void opCMPI(reg r, word v)
{
    updateStatusRegister(registers[r] - v);
}
void opMOV(reg dst, reg src)
{
    registers[dst] = registers[src];
}
void opMOVI(reg r, word value)
{
    registers[r] = value;
}
void opPUSH(reg r)
{
    pushStack(registers[r]);
}
void opPOP(reg r)
{
    popStack(r);
}
void opEI()
{
    sReg.IF = 1;
}
void opDI()
{
    sReg.IF = 0;
}

void opCALL(address to)
{
    pushStack(registers[PC]);
    setPc(to);
}
void opRET()
{
    popStack(REG_RET);
    setPc(registers[REG_RET]);
}
void opNOP()
{
    incPc();
}
void opRETI()
{

}


/* Branching */

void opJMP(address addr)
{
    setPc(addr);
}
void opJMPZ(address addr)
{
    if (sReg.Z == 0)
        setPc(addr);
    else
        incPc();
}
void opJMPEQ(address addr)
{
    if (op1 == op2)
        setPc(addr);
    else
        incPc();
}
void opJMPNEQ(address addr)
{
    if (op1 != op2)
        setPc(addr);
    else
        incPc();
}
void opJMPGT(address addr)
{
    if (op1 > op2)
        setPc(addr);
    else
        incPc();
}
void opJMPGTE(address addr)
{
    if (op1 >= op2)
        setPc(addr);
    else
        incPc();
}
void opJMPLT(address addr)
{
    if (op1 < op2)
        setPc(addr);
    else
        incPc();
}
void opJMPLTE(address addr)
{
    if (op1 <= op2)
        setPc(addr);
    else
        incPc();
}

/* Misc */


/* -- Actions -- */

void cpu_init()
{
    registers[SP] = DEFAULT_SP_INDEX;
    registers[PC] = DEFAULT_PC_INDEX;
}

int cpu_run()
{
    word* instructions;
    char msg[200];
    int running = 1;
    int instrNbr = 0;
    Instruction instr = fetchInstruction(instructions[0]);

    while (running) {
        switch (instr.op) {
            /* Arithmetic */
            case OP_ADD:
                opADD(instr.args[0], instr.args[1]);
                break;
            case OP_ADDI:
                opADDI(instr.args[0], instr.args[1]);
                break;
            case OP_SUB:
                opSUB(instr.args[0], instr.args[1]);
                break;
            case OP_SUBI:
                opSUBI(instr.args[0], instr.args[1]);
                break;
            case OP_MUL:
                opMUL(instr.args[0], instr.args[1]);
                break;
            case OP_MULI:
                opMULI(instr.args[0], instr.args[1]);
                break;
            case OP_AND:
                opAND(instr.args[0], instr.args[1]);
                break;
            case OP_ANDI:
                opANDI(instr.args[0], instr.args[1]);
                break;
            case OP_NOT:
                opNOT(instr.args[0], instr.args[1]);
                break;
            case OP_NOTI:
                opNOTI(instr.args[0], instr.args[1]);
                break;
            case OP_OR:
                opOR(instr.args[0], instr.args[1]);
                break;
            case OP_ORI:
                opORI(instr.args[0], instr.args[1]);
                break;
            case OP_XOR:
                opXOR(instr.args[0], instr.args[1]);
                break;
            case OP_XORI:
                opXORI(instr.args[0], instr.args[1]);
                break;
            case OP_LD:
                opLD(instr.args[0], instr.args[1]);
                break;
            case OP_LDI:
                opLDI(instr.args[0], instr.args[1]);
                break;
            case OP_PUSH:
                opPUSH(instr.args[0]);
                break;
            case OP_POP:
                opPOP(instr.args[0]);
                break;
            case OP_INC:
                opINC(instr.args[0]);
                break;
            case OP_DEC:
                opDEC(instr.args[0]);
                break;

            /* Branching */
            case OP_JMP:
                opJMP(instr.args[0]);
                break;
            case OP_JMPZ:
                opJMPZ(instr.args[0]);
                break;
            case OP_JMPEQ:
                opJMPEQ(instr.args[0]);
                break;
            case OP_JMPNEQ:
                opJMPNEQ(instr.args[0]);
                break;
            case OP_JMPGT:
                opJMPGT(instr.args[0]);
                break;
            case OP_JMPGTE:
                opJMPGTE(instr.args[0]);
                break;
            case OP_JMPLT:
                opJMPLT(instr.args[0]);
                break;
            case OP_JMPLTE:
                opJMPLTE(instr.args[0]);
                break;

            /* MISC */
            case OP_CMP:
                opCMP(instr.args[0], instr.args[1]);
                break;
            case OP_CMPI:
                opCMPI(instr.args[0], instr.args[1]);
                break;
            case OP_MOV:
                opMOV(instr.args[0], instr.args[1]);
                break;
            case OP_MOVI:
                opMOVI(instr.args[0], instr.args[1]);
                break;
            case OP_EI:
                opEI();
                break;
            case OP_DI:
                opDI();
                break;
            case OP_SET:
                opSET(instr.args[0], instr.args[1]);
                break;
            case OP_RES:
                opRES(instr.args[0], instr.args[1]);
                break;
            case OP_CALL:
                opCALL(instr.args[0]);
                break;
            case OP_RET:
                opRET();
                break;
            case OP_RETI:
                opRETI();
                break;
            case OP_NOP:
                opNOP();
                break;
            case OP_HALT:
                sprintf(msg, "[%d] Halt reached!\n", instrNbr);
                LOG_INFO(msg);
                running = 0;
                break;
            case OP_UNKNOWN:
            default:
                sprintf(msg, "[%d] Unknown operation %d. Exiting!\n", instrNbr, instr.op);
                LOG_INFO(msg);
                running = 0;
                break;
        }
    }

    printf("CPU Stopped.\n");
}