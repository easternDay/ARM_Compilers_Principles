#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "arm_regesiter.h" //寄存器相关

//获取对应的立即数
char *GetImmediate(int num)
{
    static char result[100];
    memset(result, 0, 100); //重设
    strcat(result, "#");
    char number[10];
    itoa(num, number, 10); //立即数转化为字符串
    strcat(result, number);
    return result;
}

//获取寄存器名字
char *GetRegName(int index)
{
    static char result[5];
    memset(result, 0, 5); //重设
    strcat(result, "r");
    char number[2];
    itoa(index, number, 10); //立即数转化为字符串
    strcat(result, number);
    return result;
}

//MOV汇编代码格式化
char *MOV(const char *Opd1, const char *Opd2)
{
    static char result[100];
    sprintf(result, "MOV %s,%s\n", Opd1, Opd2);
    return result;
}
//SUB汇编代码格式化
char *SUB(const char *Opd1, const char *Opd2, const char *Opd3)
{
    static char result[100];
    sprintf(result, "SUB %s,%s,%s\n", Opd1, Opd2, Opd3);
    return result;
}
//MVN汇编代码格式化
char *MVN(const char *Opd1, const char *Opd2)
{
    static char result[100];
    sprintf(result, "MVN %s,%s\n", Opd1, Opd2);
    return result;
}

//减法汇编代码生成
char *GetSubCode(Quaternion Qua)
{
    static char Code[1000] = "";
    memset(Code, 0, 1000); //重设
    char opd1[100], opd2[100], result[100];
    if (Qua.opd1.opdType == OPD_CONST && Qua.opd2.opdType == OPD_CONST)
    {
        strcpy(result, GetRegName(GetReg(Qua.result.opdTag.opdStr)));
        //都是立即数则不执行操作,直接给Result赋值
        // MOV RESULT,#(opd1-opd2)
        strcat(Code, MOV(result, GetImmediate(Qua.opd1.opdTag.opdInt - Qua.opd2.opdTag.opdInt))); //生成MOV代码并拼接
    }
    if (Qua.opd1.opdType == OPD_CONST && Qua.opd2.opdType == OPD_VAR)
    {
        //第一个是立即数，第二个是变量
        //SUB第一个参数只能为寄存器，所以我们先相减，然后取反
        // SUB RESULT,opd2,opd1
        // MVN RESULT,RESULT
        strcpy(result, GetRegName(GetReg(Qua.result.opdTag.opdStr)));
        strcpy(opd2, GetRegName(GetReg(Qua.opd2.opdTag.opdStr)));

        strcat(Code, SUB(result, opd2, GetImmediate(Qua.opd1.opdTag.opdInt)));
        strcat(Code, MVN(result, result));
    }
    if (Qua.opd1.opdType == OPD_VAR && Qua.opd2.opdType == OPD_VAR)
    {
        // SUB RESULT,opd1,opd2
        strcpy(result, GetRegName(GetReg(Qua.result.opdTag.opdStr)));
        strcpy(opd2, GetRegName(GetReg(Qua.opd2.opdTag.opdStr)));
        strcpy(opd1, GetRegName(GetReg(Qua.opd1.opdTag.opdStr)));
        strcat(Code, SUB(result, opd1, opd2));
    }
    if (Qua.opd1.opdType == OPD_VAR && Qua.opd2.opdType == OPD_CONST)
    {
        // SUB RESULT,opd1,opd2
        strcpy(result, GetRegName(GetReg(Qua.result.opdTag.opdStr)));
        strcpy(opd1, GetRegName(GetReg(Qua.opd1.opdTag.opdStr)));
        strcat(Code, SUB(result, opd1, GetImmediate(Qua.opd2.opdTag.opdInt)));
    }
    return Code;
}