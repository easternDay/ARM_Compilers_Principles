#pragma once
#include "arm_code_gen.h" //汇编代码生成各个函数的汇总

char *GetArmCode(Quaternion Qua)
{
    switch (Qua.opType)
    {
    case OP_ASS:
    case OP_ADD:
    case OP_SUB: //减法
        return GetSubCode(Qua);
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
    case OP_NEG:
    case OP_AND:
    case OP_OR:
    case OP_NOT:
    case OP_EQU:
    case OP_NEQU:
    case OP_GT:
    case OP_LS:
    case OP_GE:
    case OP_LE:
    case OP_ASS_ARR:
    case OP_GET_ARR:
    case OP_CALL:
    case OP_SET_ARG:
    case OP_LABEL:
    case OP_GOTO:
    case OP_JNZ:
    case OP_STARTCALL:
    case OP_RETURN:
    case OP_FUNC:
    default:
        break;
    }
}