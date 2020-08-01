#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"          //数据结构定义
#include "readQuaternion.h" //此文件用来读取文本输入的四元式
#include "arm_result.h"     //生成汇编代码的头文件

int main()
{
    /*字典测试环节
    //初始化30个存储空间，若不够，会自动翻倍，变为60个
    dictionary *Regesiter = dictionary_new(31); //31个通用寄存器
    dictionary_set(Regesiter, "x", "1的地址");
    dictionary_set(Regesiter, "y", "2的地址");
    dictionary_set(Regesiter, "z", "3的地址");
    char **str = dictionary_get(Regesiter, "x", NULL); //从字典中读取
    printf("%s", str);
    //销毁
    dictionary_del(Regesiter);
    */
    InitRegesiter(); //初始化寄存器相关参数

    int index = 0; //四元式索引
    FILE *fp = NULL;
    while (true)
    {
        char op[100];     //符号
        char opd1[100];   //操作数1
        char opd2[100];   //操作数2
        char result[100]; //结果

        //索引自增，以1为开始，如果想要0为开始请移动到最后
        index++;

        //输入示例,务必使用空格分隔
        //- 1 2 x
        printf("输入四元式:");
        scanf("%s %s %s %s", op, opd1, opd2, result);
        Quaternion Qua;
        InitQuaternion(&Qua, index, op, opd1, opd2, result);
        //printf("符号：%s\n操作数1：%s\n操作数2：%s\n结果：%s\n", op, opd1, opd2, result);

        //输出汇编代码
        fp = fopen("./out.txt", "a+");
        fprintf(fp, " ");
        fprintf(fp, GetArmCode(Qua));
        fclose(fp);

        //回车查看一下，自己断点也可以
        getchar();
    }

    return 0;
}