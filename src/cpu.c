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
    ram[SP] = 0;
}

/* --- IO --- */
void cpuPutc(char c)
{
    putchar(c);
}

/* --- Instructions --- */


