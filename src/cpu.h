#ifndef CPU_H
#define CPU_H
#include <stdint.h>

#define LOG_ERROR(msg) printf("Error: %s", msg)
#define LOG_WARN(msg) printf("Warning: %s", msg)
#define LOG_INFO(msg) printf("Info: %s", msg)
#define LOG_DEBUG(msg) printf("Debug: %s", msg)


typedef struct {
    uint8_t Z;      // Z flag
    uint8_t OF;     // OverFlow flag
    uint8_t IF;     // Interrupt flag
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
#define TOTAL_REGISTERS 8

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
    OP_ADD,     // ADD R1 R2 R3  -> R1 = R2 + R3
    OP_ADDI,    // ADD R1 R2 2   -> R1 = R2 + 2
    OP_SUB,     // SUB R1 R2 R3  -> R1 = R2 - R3
    OP_SUBI,    // SUB R1 R2 2   -> R1 = R2 - 2
    OP_MUL,     // MUL R1 R2 R3  -> R1 = R2 + R3
    OP_MULI,    // MUL R1 R2 2   -> R1 = R2 * 2
    OP_AND,     // AND R1 R2 R3  -> R1 = R2 & R3
    OP_ANDI,    // AND R1 R2 2   -> R1 = R2 & 2
    OP_OR,      // OR R1 R2 R3   -> R1 = R2 || R3
    OP_ORI,     // OR R1 R2 2    -> R1 = R2 || 2
    OP_XOR,     // XOR R1 R2 R3  -> R1 = R2 ^ R3
    OP_XORI,    // XOR R1 R2 2   -> R1 = R2 ^ 2
    OP_NOT,     // NOT R1 R2     -> R1 = ~R2
    OP_NOTI,    // NOT R1 2      -> R1 = ~2

    // Memory -> Register
    OP_LD,      // LD R1 Label   -> R1 = $[Label]
    OP_LDI,     // LDI R1 2      -> R1 = $[2]

    // Register -> Memory
    OP_ST,      // ST R1 Label   -> $[Label] = R1
    OP_STI,     // ST R1 2       -> $[2] = R1

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
void opADD(address to, reg r1, reg r2);
void opADDI(address to, reg r, word op);
void opSUB(address to, reg r1, reg r2);
void opSUBI(address to, reg r, word op);
void opMUL(address to, reg r1, reg r2);
void opMULI(address to, reg r, word op);
void opAND(address to, reg r1, reg r2);
void opANDI(address to, reg r, word op);
void opNOT(address to, reg r);
void opNOTI(address to, word op);
void opOR(address to, reg r1, reg r2);
void opORI(address to, reg r, word op);
void opXOR(address to, reg r1, reg r2);
void opXORI(address to, reg r, word op);

void opLD(address to, reg r1, reg r2);
void opLDI(address to, reg r, word op);

void opPUSH(reg r);
void opPOP(reg r);
void opINC(reg r);
void opDEC(reg r);

/* Enable interrupts. */
void opEI();
/* Disable Interrupts. */
void opDI();
/* Set bit b, in reg r to 1 */
void opSET(uint8_t bit, reg r);
/* Set bit b, in reg r to 0 */
void opRES(uint8_t bit, reg r);

void opCALL();
void opRET();
void opRETI();

/* Branching */
void opJUMP(address addr);
void opJUMPZ(address addr);
void opJUMPEQ(address addr, word op1, word op2);
void opJUMPNEQ(address addr, word op1, word op2);
void opJUMPGT(address addr, word op1, word op2);
void opJUMPGTE(address addr, word op1, word op2);
void opJUMPLT(address addr, word op1, word op2);
void opJUMPLTE(address addr, word op1, word op2);

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