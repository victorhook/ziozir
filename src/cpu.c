#include "cpu.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READ_SREG_BIT(bit) (ram[STATUS_REG] & (1 << bit))
#define WRITE_SREG_BIT(bit) (ram[STATUS_REG] &= ~(1 << bit))

reg registers[TOTAL_REGISTERS];     // Register file
address pc;                         // Program counter
StatusReg sReg;                     // Status register

word ram[RAM_SIZE];


reg sp;


/* --- Primary memory --- */
#define WRITE_RAM(value, addr) {ram[addr] = value;}
#define READ_RAM(addr) {ram[addr]}

inline void writeRam(address addr, word value)
{
    ram[addr] = value;
}
inline word readRam(address addr)
{
    return ram[addr];
}
inline word readReg(reg reg)
{
    return registers[reg];
}
inline void writeReg(reg reg, word value)
{
    registers[reg] = value;
}


/* --- Secondary memory --- */
const char* memoryPath = MEMORY_FILE_PATH;
word readMemory(memoryAddress addr)
{
    word buf;
    int fd = open(memoryPath, O_RDONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to read from memory!");
        return 0;
    }

    lseek(fd, addr, SEEK_CUR);
    read(fd, (void*) &buf, sizeof(buf));
    close(fd);
    return buf;
}
int writeMemory(memoryAddress addr, word value)
{
    int fd = open(memoryPath, O_WRONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to write to memory!");
        return -1;
    }

    lseek(fd, addr, SEEK_CUR);
    write(fd, &value, sizeof(word));
    close(fd);
    return 1;
}


/* --- Utils --- */
StatusReg getStatusReg()
{
    return sReg;
}
void updateStatusReg()
{
    sReg.Z = READ_SREG_BIT(STATUS_REG_Z_FLAG);
}
void updateZFlag(word result)
{
    WRITE_SREG_BIT(result == 0 ? 1 : 0);
}
void incPc()
{
    pc++;
}
void setPc(address value)
{
    pc = value;
}
void pushStack(word value)
{
    writeRam(sp, value);
    sp--;
}
void popStack(reg r)
{
    registers[r] = readRam(sp);
    sp++;
}
Instruction fetchInstruction()
{

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
static inline void arithmetic(address to, word result)
{
    WRITE_RAM(to, result);
    updateZFlag(result);
    incPc();
}
/* Arithmetic */
void opADD(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] + registers[r2]);
}
void opADDI(address to, reg r, word op)
{
    arithmetic(to, registers[r] + op);
}
void opSUB(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] - registers[r2]);
}
void opSUBI(address to, reg r, word op)
{
    arithmetic(to, registers[r] - op);
}
void opMUL(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] * registers[r2]);
}
void opMULI(address to, reg r, word op)
{
    arithmetic(to, registers[r] * op);
}
void opAND(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] & registers[r2]);
}
void opANDI(address to, reg r, word op)
{
    arithmetic(to, registers[r] & op);
}
void opNOT(address to, reg r)
{
    arithmetic(to, ~registers[r]);
}
void opNOTI(address to, word op)
{
    arithmetic(to, ~op);
}
void opOR(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] || registers[r2]);
}
void opORI(address to, reg r, word op)
{
    arithmetic(to, registers[r] || op);
}
void opXOR(address to, reg r1, reg r2)
{
    arithmetic(to, registers[r1] ^ registers[r2]);
}
void opXORI(address to, reg r, word op)
{
    arithmetic(to, registers[r] ^ op);
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
void opLD(reg r, address from)
{
    registers[r] = readRam(from);
}
void opLDI(reg r, word value)
{
    registers[r] = value;
}
void opST(reg r, address to)
{
    writeRam(to, registers[r]);
}

void opSTI(word value, address to)
{
    writeRam(to, value);
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
    pushStack(pc);
    setPc(to);
}
void opRET()
{
    popStack(REG_0);
    setPc(registers[REG_0]);
}
void opNOP()
{
    incPc();
}
void opRETI()
{

}


/* Branching */

void opJUMP(address addr)
{
    setPc(addr);
}
void opJUMPZ(address addr)
{
    if (sReg.Z == 0)
        setPc(addr);
    else
        incPc();
}
void opJUMPEQ(address addr, word op1, word op2)
{
    if (op1 == op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPNEQ(address addr, word op1, word op2)
{
    if (op1 != op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPGT(address addr, word op1, word op2)
{
    if (op1 > op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPGTE(address addr, word op1, word op2)
{
    if (op1 >= op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPLT(address addr, word op1, word op2)
{
    if (op1 < op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPLTE(address addr, word op1, word op2)
{
    if (op1 <= op2)
        setPc(addr);
    else
        incPc();
}

/* Misc */


/* -- Actions -- */

void init_cpu()
{
    ram[SP] = DEFAULT_SP_INDEX;
    ram[PC] = DEFAULT_PC_INDEX;
}

int run()
{
    char msg[200];
    int running = 1;
    int instrNbr = 0;
    Instruction instr = fetchInstruction();

    while (running) {
        switch (instr.op) {
            /* Arithmetic */
            case OP_ADD:
                opADD(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ADDI:
                opADDI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_SUB:
                opSUB(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_SUBI:
                opSUBI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_MUL:
                opMUL(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_MULI:
                opMULI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_AND:
                opAND(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ANDI:
                opANDI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_NOT:
                opNOT(instr.args[0], instr.args[1]);
                break;
            case OP_NOTI:
                opNOTI(instr.args[0], instr.args[1]);
                break;
            case OP_OR:
                opOR(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ORI:
                opORI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_XOR:
                opXOR(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_XORI:
                opXORI(instr.args[0], instr.args[1], instr.args[2]);
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
            case OP_JUMP:
                opJUMP(instr.args[0]);
                break;
            case OP_JUMPZ:
                opJUMPZ(instr.args[0]);
                break;
            case OP_JUMPEQ:
                opJUMPEQ(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPNEQ:
                opJUMPNEQ(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPGT:
                opJUMPGT(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPGTE:
                opJUMPGTE(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPLT:
                opJUMPLT(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPLTE:
                opJUMPLTE(instr.args[0], instr.args[1], instr.args[2]);
                break;

            /* MISC */
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