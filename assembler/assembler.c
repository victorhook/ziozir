#include <string.h>
#include <stdio.h>

#include "cpu.h"
#include "assembler.h"


AssemblerState getNextStateIsNewLine(const char c)
{
    switch (c) {
        case ' ':
        case '\t':
            return IS_UNKNOWN;
        case '\n':
            return IS_NEW_LINE;
        case ';':
            return IS_COMMENT;
        default:
            return IS_OPERATION_OP;
    }
}
AssemblerState getNextStateIsComment(const char c)
{
    switch (c) {
        case '\n':
            return IS_NEW_LINE;
        default:
            return IS_COMMENT;
    }
}
AssemblerState getNextStateIsOperationOp(const char c)
{
    switch (c) {
        case ' ':
        case '\t':
            return IS_OPERATION_ARG;
        case ';':
            return IS_COMMENT;
        case '\n':
            return IS_NEW_LINE;
        default:
            return IS_OPERATION_OP;
    }
}
AssemblerState getNextStateIsOperationArg(const char c)
{
    return IS_NEW_LINE;
}
AssemblerState getNextStateIsOperationArgWhiteSpace(const char c)
{
    return IS_NEW_LINE;
}
AssemblerState getNextStateIsUnkown(const char c)
{
    return IS_NEW_LINE;
}
Operation getOperation(const char* buf)
{
    return OP_ADD;
}
Arg getArgument(const char* buf)
{
    return REG_1;
}

char msg[200];

int assemble()
{
    #define BUFF_SIZE 20
    const char* input;

    AssemblerState currState = IS_NEW_LINE;
    AssemblerState nextState;

    Instruction* instructions;
    char buf[BUFF_SIZE];
    int buffIndex = 0;
    int instrCounter = 0;
    int argCounter = 0;

    const char* c = input;

    while (*c != EOF) {
        switch (currState) {
            case IS_NEW_LINE:
                nextState = getNextStateIsNewLine(*c);
                if (nextState == IS_OPERATION_OP)
                    buf[buffIndex] = *c;
                break;
            case IS_COMMENT:
                nextState = getNextStateIsComment(*c);
                break;
            case IS_OPERATION_OP:
                nextState = getNextStateIsOperationOp(*c);
                if (nextState == IS_OPERATION_ARG) {
                    instructions[instrCounter].op = getOperation(buf);
                    buffIndex = 0;
                }
                break;
            case IS_OPERATION_ARG:
                nextState = getNextStateIsOperationArg(*c);
                if (nextState == IS_OPERATION_ARG_WHITESPACE || nextState == IS_NEW_LINE) {
                    instructions[instrCounter].args[argCounter] = getArgument(buf);
                    buffIndex = 0;
                    if (nextState == IS_NEW_LINE) {     // End of instruction.
                        argCounter = 0;
                        instrCounter++;
                    }
                } 
                break;
            case IS_OPERATION_ARG_WHITESPACE:
                nextState = getNextStateIsOperationArgWhiteSpace(*c);
                break;
            case IS_UNKNOWN:
                nextState = getNextStateIsUnkown(*c);
                break;
            default: 
                break;
        }

        currState = nextState;
        c++;
    }


    return 1;
}