#include "memory.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


word ram[RAM_SIZE];
word bios[BIOS_SIZE];
word flash[FLASH_SIZE];

const char* flashMemoryPath = FLASH_MEMORY_FILE_PATH;
const char* biosMemoryPath = BIOS_MEMORY_FILE_PATH;


static word _readMemory(memoryAddress addr, const char* filepath)
{
    word buf;
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to read from memory!");
        return 0;
    }

    lseek(fd, addr, SEEK_CUR);
    read(fd, (void*) &buf, sizeof(buf));
    close(fd);
    return buf;
}

static int _writeMemory(memoryAddress addr, word value, const char* filepath)
{
    int fd = open(filepath, O_WRONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to write to memory!");
        return -1;
    }

    lseek(fd, addr, SEEK_CUR);
    write(fd, &value, sizeof(word));
    close(fd);
    return 1;
}

static int _readMemoryInto(void* buf, const size_t len, const char* filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to read from memory!");
        return 0;
    }

    int bytesRead = read(fd, buf, len);
    close(fd);
    return bytesRead;
}

static int _readMemoryIntoUntilEof(void* buf, const size_t maxLen, const char* filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        LOG_ERROR("Failed to read from memory!");
        return 0;
    }

    int bytesRead = 0;
    while (read(fd, (char*) buf, 1) != EOF && bytesRead < maxLen) {
        bytesRead++;
        buf++;
    }

    close(fd);
    return bytesRead;
}


/* --- RAM --- */
word readRam(address addr)
{
    return ram[addr];
}
void writeRam(address addr, word value)
{
    ram[addr] = value;
}


/* --- Flash --- */
word readFlash(memoryAddress addr)
{
    return _readMemory(addr, flashMemoryPath);
}
int writeFlash(memoryAddress addr, word value)
{
    return _writeMemory(addr, value, flashMemoryPath);
}
int loadFlash(word* buf, size_t offset)
{
    return _readMemoryIntoUntilEof(buf + offset, FLASH_SIZE, flashMemoryPath);
}

/* --- Bios --- */
word readBios(memoryAddress addr)
{
    return _readMemory(addr, biosMemoryPath);
}
int writeBios(memoryAddress addr, word value)
{
    return _writeMemory(addr, value, biosMemoryPath);
}
int loadBios(word* buf)
{
    return _readMemoryInto(buf, BIOS_SIZE * sizeof(word), biosMemoryPath);
}

