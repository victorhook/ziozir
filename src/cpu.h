#ifndef CPU_H
#define CPU_H
#include "emulator.h"


word readReg(reg reg);
void writeReg(reg reg, word value);


/* --- Instructions --- */
typedef enum {
    /* Arithmetic */
    OP_ADD,     // ADD R1 R2 R3  -> R1 = R2 + R3
    OP_ADDI,    // ADDI R1 R2 2  -> R1 = R2 + 2
    OP_SUB,     // SUB R1 R2 R3  -> R1 = R2 - R3
    OP_SUBI,    // SUBI R1 R2 2  -> R1 = R2 - 2
    OP_MUL,     // MUL R1 R2 R3  -> R1 = R2 + R3
    OP_MULI,    // MULI R1 R2 2  -> R1 = R2 * 2
    OP_AND,     // AND R1 R2 R3  -> R1 = R2 & R3
    OP_ANDI,    // ANDI R1 R2 2  -> R1 = R2 & 2
    OP_OR,      // OR R1 R2 R3   -> R1 = R2 || R3
    OP_ORI,     // ORI R1 R2 2   -> R1 = R2 || 2
    OP_XOR,     // XOR R1 R2 R3  -> R1 = R2 ^ R3
    OP_XORI,    // XORI R1 R2 2  -> R1 = R2 ^ 2
    OP_NOT,     // NOT R1 R2     -> R1 = ~R2
    OP_NOTI,    // NOTI R1 2     -> R1 = ~2
    /* Memory -> Register */
    OP_LD,      // LD R1 Label   -> R1 = $[Label]
    OP_LDI,     // LDI R1 2      -> R1 = $[2]
    /* Register -> Memory */
    OP_ST,      // ST R1 Label   -> $[Label] = R1
    OP_STI,     // ST R1 2       -> $[2] = R1
    /* Misc */
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


/* ------------- Instructions ------------------- */

/* -- Arithmetic -- */

/* ADD R1 R2 R3  -> R1 = R2 + R3 */
void opADD(address to, reg r1, reg r2);
/* ADDI R1 R2 2  -> R1 = R2 + 2 */
void opADDI(address to, reg r, word op);
/* SUB R1 R2 R3  -> R1 = R2 - R3 */
void opSUB(address to, reg r1, reg r2);
/* SUBI R1 R2 2  -> R1 = R2 - 2 */
void opSUBI(address to, reg r, word op);
/* MUL R1 R2 R3  -> R1 = R2 + R3 */
void opMUL(address to, reg r1, reg r2);
/* MULI R1 R2 2  -> R1 = R2 * 2 */
void opMULI(address to, reg r, word op);
/* AND R1 R2 R3  -> R1 = R2 & R3 */
void opAND(address to, reg r1, reg r2);
/* ANDI R1 R2 2  -> R1 = R2 & 2 */
void opANDI(address to, reg r, word op);
/* OR R1 R2 R3   -> R1 = R2 || R3 */
void opOR(address to, reg r1, reg r2);
/* ORI R1 R2 2   -> R1 = R2 || 2 */
void opORI(address to, reg r, word op);
/* XOR R1 R2 R3  -> R1 = R2 ^ R3 */
void opXOR(address to, reg r1, reg r2);
/* XORI R1 R2 2  -> R1 = R2 ^ 2 */
void opXORI(address to, reg r, word op);
/* NOT R1 R2     -> R1 = ~R2 */
void opNOT(address to, reg r);
/* NOTI R1 2     -> R1 = ~2 */
void opNOTI(address to, word op);
/* Increments register r by 1. */
void opINC(reg r);
/* Decrements register r by 1. */
void opDEC(reg r);


/* -- Memory -- */

/* Loads value at Ram[from] into register r. */
void opLD(reg r, address from);
/* Loads value into register r. */
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
void opJUMP(address addr);
/* Jumps to address addr if z flag is set. */
void opJUMPZ(address addr);
/* Jumps to address addr if op1 == op2. */
void opJUMPEQ(address addr, word op1, word op2);
/* Jumps to address addr if op1 != op2. */
void opJUMPNEQ(address addr, word op1, word op2);
/* Jumps to address addr if op1 > op2. */
void opJUMPGT(address addr, word op1, word op2);
/* Jumps to address addr if op1 >= op2. */
void opJUMPGTE(address addr, word op1, word op2);
/* Jumps to address addr if op1 < op2. */
void opJUMPLT(address addr, word op1, word op2);
/* Jumps to address addr if op1 <= op2. */
void opJUMPLTE(address addr, word op1, word op2);

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