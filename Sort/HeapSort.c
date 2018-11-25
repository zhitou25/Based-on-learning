#ifndef _HEAP_H_
#define _HEAP_H_
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include<math.h>
#define MAXSIZE  10
typedef int DataType;

typedef struct heap
{
	DataType* arr;
	int size;
	int capacity;
}heap, *pheap;

//�ѵĳ�ʼ��
void HeapInit(pheap hp);

//����
void CreatHeap(pheap hp);

//��β�Ĳ���
void HeapInsert(pheap hp, DataType data);

//�Ѷ���ɾ��
void Heapdel(pheap hp);

//���µ��������ѣ�
void AdjustDown(pheap hp, int parent);

//���ϵ��������룩
void AdjustUp(pheap hp);

//�ѵĲ���
void HeapFlow(pheap hp);

//������
void HeapSort(pheap hp);

//���ٶ�
void HeapDestory(pheap hp);


#endif  //_HEAP_H_



//�ѵĳ�ʼ��
void HeapInit(pheap hp)
{
	hp->size = 0;
	for (int i = 0; i < 10; i++)
	{
		hp->arr[i] = rand() % 10;
		hp->size++;
	}
	hp->capacity = MAXSIZE;
}


//����
void CreatHeap(pheap hp)
{
	int i;
	for (i = (hp->size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(hp, i);
	}
}


//��β�Ĳ���
void HeapInsert(pheap hp, DataType data)
{
	assert(hp);
	if (hp->capacity == hp->size)
	{
		hp->arr = realloc(hp->arr, sizeof(DataType)*MAXSIZE * 2);
		hp->capacity = MAXSIZE * 2;
	}
	hp->arr[hp->size] = data;
	hp->size++;
	AdjustUp(hp);
}


//�Ѷ���ɾ��
void Heapdel(pheap hp)
{
	assert(hp);
	if (!hp->size)
		return;
	DataType temp = hp->arr[0];
	hp->arr[0] = hp->arr[hp->size - 1];
	hp->arr[hp->size - 1] = temp;
	hp->size--;
	AdjustDown(hp, 0);
}

//���µ��������ѣ�
void AdjustDown(pheap hp, int parent)
{
	assert(hp);
	//ȷ����һ����Ҷ�ӽ�������
	int lchild = 2 * parent + 1;
	while (lchild<hp->size)
	{//�жϵ�һ����Ҷ�ӽ���Ƿ����Һ��Ӳ��ұȽ����Һ��ӵĴ�С��ȡС��
		if (lchild + 1< hp->size&&hp->arr[lchild]>hp->arr[lchild + 1])
			lchild++;
		if (hp->arr[lchild] >= hp->arr[parent])
			break;
		DataType temp = hp->arr[parent];
		hp->arr[parent] = hp->arr[lchild];
		hp->arr[lchild] = temp;
		parent = lchild;
		lchild = 2 * parent + 1;
	}
}
//���ϵ��������룩
void AdjustUp(pheap hp)
{//ȷ����һ����Ҷ�ӽ��
	int parent = (hp->size - 2) / 2;
	//ȷ����һ����Ҷ�ӽڵ������
	int lchild = 2 * parent + 1;
	//һ��Ҫ�����ж�����lchild!=0;�����ֻ��������㣬��˫�׽��
	//hp->arr[parent]>hp->arr[lchild]ʱ���ͻ������ѭ����
	while (parent >= 0 && lchild != 0)
	{//�жϲ�����λ��
		if (lchild + 1 < hp->size)
			lchild++;
		if (hp->arr[lchild] >= hp->arr[parent])
			break;
		DataType temp = hp->arr[parent];
		hp->arr[parent] = hp->arr[lchild];
		hp->arr[lchild] = temp;
		lchild = parent;
		parent = (lchild - 1) / 2;
	}
}

//�ѵĸ߶�
void HeapFlow(pheap hp)
{
	assert(hp);
	int flow = ((int)(log(hp->size) / log(2))) + 1;
	printf("�ѵĸ߶��ǣ�%d\n", flow);
}
//���ٶ�
void HeapDestory(pheap hp)
{
	free(hp->arr);
	hp->arr = NULL;
	free(hp);
	hp = NULL;
}

//������
void HeapSort(pheap hp)
{
	int i;
	int temp;
	int num = hp->size;
	while (hp->size > 1)
	{
		for (i = hp->size - 1; i > 0; i--)
		{
			temp = hp->arr[0];
			hp->arr[0] = hp->arr[i];
			hp->arr[i] = temp;
			hp->size--;
			AdjustDown(hp, 0);
		}
	}
	printf("������:");
	for (int i = 0; i < num; i++)
	{
		printf("%d ", hp->arr[i]);
	}
}



int main()
{
	pheap hp;
	hp = (pheap)malloc(sizeof(heap));
	if (!hp)
		return NULL;
	hp->arr = (DataType*)malloc(sizeof(DataType) * MAXSIZE);
	if (!hp->arr)
		return NULL;
	//����������ʼ����
	HeapInit(hp);
	printf("����������ʼ����:");
	//��ӡ����
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//����С���Ѳ���ӡ
	CreatHeap(hp);
	printf("����С����:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//�Ѳ������� 3
	HeapInsert(hp, 3);
	printf("�Ѳ������� 3:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//�Ѷ���ɾ��
	Heapdel(hp);
	printf("�Ѷ���ɾ��:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//������
	HeapSort(hp);
	printf("\n");
	system("pause");
	return 0;
}