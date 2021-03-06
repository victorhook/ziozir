#ifndef CPU_H
#define CPU_H
#include "emulator.h"


word readReg(reg reg);
void writeReg(reg reg, word value);

#define BITS_PER_WORD 32
#define OPCODE_MASK 4227858432
#define OPCODE_BITS 6
#define REG_MASK 62914560
#define REG_BITS 4
#define ADDR_MASK 67108863


/* --- Instructions --- */
typedef enum {
    /* Arithmetic */
    OP_ADD,     // ADD R1 R1 R3     -> R1 = R1 + R3
    OP_ADDI,    // ADDI R1 R1 2     -> R1 = R1 + 2
    OP_SUB,     // SUB R1 R1 R3     -> R1 = R1 - R3
    OP_SUBI,    // SUBI R1 R1 2     -> R1 = R1 - 2
    OP_MUL,     // MUL R1 R1 R3     -> R1 = R1 + R3
    OP_MULI,    // MULI R1 R1 2     -> R1 = R1 * 2
    OP_AND,     // AND R1 R1 R3     -> R1 = R1 & R3
    OP_ANDI,    // ANDI R1 R1 2     -> R1 = R1 & 2
    OP_OR,      // OR R1 R1 R3      -> R1 = R1 || R3
    OP_ORI,     // ORI R1 R1 2      -> R1 = R1 || 2
    OP_XOR,     // XOR R1 R1 R3     -> R1 = R1 ^ R3
    OP_XORI,    // XORI R1 R1 2     -> R1 = R1 ^ 2
    OP_NOT,     // NOT R1 R2        -> R1 = ~R2
    OP_NOTI,    // NOTI R1 2        -> R1 = ~2
    /* Memory -> Register */
    OP_LD,      // LD R1 Label      -> R1 = $[Label]
    OP_LDI,     // LDI R1 2         -> R1 = $[2]
    /* Register -> Memory */
    OP_ST,      // ST R1 Label      -> $[Label] = R1
    OP_STI,     // ST R1 2          -> $[2] = R1
    /* Misc */
    OP_CMP,     // CMP R1 R2
    OP_CMPI,    // CMP R1 1
    OP_MOV,     // MOV R2 R3
    OP_MOVI,    // MOV R2 1
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
    /* Branching */
    OP_JMP,     // JMP
    OP_JMPZ,    // JMPZ
    OP_JMPEQ,   // JMPEQ
    OP_JMPNEQ,  // JMPNEQ
    OP_JMPGT,   // JPMGT
    OP_JMPGTE,  // JMPGTE
    OP_JMPLT,   // JMPLT
    OP_JMPLTE,  // JMPLTE
    OP_NOP,     // NOP
    OP_HALT,    // HALT
    OP_UNKNOWN
} Operation;

typedef reg Arg;

typedef struct {
    Operation op;
    Arg args[4];
} Instruction;


/* ------------- Instructions ------------------- */

/* -- Arithmetic -- */

/* ADD R1 R2 R3  -> R1 = R2 + R3 */
void opADD(reg r1, reg r2, reg r3);
/* ADDI R1 R2 2  -> R1 = R2 + 2 */
void opADDI(reg r1, reg r2, word constant);
/* SUB R1 R2 R3  -> R1 = R2 - R3 */
void opSUB(reg r1, reg r2, reg r3);
/* SUBI R1 R2 2  -> R1 = R2 - 2 */
void opSUBI(reg r1, reg r2, word constant);
/* MUL R1 R2 R3  -> R1 = R2 + R3 */
void opMUL(reg r1, reg r2, reg r3);
/* MULI R1 R2 2  -> R1 = R2 * 2 */
void opMULI(reg r1, reg r2, word constant);
/* AND R1 R2 R3  -> R1 = R2 & R3 */
void opAND(reg r1, reg r2, reg r3);
/* ANDI R1 R2 2  -> R1 = R2 & 2 */
void opANDI(reg r1, reg r2, word constant);
/* OR R1 R2 R3   -> R1 = R2 || R3 */
void opOR(reg r1, reg r2, reg r3);
/* ORI R1 R2 2   -> R1 = R2 || 2 */
void opORI(reg r1, reg r2, word constant);
/* XOR R1 R2 R3  -> R1 = R2 ^ R3 */
void opXOR(reg r1, reg r2, reg r3);
/* XORI R1 R2 2  -> R1 = R2 ^ 2 */
void opXORI(reg r1, reg r2, word constant);
/* NOT R1 R2     -> R1 = ~R2 */
void opNOT(reg r1, reg r2);
/* NOTI R1 2     -> R1 = ~2 */
void opNOTI(reg r, word op);
/* Increments register r by 1. */
void opINC(reg r);
/* Decrements register r by 1. */
void opDEC(reg r);


/* -- Memory -- */

/* Loads value at Ram[from] into register r. */
void opLD(reg r, reg from);
/* Loads value at Ram[from] into register r. */
void opLDI(reg r, word value);
/* Stores register r into Ram[to] */
void opST(reg r, address to);
/* Stores value into Ram[to] */
void opSTI(word value, address to);
/* Pushes register r onto the stack. Decrements stackpointer by 1. */
void opPUSH(reg r);
/* Pops the top of the stack into register r. Increments stackpointer by 1. */
void opPOP(reg r);

/* -- Misc -- */

/* Compares register r1 with r2 and updates the status register. */
void opCMP(reg r1, reg r2);
/* Compares register r1 the operand value and updates the status register. */
void opCMPI(reg r, word v);
/* Copies register src into register r. */
void opMOV(reg dst, reg src);
/* Copies value value into register r. */
void opMOVI(reg r, word value);
/* Enable interrupts. */
void opEI();
/* Disable Interrupts. */
void opDI();
/* Set bit b, in reg r to 1 */
void opSET(uint8_t bit, reg r);
/* Set bit b, in reg r to 0 */
void opRES(uint8_t bit, reg r);
/* Pushes the current value of Program Counter to the stack and sets it to address to. */
void opCALL(address to);
/* Pops the ToS into R0 and sets the Program Counter to that value. 
   Note: This means that R0 is reserved for this. 
*/
void opRET();
/* CPU do nothing for 1 clock cycle. Increment pc by 1. */
void opNop();

// TODO: this
void opRETI();


/* -- Branching -- */

/* Jumps to address addr. */
void opJMP(address addr);
/* Jumps to address addr if z flag is set. */
void opJMPZ(address addr);
/* Jumps to address addr if previous compare op1 == op2. */
void opJMPEQ(address addr);
/* Jumps to address addr if previous compare op1 != op2. */
void opJMPNEQ(address addr);
/* Jumps to address addr if previous compare op1 > op2. */
void opJMPGT(address addr);
/* Jumps to address addr if previous compare op1 >= op2. */
void opJMPGTE(address addr);
/* Jumps to address addr if previous compare op1 < op2. */
void opJMPLT(address addr);
/* Jumps to address addr if previous compare op1 <= op2. */
void opJMPLTE(address addr);

/* Gets the next instructions and packs it into opcode and operands. */
Instruction fetchInstruction();

/* --- IO --- */
void cpuPutc(char c);
char cpuGetc();


/* -- Utils -- */
StatusReg getStatusReg();
void updateStatusReg();
void updateZFlag(word result);
void cpu_init();
int cpu_run();


#endif