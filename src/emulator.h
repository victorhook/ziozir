#ifndef EMULATOR_H
#define EMULATOR_H
#include <stdint.h>
#include <stdio.h>

#define LOG_ERROR(msg) printf("Error: %s", msg)
#define LOG_WARN(msg) printf("Warning: %s", msg)
#define LOG_INFO(msg) printf("Info: %s", msg)
#define LOG_DEBUG(msg) printf("Debug: %s", msg)

/* -- Registers --*/
#define REG_0 0
#define REG_1 1
#define REG_2 2
#define REG_3 3
#define REG_4 4
#define REG_5 5
#define REG_6 6
#define SP 7
#define PC 8
#define STATUS_REG 9
#define TOTAL_REGISTERS 10

/* Status reg bits */
#define STATUS_BIT_Z  0b00000001
#define STATUS_BIT_OF 0b00000010
#define STATUS_BIT_IF 0b00000100

/* -- Memory -- */
#define RAM_SIZE 8192
#define BIOS_SIZE 512
#define FLASH_SIZE 512

#define MONITOR_WIDTH 144
#define MONITOR_HEIGHT 166

#define RAM_END RAM_SIZE-1

#define FLASH_MEMORY_FILE_PATH "/home/victor/coding/projects/ziozir/raw/memory"
#define BIOS_MEMORY_FILE_PATH "/home/victor/coding/projects/ziozir/raw/bios"

/* -- Constants -- */
#define DEFAULT_PC_INDEX 100
#define DEFAULT_SP_INDEX 200

/* -- Type definitinos -- */
typedef uint16_t word;
typedef uint16_t reg;
typedef uint16_t address;
typedef uint16_t memoryAddress;
typedef struct {
    uint8_t Z;      // Z flag
    uint8_t OF;     // OverFlow flag
    uint8_t IF;     // Interrupt flag
} StatusReg;


#endif /* EMULATOR_H */
