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
#define STATUS_REG 7
#define STATUS_REG_Z_FLAG 0

/* --- Primary memory --- */
#define RAM_SIZE 256
typedef unsigned char word;
typedef uint16_t address;
typedef unsigned char reg;

void writeRam(address addr, word value);
word readRam(address addr);
word readReg(reg reg);
void writeReg(reg reg, word value);
StatusReg getStatusReg();
void updateStatusReg();
void updateZFlag(word result);


/* --- Secondary memory --- */
#define MEMORY_SIZE 1024
#define MEMORY_FILE_PATH "//home/victor/coding/projects/cpu/src/memory"
typedef uint16_t memoryAddress;

word readMemory(memoryAddress addr);
int writeMemory(memoryAddress addr, word value);


/* --- Instructions --- */
void add(word op1, word op2, address to);
void sub(word op1, word op2, address to);
void mul(word op1, word op2, address to);
void jump(address addr);
void jumpEq(address addr);
void jumpNeq(address addr);
void jumpGT(address addr);
void jumpGTE(address addr);
void jumpLT(address addr);
void jumpLTE(address addr);

/* --- IO --- */
void cpuPutc(char c);


void init_cpu();



#endif