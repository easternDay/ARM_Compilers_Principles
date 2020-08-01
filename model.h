#pragma once
//操作数类型名称
#define OPD_NULL    0   //空值
#define OPD_CONST   1   //立即数
#define OPD_VAR     2   //变量名
#define OPD_TEMP    3   //临时变量
#define OPD_STRING  4   //字符串常量

#define OPD_FUNC    5   //函数名(call,funcName,_,_)
#define OPD_PARAM   6   //函数参数表

//运算符常量名称
#define OP_ASS     0       //赋值运算
#define OP_ADD     1       //+加
#define OP_SUB     2       //-减
#define OP_MUL     3       //*乘
#define OP_DIV     4       ///除
#define OP_MOD     5       //%求余
#define OP_NEG     6       //-取反

#define OP_AND     7       //&&逻辑与
#define OP_OR      8       //||逻辑或
#define OP_NOT     9       //！逻辑非
#define OP_EQU     10      //==等于
#define OP_NEQU    11      //！=不等于
#define OP_GT      12      //>大于
#define OP_LS      13      //<小于
#define OP_GE      14      //>=大于等于
#define OP_LE      15      //<=小于等于

#define OP_ASS_ARR 16      //一维数组赋值
#define OP_GET_ARR 17      //一维数组访问

#define OP_CALL    18      //函数调用
#define OP_SET_ARG 19      //设置参数？
#define OP_LABEL   20      //设置标签？
#define OP_GOTO    21      //无条件跳转
#define OP_JNZ     22      //条件为真跳转
#define OP_STARTCALL 23    //开始调用函数标志
#define OP_RETURN  24      //返回

#define OP_FUNC    25      //函数定义  (funcDef,参数链表，参数个数，_)

/*
	操作数结构体
*/
typedef struct Operand
{
	int opdType; //操作数类型
	union opdContent {
		int opdInt;			  //立即数、跳转到的四元式序号...
		char *opdStr;		  //变量名、字符串常量、临时变量变量名
	} opdTag;				  //操作数标签，代表一个值（立即数）、一个编号（临时变量的编号）或字符串（变量名或字符串常量）
} Operand;

/*
四元式结构体
*/
typedef struct Quaternion
{
	int index;			   //四元式序号
	int opType;			   //运算符类型
	Operand opd1, opd2, result; //操作数
	struct Quaternion *front;	   //上一条四元式
	struct Quaternion *next;	   //下一条四元式
} Quaternion;