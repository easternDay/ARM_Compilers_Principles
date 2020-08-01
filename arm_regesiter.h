#include "dictionary.h" //字典函数实现
#include "queue.h"      //队列实现

//TODO
//回收寄存器

//寄存器数组
int Regesiter[30];

//寄存器字典
dictionary *RegesiterMap;
//空闲寄存器队列
Queue *SpareRegister;

//初始化对应参数
void InitRegesiter()
{
    RegesiterMap = dictionary_new(30);                 //X0-X30
    SpareRegister = Queue_Init(OnQueueIncreasedEvent); //初始化空闲寄存器队列
    //初始化寄存器数组
    for (int i = 0; i < 30; i++)
    {
        Regesiter[i] = i + 1;
        //进入队列
        Queue_AddToHead(SpareRegister, &Regesiter[i]);
    }
}

//获取对应的寄存器
int GetReg(const char *var)
{
    //如果没分配寄存器
    if (dictionary_get(RegesiterMap, var, NULL) == NULL)
    {
        //有空闲寄存器
        if (SpareRegister->length != 0)
        {
            void *data = Queue_GetFromHead(SpareRegister);
            //int reg = *((int *)data);//获得寄存器序号
            dictionary_set(RegesiterMap, var, data);
            return *((int *)data); //返回寄存器序号
        }
        //没空闲寄存器
        else
        {
            //后面补充
            return -1;
        }
    }
    //如果分配了寄存器
    else
    {
        return *((int *)dictionary_get(RegesiterMap, var, NULL)); //返回分配的寄存器
    }
}