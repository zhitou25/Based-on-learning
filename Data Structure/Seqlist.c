#ifndef _SLIST_H_
#define _SLIST_H_
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#pragma warning(disable:4996)
typedef int DataType;
#define init_size 6
// 动态顺序表结构 
typedef struct SeqList
{
	DataType *_pData;  // 空间的首地址
	int capacity;     // 空间的总大小
	int size;         // 有效元素的个数 
}SeqList, *PSeqList;

//顺序表初始化
void SeqListInit(PSeqList ps);

//顺序表头插操作
void SeqListPushFront(PSeqList ps, DataType data);

// 顺序表尾插操作
void SeqListPushBack(PSeqList ps, DataType data);

//顺序表头删操作
void SeqListPopFront(PSeqList ps);

//顺序表尾删操作
void SeqListPopBack(PSeqList ps);

// 在顺序表指定位置插入指定数据
void SeqListInsert(PSeqList ps, int pos, DataType data);

// 删除顺序表中指定位置的数据
void SeqListErase(PSeqList ps, int pos);

// 在顺序表中确定data第一次出现的位置
int SeqListFind(PSeqList ps, DataType data);

// 删除顺序表中所有值为data的元素
void SeqListRemoveAll(PSeqList ps, DataType data);

// 删除顺序表中第一个值为data的元素
void SeqListRemove(PSeqList ps, DataType data);

// 获取顺序表中最后一个元素
DataType SeqListBack(PSeqList ps);

//获取顺序表中有效元素的个数
int SeqListSize(PSeqList ps);

// 用冒泡法对顺序表中的元素进行排序
void BubbleSort(PSeqList ps);

//显示当前顺序表所有元素
void show_sqlist(PSeqList ps);

//销毁顺序表
void SeqListDestroy(PSeqList ps);

#endif //_SLIST_H_



//当进行插入操作时，顺序表空间不足进行增大容量的操作
static int add_space(PSeqList ps)
{
	assert(ps);
	PSeqList new_ps = (PSeqList)malloc(sizeof(DataType)*init_size * 2);
	if (new_ps != NULL)
	{
		memcpy(new_ps, ps, sizeof(DataType)*init_size);
		ps = new_ps;
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}

//顺序表初始化
void SeqListInit(PSeqList ps)
{
	assert(ps);
	ps->_pData = (DataType*)malloc(sizeof(DataType)*init_size);
	if ((ps->_pData == NULL) || (ps == NULL))
	{
		printf("申请内存失败,初始化失败!\n");
		return;
	}
	ps->size = 0;
	ps->capacity = init_size*sizeof(DataType);
}

// 顺序表尾插操作
void SeqListPushBack(PSeqList ps, DataType data)
{
	assert(ps);
	if ((ps->size*sizeof(DataType)) == ps->capacity)
	{
		if (add_space(ps))
		{
			ps->_pData[ps->size] = data;
			ps->size++;
			return;
		}
		else
		{
			printf("扩容失败！\n");
			return;
		}
	}
	ps->_pData[ps->size] = data;
	ps->size++;
}

// 顺序表尾删操作
void SeqListPopBack(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");

	}
	ps->size--;
}

// 顺序表头插操作
void SeqListPushFront(PSeqList ps, DataType data)
{
	assert(ps);
	if ((ps->size*sizeof(DataType)) == ps->capacity)
	{
		if (add_space(ps))
		{
			for (int i = ps->size; i > 0; i--)
			{
				ps->_pData[i] = ps->_pData[i - 1];
			}
			ps->_pData[0] = data;
			ps->size++;
		}
		else
		{
			printf("扩容失败！\n");
			return;
		}
	}
	int i;
	for (i = ps->size; i > 0; i--)
	{
		ps->_pData[i] = ps->_pData[i - 1];
	}
	ps->_pData[0] = data;
	ps->size++;
}

// 顺序表头删操作
void SeqListPopFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return;
	}
	for (int i = 0; i < ps->size; i++)
	{
		ps->_pData[i] = ps->_pData[i + 1];
	}
	ps->size--;
}

// 在顺序表指定位置插入指定数据
void SeqListInsert(PSeqList ps, int pos, DataType data)
{
	assert(ps);
	if ((pos >= 0) && (pos <= ps->size))
	{
		if ((ps->size*sizeof(DataType)) == ps->capacity)
		{
			if (add_space(ps))
			{
				for (int i = ps->size; i > pos; i--)
				{
					ps->_pData[i] = ps->_pData[i - 1];
				}
				ps->_pData[pos] = data;
				ps->size++;
				return;
			}
			else
			{
				printf("扩容失败！\n");
				return;
			}
		}
		for (int i = ps->size; i >= pos; i--)
		{
			ps->_pData[i] = ps->_pData[i - 1];
		}
		ps->_pData[pos - 1] = data;
		ps->size++;
	}
	else
	{
		printf("插入位置选择错误！\n");
		return;
	}
}

// 删除顺序表中指定位置的数据
void SeqListErase(PSeqList ps, int pos)
{
	assert(ps);
	if (0 <= pos < ps->size)
	{
		if (0 == ps->size)
		{
			printf("顺序表为空!\n");
			return;
		}
		for (int i = pos - 1; i < ps->size; i++)
		{
			ps->_pData[i] = ps->_pData[i + 1];
		}
		ps->size--;
	}
	else
	{
		printf("插入位置选择错误！\n");
		return;
	}
}

// 在顺序表中确定data第一次出现的位置
int SeqListFind(PSeqList ps, DataType data)
{
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return 0;
	}
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->_pData[i] == data)
		{
			printf("%d第一次出现在顺序表第%d个位置\n", data, i + 1);
			return 0;
			break;
		}
	}
	printf("顺序表中无该数据！\n");
	return 0;
}

// 删除顺序表中第一个值为data的元素
void SeqListRemove(PSeqList ps, DataType data)
{
	assert(ps);
	int i;
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return;
	}
	for (i = 0; i < ps->size; i++)
	{
		if (ps->_pData[i] == data)
		{
			for (; i < ps->size - 1; i++)
			{
				ps->_pData[i] = ps->_pData[i + 1];
			}
			ps->size--;
			break;
		}
	}
	return;
}

// 删除顺序表中所有值为data的元素
void SeqListRemoveAll(PSeqList ps, DataType data)
{
	assert(ps);
	int i = 0;
	int j = 0;
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return;
	}
	for (; i < ps->size; i++)
	{
		if (ps->_pData[i] == data)
		{
			j = i;
			for (; i < ps->size - 1; i++)
			{
				ps->_pData[i] = ps->_pData[i + 1];
			}
			ps->size--;
			i = j - 1;
		}
		if (i == ps->size - 1)
		{
			if (ps->_pData[i] == data);
			{
				ps->size--;
			}
			return;
		}
	}
	return;
}

// 获取顺序表中有效元素的个数
int SeqListSize(PSeqList ps)
{
	assert(ps);
	printf("顺序表元素个数：%d\n", ps->size);
	return 0;
}
// 获取顺序表的容量
int SeqListCapacity(PSeqList ps)
{
	assert(ps);
	printf("顺序表容量：%d", ps->capacity);
	return 0;
}

// 获取顺序表中第一个元素
DataType SeqListFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return 0;
	}
	printf("顺序表第一个元素是：%d", ps->_pData[0]);
	return 0;
}

// 获取顺序表中最后一个元素
DataType SeqListBack(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
		return 0;
	}
	printf("顺序表最后一个元素是：%d\n", ps->_pData[ps->size - 1]);
	return 0;
}

// 清空顺序表中有效元素的个数
void SeqListClear(PSeqList ps)
{
	assert(ps);
	ps->size = 0;
}

// 销毁顺序表
void SeqListDestroy(PSeqList ps)
{
	if (NULL != ps)
	{
		free(ps);
		ps = NULL;
	}
}

// 用冒泡法对顺序表中的元素进行排序
void BubbleSort(PSeqList ps)
{
	int i = 0;
	int j = 0;
	for (; i < ps->size - 1; i++)
	{
		for (j = 0; j < ps->size - i - 1; j++)
		{
			if (ps->_pData[j]>ps->_pData[j + 1])
			{
				int temp = ps->_pData[j + 1];
				ps->_pData[j + 1] = ps->_pData[j];
				ps->_pData[j] = temp;
			}
		}
	}
}

//显示当前顺序表所有元素
void show_sqlist(PSeqList ps)
{
	int i = 0;
	if (0 == ps->size)
	{
		printf("顺序表为空！\n");
	}
	for (i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->_pData[i]);
	}
	printf("\n");
}





void menu()
{
	printf("#################################################################\n");
	printf("                      顺序表                    \n");
	printf("    1.尾插数据                        2.头删数据 \n");
	printf("    3.找到一个数据第一次出现的位置    4.尾删数据 \n");
	printf("    5.头插数据                        6.在顺序表指定位置插入元素 \n");
	printf("    7.删除指定位置元素                8.冒泡排序  \n");
	printf("    9.删除第一次出现的指定数据        10.顺序表大小 \n");
	printf("    11.获取顺序表最后一个元素         12.删除顺序表中所有指定的值 \n");
	printf("    13.退出 \n");
	printf("##################################################################\n");
}


int main()
{
	int num;
	SeqList pt;
	SeqListInit(&pt);
	while (1)
	{
		menu();
		printf("choose:");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			SeqListPushBack(&pt, 1);
			SeqListPushBack(&pt, 2);
			SeqListPushBack(&pt, 3);
			SeqListPushBack(&pt, 1);
			show_sqlist(&pt);
			break;
		case 2:
			SeqListPopFront(&pt);
			show_sqlist(&pt);
			break;
		case 3:
			SeqListFind(&pt, 3);
			break;
		case 4:
			SeqListPopBack(&pt);
			show_sqlist(&pt);
			break;
		case 5:
			SeqListPushFront(&pt, 5);
			show_sqlist(&pt);
			break;
		case 6:
			SeqListInsert(&pt, 2, 6);
			show_sqlist(&pt);
			break;
		case 7:
			SeqListErase(&pt, 2);
			show_sqlist(&pt);
			break;
		case 8:
			BubbleSort(&pt);
			show_sqlist(&pt);
			break;
		case 9:
			SeqListRemove(&pt, 1);
			show_sqlist(&pt);
			break;
		case 10:
			SeqListSize(&pt);
			break;
		case 11:
			SeqListBack(&pt);
			break;
		case 12:
			SeqListRemoveAll(&pt, 1);
			show_sqlist(&pt);
			break;
		case 13:
			exit(1);
			break;
		default:
			break;
		}

	}
	system("pause");
	return 0;
}

