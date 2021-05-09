#ifndef ASSEMBLER_H
#define ASSEMBLER_H

int assemble();


typedef enum {
    IS_NEW_LINE,
    IS_COMMENT,
    IS_OPERATION_OP,
    IS_OPERATION_ARG,
    IS_OPERATION_ARG_WHITESPACE,
    IS_UNKNOWN
} AssemblerState;





#endif
