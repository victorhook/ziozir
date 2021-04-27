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
#define MEMORY_FILE_PATH "//home/victor/coding/projects/cpu/src/memory"
typedef uint16_t memoryAddress;

word readMemory(memoryAddress addr);
int writeMemory(memoryAddress addr, word value);


/* --- Instructions --- */
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_JUMP,
    OP_JUMPEQ,
    OP_JUMPNEQ,
    OP_JUMPGT,
    OP_JUMPGTE,
    OP_JUMPLT,
    OP_JUMPLTE
} Operation;

typedef reg Arg;

typedef struct {
    Operation op;
    Arg args[4];
} Instruction;

void opAdd(word op1, word op2, address to);
void opSub(word op1, word op2, address to);
void opMul(word op1, word op2, address to);
void opJump(address addr);
void opJumpZ(address addr);
void opJumpEq(address addr);
void opJumpNeq(address addr);
void opJumpGT(address addr);
void opJumpGTE(address addr);
void opJumpLT(address addr);
void opJumpLTE(address addr);

/* --- IO --- */
void cpuPutc(char c);
char cpuGetc();


/* -- Utils -- */
StatusReg getStatusReg();
void updateStatusReg();
void updateZFlag(word result);

typedef char token;



void init_cpu();



#endif