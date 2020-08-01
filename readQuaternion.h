#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

//判断字符串是否为数字
bool IsDigital(char *str)
{
    //C 库函数 size_t strspn(const char *str1, const char *str2) 检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
    if (strspn(str, "0123456789") == strlen(str))
    {
        return true;
    }
    return false;
}

//返回输入字符串对应的操作数/变量
void GetOperand(Operand *OPD, char *opd)
{
    //TODO
    //其实变量名判断这里我判断是否纯数字，其实判断第一个是否为数字就可以，因为变量名的命名规则。但是这样稳妥一些...
    //而且此处没考虑到doulble这里的小数点

    //如果为纯数字
    if (IsDigital(opd))
    {
        OPD->opdType = OPD_CONST;       //设置为立即数
        OPD->opdTag.opdInt = atoi(opd); //转化为数字
    }
    else
    {
        OPD->opdType = OPD_VAR;   //设置为变量
        OPD->opdTag.opdStr = opd; //设置变量名
    }
}

//获取运算符类型
int GetOpType(char *op)
{
    if (strcmp(op, "=") == 0)
    {
        return OP_ASS; //赋值运算
    }
    else if (strcmp(op, "+") == 0)
    {
        return OP_ADD; //+加
    }
    else if (strcmp(op, "-") == 0)
    {
        return OP_SUB; //-减
    }
    else if (strcmp(op, "*") == 0)
    {
        return OP_MUL; //*乘
    }
    else if (strcmp(op, "/") == 0)
    {
        return OP_DIV; ///除
    }
    else if (strcmp(op, "%") == 0)
    {
        return OP_MOD; //%求余
    }
    //此处其实不会生效，因为是自己本地读取
    else if (strcmp(op, "-") == 0)
    {
        return OP_NEG; //-取相反数
    }
    else
    {
        //后面还有写不动了，到时候再写,正常else该返回OP_FUNC？
        return -1;
    }
}

//拆分输入的四元式
void InitQuaternion(Quaternion *Qua, int index, char *op, char *opd1, char *opd2, char *result)
{

    Operand OPD_1;
    GetOperand(&OPD_1, opd1); //获取操作数1

    Operand OPD_2;
    GetOperand(&OPD_2, opd2); //获取操作数2

    Operand OPD_RESULT;
    GetOperand(&OPD_RESULT, result); //其实可以这一步直接设置为变量，如果这个不为变量，肯定是有错误

    Qua->index = index; //设置索引
    Qua->opType = GetOpType(op);
    Qua->opd1 = OPD_1;
    Qua->opd2 = OPD_2;
    Qua->result = OPD_RESULT;
    //还有front和next指针我就不写了，这里有用不上。
    Qua->front = Qua->next = NULL;
}