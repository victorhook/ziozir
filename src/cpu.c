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

void init_cpu()
{
    ram[SP] = DEFAULT_SP_INDEX;
    ram[PC] = DEFAULT_PC_INDEX;
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
}
void opAdd(word op1, word op2, address to)
{
    arithmetic(op1 + op2, to);
}
void opSub(word op1, word op2, address to)
{
    arithmetic(op1 - op2, to);
}
void opMul(word op1, word op2, address to)
{
    arithmetic(op1 * op2, to);
}
void opJump(address addr)
{
    setPc(addr);
}
void opJumpZ(address addr)
{
    if (sReg.zFlag == 0)
        setPc(addr);
    else
        incPc();
}

void opJumpEq(address addr)
{

}
void opJumpNeq(address addr)
{

}
void opJumpGT(address addr)
{

}
void opJumpGTE(address addr)
{

}
void opJumpLT(address addr)
{

}
void opJumpLTE(address addr)
{

}