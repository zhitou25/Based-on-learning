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

//堆的初始化
void HeapInit(pheap hp);

//建堆
void CreatHeap(pheap hp);

//堆尾的插入
void HeapInsert(pheap hp, DataType data);

//堆顶的删除
void Heapdel(pheap hp);

//向下调整（建堆）
void AdjustDown(pheap hp, int parent);

//向上调整（插入）
void AdjustUp(pheap hp);

//堆的层数
void HeapFlow(pheap hp);

//堆排序
void HeapSort(pheap hp);

//销毁堆
void HeapDestory(pheap hp);


#endif  //_HEAP_H_



//堆的初始化
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


//建堆
void CreatHeap(pheap hp)
{
	int i;
	for (i = (hp->size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(hp, i);
	}
}


//堆尾的插入
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


//堆顶的删除
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

//向下调整（建堆）
void AdjustDown(pheap hp, int parent)
{
	assert(hp);
	//确定第一个非叶子结点的左孩子
	int lchild = 2 * parent + 1;
	while (lchild<hp->size)
	{//判断第一个非叶子结点是否有右孩子并且比较左右孩子的大小，取小的
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
//向上调整（插入）
void AdjustUp(pheap hp)
{//确定第一个非叶子结点
	int parent = (hp->size - 2) / 2;
	//确定第一个非叶子节点的左孩子
	int lchild = 2 * parent + 1;
	//一定要加上判断条件lchild!=0;如果在只有两个结点，且双亲结点
	//hp->arr[parent]>hp->arr[lchild]时，就会造成死循环。
	while (parent >= 0 && lchild != 0)
	{//判断插入结点位置
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

//堆的高度
void HeapFlow(pheap hp)
{
	assert(hp);
	int flow = ((int)(log(hp->size) / log(2))) + 1;
	printf("堆的高度是：%d\n", flow);
}
//销毁堆
void HeapDestory(pheap hp)
{
	free(hp->arr);
	hp->arr = NULL;
	free(hp);
	hp = NULL;
}

//堆排序
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
	printf("堆排序:");
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
	//用数组来初始化堆
	HeapInit(hp);
	printf("用数组来初始化堆:");
	//打印数组
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//创建小顶堆并打印
	CreatHeap(hp);
	printf("创建小顶堆:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//堆插入数据 3
	HeapInsert(hp, 3);
	printf("堆插入数据 3:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//堆顶的删除
	Heapdel(hp);
	printf("堆顶的删除:");
	for (int i = 0; i < hp->size; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n");
	//堆排序
	HeapSort(hp);
	printf("\n");
	system("pause");
	return 0;
}