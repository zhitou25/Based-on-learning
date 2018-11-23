#ifndef _SLIST_H_
#define _SLIST_H_
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#pragma warning(disable:4996)
typedef int DataType;
#define init_size 6
// ��̬˳���ṹ 
typedef struct SeqList
{
	DataType *_pData;  // �ռ���׵�ַ
	int capacity;     // �ռ���ܴ�С
	int size;         // ��ЧԪ�صĸ��� 
}SeqList, *PSeqList;

//˳����ʼ��
void SeqListInit(PSeqList ps);

//˳���ͷ�����
void SeqListPushFront(PSeqList ps, DataType data);

// ˳���β�����
void SeqListPushBack(PSeqList ps, DataType data);

//˳���ͷɾ����
void SeqListPopFront(PSeqList ps);

//˳���βɾ����
void SeqListPopBack(PSeqList ps);

// ��˳���ָ��λ�ò���ָ������
void SeqListInsert(PSeqList ps, int pos, DataType data);

// ɾ��˳�����ָ��λ�õ�����
void SeqListErase(PSeqList ps, int pos);

// ��˳�����ȷ��data��һ�γ��ֵ�λ��
int SeqListFind(PSeqList ps, DataType data);

// ɾ��˳���������ֵΪdata��Ԫ��
void SeqListRemoveAll(PSeqList ps, DataType data);

// ɾ��˳����е�һ��ֵΪdata��Ԫ��
void SeqListRemove(PSeqList ps, DataType data);

// ��ȡ˳��������һ��Ԫ��
DataType SeqListBack(PSeqList ps);

//��ȡ˳�������ЧԪ�صĸ���
int SeqListSize(PSeqList ps);

// ��ð�ݷ���˳����е�Ԫ�ؽ�������
void BubbleSort(PSeqList ps);

//��ʾ��ǰ˳�������Ԫ��
void show_sqlist(PSeqList ps);

//����˳���
void SeqListDestroy(PSeqList ps);

#endif //_SLIST_H_



//�����в������ʱ��˳���ռ䲻��������������Ĳ���
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

//˳����ʼ��
void SeqListInit(PSeqList ps)
{
	assert(ps);
	ps->_pData = (DataType*)malloc(sizeof(DataType)*init_size);
	if ((ps->_pData == NULL) || (ps == NULL))
	{
		printf("�����ڴ�ʧ��,��ʼ��ʧ��!\n");
		return;
	}
	ps->size = 0;
	ps->capacity = init_size*sizeof(DataType);
}

// ˳���β�����
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
			printf("����ʧ�ܣ�\n");
			return;
		}
	}
	ps->_pData[ps->size] = data;
	ps->size++;
}

// ˳���βɾ����
void SeqListPopBack(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");

	}
	ps->size--;
}

// ˳���ͷ�����
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
			printf("����ʧ�ܣ�\n");
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

// ˳���ͷɾ����
void SeqListPopFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
		return;
	}
	for (int i = 0; i < ps->size; i++)
	{
		ps->_pData[i] = ps->_pData[i + 1];
	}
	ps->size--;
}

// ��˳���ָ��λ�ò���ָ������
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
				printf("����ʧ�ܣ�\n");
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
		printf("����λ��ѡ�����\n");
		return;
	}
}

// ɾ��˳�����ָ��λ�õ�����
void SeqListErase(PSeqList ps, int pos)
{
	assert(ps);
	if (0 <= pos < ps->size)
	{
		if (0 == ps->size)
		{
			printf("˳���Ϊ��!\n");
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
		printf("����λ��ѡ�����\n");
		return;
	}
}

// ��˳�����ȷ��data��һ�γ��ֵ�λ��
int SeqListFind(PSeqList ps, DataType data)
{
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
		return 0;
	}
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->_pData[i] == data)
		{
			printf("%d��һ�γ�����˳����%d��λ��\n", data, i + 1);
			return 0;
			break;
		}
	}
	printf("˳������޸����ݣ�\n");
	return 0;
}

// ɾ��˳����е�һ��ֵΪdata��Ԫ��
void SeqListRemove(PSeqList ps, DataType data)
{
	assert(ps);
	int i;
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
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

// ɾ��˳���������ֵΪdata��Ԫ��
void SeqListRemoveAll(PSeqList ps, DataType data)
{
	assert(ps);
	int i = 0;
	int j = 0;
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
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

// ��ȡ˳�������ЧԪ�صĸ���
int SeqListSize(PSeqList ps)
{
	assert(ps);
	printf("˳���Ԫ�ظ�����%d\n", ps->size);
	return 0;
}
// ��ȡ˳��������
int SeqListCapacity(PSeqList ps)
{
	assert(ps);
	printf("˳���������%d", ps->capacity);
	return 0;
}

// ��ȡ˳����е�һ��Ԫ��
DataType SeqListFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
		return 0;
	}
	printf("˳����һ��Ԫ���ǣ�%d", ps->_pData[0]);
	return 0;
}

// ��ȡ˳��������һ��Ԫ��
DataType SeqListBack(PSeqList ps)
{
	assert(ps);
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
		return 0;
	}
	printf("˳������һ��Ԫ���ǣ�%d\n", ps->_pData[ps->size - 1]);
	return 0;
}

// ���˳�������ЧԪ�صĸ���
void SeqListClear(PSeqList ps)
{
	assert(ps);
	ps->size = 0;
}

// ����˳���
void SeqListDestroy(PSeqList ps)
{
	if (NULL != ps)
	{
		free(ps);
		ps = NULL;
	}
}

// ��ð�ݷ���˳����е�Ԫ�ؽ�������
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

//��ʾ��ǰ˳�������Ԫ��
void show_sqlist(PSeqList ps)
{
	int i = 0;
	if (0 == ps->size)
	{
		printf("˳���Ϊ�գ�\n");
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
	printf("                      ˳���                    \n");
	printf("    1.β������                        2.ͷɾ���� \n");
	printf("    3.�ҵ�һ�����ݵ�һ�γ��ֵ�λ��    4.βɾ���� \n");
	printf("    5.ͷ������                        6.��˳���ָ��λ�ò���Ԫ�� \n");
	printf("    7.ɾ��ָ��λ��Ԫ��                8.ð������  \n");
	printf("    9.ɾ����һ�γ��ֵ�ָ������        10.˳����С \n");
	printf("    11.��ȡ˳������һ��Ԫ��         12.ɾ��˳���������ָ����ֵ \n");
	printf("    13.�˳� \n");
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

