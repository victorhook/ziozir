#include "cpu.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READ_SREG_BIT(bit) (ram[STATUS_REG] & (1 << bit))
#define WRITE_SREG_BIT(bit) (ram[STATUS_REG] &= ~(1 << bit))

static word ram[RAM_SIZE];
static StatusReg sReg;



/* --- Primary memory --- */
#define WRITE_RAM(value, addr) {ram[addr] = value;}
#define READ_RAM(addr) {ram[addr]}

void writeRam(address addr, word value)
{
    ram[addr] = value;
}
word readRam(address addr)
{
    return ram[addr];
}
word readReg(reg reg)
{
    return ram[REG_OFFSET + reg];
}
void writeReg(reg reg, word value)
{
    ram[REG_OFFSET + reg] = value;
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
    sReg.zFlag = READ_SREG_BIT(STATUS_REG_Z_FLAG);
}
void updateZFlag(word result)
{
    WRITE_SREG_BIT(result == 0 ? 1 : 0);
}
static inline void incPc()
{
    ram[PC]++;
}
static inline void setPc(address value)
{
    ram[PC] = value;
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
static inline void arithmetic(word result, address to)
{
    WRITE_RAM(to, result);
    updateZFlag(result);
    incPc();
}
/* Arithmetic */
void opADD(word op1, word op2, address to)
{
    arithmetic(op1 + op2, to);
}
void opADDI(reg r, word op, address to)
{
    REGI
    arithmetic(op1 + op2, to);
}
void opSUB(word op1, word op2, address to)
{
    arithmetic(op1 - op2, to);
}
void opSUBI(reg r, word op, address to)
{
    arithmetic(op1 - op2, to);
}
void opMUL(word op1, word op2, address to)
{
    arithmetic(op1 * op2, to);
}
void opMULI(reg r, word op, address to)
{
    arithmetic(op1 * op2, to);
}


/* Branching */
void opNOP()
{
    incPc();
}
void opJUMP(address addr)
{
    setPc(addr);
}
void opJUMPZ(address addr)
{
    if (sReg.zFlag == 0)
        setPc(addr);
    else
        incPc();
}
void opJUMPEQ(word op1, word op2, address addr)
{
    if (op1 == op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPNEQ(word op1, word op2, address addr)
{
    if (op1 != op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPGT(word op1, word op2, address addr)
{
    if (op1 > op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPGTE(word op1, word op2, address addr)
{
    if (op1 >= op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPLT(word op1, word op2, address addr)
{
    if (op1 < op2)
        setPc(addr);
    else
        incPc();
}
void opJUMPLTE(word op1, word op2, address addr)
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
                opAdd(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ADDI:
                opAddI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_SUB:
                opSub(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_SUBI:
                opSubI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_MUL:
                opMul(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_MULI:
                opMulI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_AND:
                opAnd(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ANDI:
                opAndI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_NOT:
                opNot(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_NOTI:
                opNotI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_OR:
                opOr(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_ORI:
                opOrI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_XOR:
                opXor(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_XORI:
                opXorI(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_LD:
                opLD(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_LDI:
                opLDI(instr.args[0], instr.args[1], instr.args[2]);
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
            case OP_EI :
                opEI();
                break;
            case OP_DI :
                opDI();
                break;
            case OP_SET:
                opSET(instr.args[0], instr.args[1]);
                break;
            case OP_RES:
                opRES(instr.args[0], instr.args[1]);
                break;
            case OP_CALL:
                opCALL();
                break;
            case OP_RET:
                opRET();
                break;
            case OP_RETI:
                opRETI();
                break;

            /* Branching */
            case OP_JUMP:
                opJump(instr.args[0]);
                break;
            case OP_JUMPZ:
                opJumpZ(instr.args[0]);
                break;
            case OP_JUMPEQ:
                opJumpEq(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPNEQ:
                opJumpNeq(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPGT:
                opJumpGT(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPGTE:
                opJumpGTE(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPLT:
                opJumpLT(instr.args[0], instr.args[1], instr.args[2]);
                break;
            case OP_JUMPLTE:
                opJumpLTE(instr.args[0], instr.args[1], instr.args[2]);
                break;

            /* MISC */
            case OP_NOP:
                opNop();
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