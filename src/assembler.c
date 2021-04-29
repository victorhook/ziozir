#include <string.h>
#include <stdio.h>

#include "cpu.h"
#include "assembler.h"


AssemblerState getNextStateIsNewLine(const char c)
{
    return IS_NEW_LINE;
}
AssemblerState getNextStateIsComment(const char c)
{
    return IS_NEW_LINE;
}
AssemblerState getNextStateIsOperationOp(const char c)
{
    return IS_NEW_LINE;
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
    AssemblerState currState = IS_NEW_LINE;
    AssemblerState nextState;

    Instruction* instructions;
    int instrCounter = 0;
    int argCounter = 0;

    const char* input;
    char* c = input;

    while (*c != EOF) {
        switch (currState) {
            case IS_NEW_LINE:
                nextState = getNextStateIsNewLine(c);
                break;
            case IS_COMMENT:
                nextState = getNextStateIsComment(c);
                break;
            case IS_OPERATION_OP:
                nextState = getNextStateIsOperationOp(c);
                break;
            case IS_OPERATION_ARG:
                nextState = getNextStateIsOperationArg(c);
                break;
            case IS_OPERATION_ARG_WHITESPACE:
                nextState = getNextStateIsOperationArgWhiteSpace(c);
                break;
            case IS_UNKNOWN:
                nextState = getNextStateIsUnkown(c);
                break;
            default:
                break;
        }

        currState = nextState;
        c++;
    }



    return 1;
}