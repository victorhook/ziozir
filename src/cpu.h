#ifndef CPU_H
#define CPU_H
#include <stdint.h>

#define LOG_ERROR(msg) printf("Error: %s", msg)
#define LOG_WARN(msg) printf("Warning: %s", msg)
#define LOG_INFO(msg) printf("Info: %s", msg)
#define LOG_DEBUG(msg) printf("Debug: %s", msg)


typedef struct {
    uint8_t zFlag;
} StatusReg;

#define REG_OFFSET 0
#define REG_0 0
#define REG_1 1
#define REG_2 2
#define REG_3 3
#define REG_4 4
#define REG_5 5
#define SP 6
#define PC 7
#define STATUS_REG 8
#define STATUS_REG_Z_FLAG 0

/* --- Primary memory --- */
#define RAM_SIZE 256
#define DEFAULT_PC_INDEX 100
#define DEFAULT_SP_INDEX 200

typedef unsigned char word;
typedef uint16_t address;
typedef unsigned char reg;

void writeRam(address addr, word value);
word readRam(address addr);
word readReg(reg reg);
void writeReg(reg reg, word value);


/* --- Secondary memory --- */
#define MEMORY_SIZE 1024
#define MEMORY_FILE_PATH "/home/victor/coding/projects/cpu/src/memory"
typedef uint16_t memoryAddress;

word readMemory(memoryAddress addr);
int writeMemory(memoryAddress addr, word value);


/* --- Instructions --- */
typedef enum {
    OP_ADD,     // ADD R1 R2
    OP_ADDI,    // ADD R1 2
    OP_SUB,     // MUL R1 R2
    OP_SUBI,    // MUL R1 2
    OP_MUL,     // MUL R1 R2
    OP_MULI,    // MUL R1 2
    OP_AND,     // AND R1 R2
    OP_ANDI,    // AND R1 1
    OP_NOT,     // NOT R1 R2
    OP_NOTI,    // NOT R1 1
    OP_OR,      // OR R1 R2
    OP_ORI,     // OR R1 1
    OP_XOR,     // XOR R1 R2
    OP_XORI,    // XOR R1 1
    OP_OP_LD,   // LD R1 R2
    OP_OP_LDI,  // LD R1 2
    OP_PUSH,    // PUSH
    OP_POP,     // POP
    OP_INC,     // INC R1
    OP_DEC,     // DEC R1
    OP_EI,      // Enable Interrupts
    OP_DI,      // Disable Interrupts
    OP_SET,     // SET 1 R1  -  Set (b, reg)
    OP_RES,     // RET 1 R1  -  Reset (b, reg)
    OP_CALL,
    OP_RET,
    OP_RETI,
    OP_JUMP,    // JMP
    OP_JUMPZ,   // JMPZ
    OP_JUMPEQ,  // JMPEQ
    OP_JUMPNEQ, // JMPNEQ
    OP_JUMPGT,  // JPMGT
    OP_JUMPGTE, // JMPGTE
    OP_JUMPLT,  // JMPLT
    OP_JUMPLTE, // JMPLTE
    OP_NOP,     // NOP
    OP_HALT,    // HALT
    OP_UNKNOWN
} Operation;

typedef reg Arg;

typedef struct {
    Operation op;
    Arg args[4];
} Instruction;

void opNop();

/* Arithmetic */
void opAdd(reg r1, reg r2, address to);
void opAddI(reg r, word op, address to);
void opSub(reg r1, reg r2, address to);
void opSubI(reg r, word op, address to);
void opMul(reg r1, reg r2, address to);
void opMulI(reg r, word op, address to);
void opAnd(reg r1, reg r2, address to);
void opAndI(reg r, word op, address to);
void opNot(reg r1, reg r2, address to);
void opNotI(reg r, word op, address to);
void opOr(reg r1, reg r2, address to);
void opOrI(reg r, word op, address to);
void opXor(reg r1, reg r2, address to);
void opXorI(reg r, word op, address to);

void opLd(reg r1, reg r2, address to);
void opLdI(reg r, word op, address to);

void opPush(reg r);
void opPop(reg r);
void opInc(reg r);
void opDec(reg r);

/* Enable interrupts. */
void opEI();
/* Disable Interrupts. */
void opDI();
/* Set bit b, in reg r to 1 */
void opSet(uint8_t bit, reg r);
/* Set bit b, in reg r to 0 */
void opRes(uint8_t bit, reg r);

void opCall(reg r1, reg r2, address to);
void opRet(reg r, word op, address to);
void opReti(reg r, word op, address to);


void opJump(address addr);
void opJumpZ(address addr);
void opJumpEq(word op1, word op2, address addr);
void opJumpNeq(word op1, word op2, address addr);
void opJumpGT(word op1, word op2, address addr);
void opJumpGTE(word op1, word op2, address addr);
void opJumpLT(word op1, word op2, address addr);
void opJumpLTE(word op1, word op2, address addr);

Instruction fetchInstruction();

/* --- IO --- */
void cpuPutc(char c);
char cpuGetc();


/* -- Utils -- */
StatusReg getStatusReg();
void updateStatusReg();
void updateZFlag(word result);

typedef char token;



void init_cpu();
int run();



#endif