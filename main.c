#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"          //���ݽṹ����
#include "readQuaternion.h" //���ļ�������ȡ�ı��������Ԫʽ
#include "arm_result.h"     //���ɻ������ͷ�ļ�

int main()
{
    /*�ֵ���Ի���
    //��ʼ��30���洢�ռ䣬�����������Զ���������Ϊ60��
    dictionary *Regesiter = dictionary_new(31); //31��ͨ�üĴ���
    dictionary_set(Regesiter, "x", "1�ĵ�ַ");
    dictionary_set(Regesiter, "y", "2�ĵ�ַ");
    dictionary_set(Regesiter, "z", "3�ĵ�ַ");
    char **str = dictionary_get(Regesiter, "x", NULL); //���ֵ��ж�ȡ
    printf("%s", str);
    //����
    dictionary_del(Regesiter);
    */
    InitRegesiter(); //��ʼ���Ĵ�����ز���

    int index = 0; //��Ԫʽ����
    FILE *fp = NULL;
    while (true)
    {
        char op[100];     //����
        char opd1[100];   //������1
        char opd2[100];   //������2
        char result[100]; //���

        //������������1Ϊ��ʼ�������Ҫ0Ϊ��ʼ���ƶ������
        index++;

        //����ʾ��,���ʹ�ÿո�ָ�
        //- 1 2 x
        printf("������Ԫʽ:");
        scanf("%s %s %s %s", op, opd1, opd2, result);
        Quaternion Qua;
        InitQuaternion(&Qua, index, op, opd1, opd2, result);
        //printf("���ţ�%s\n������1��%s\n������2��%s\n�����%s\n", op, opd1, opd2, result);

        //���������
        fp = fopen("./out.txt", "a+");
        fprintf(fp, " ");
        fprintf(fp, GetArmCode(Qua));
        fclose(fp);

        //�س��鿴һ�£��Լ��ϵ�Ҳ����
        getchar();
    }

    return 0;
}