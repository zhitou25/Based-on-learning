/*
*C语言的各种排序算法，
*排序算法的时间复杂度下限不可能超过O(nlogn)
*根据不同的场景选择合适的排序算法
*/

//根据数据量分为内部排序和外部排序


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
/*
*插入排序
*  稳定
*/
void InsertSort(int*arr,int n)
{
	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		int end = i - 1;
		temp = arr[i];
		while (temp < arr[end]&&end>=0)
		{
			arr[end + 1] = arr[end];
			end--;
		}
		arr[end + 1] = temp;
	}
}


/*
*希尔排序(优化的插入排序)
*数据量大且混乱，运用插入排序思想。
*不稳定
*/
void ShellSort(int*arr, int n)
{
	int temp = 0;
	int gap = n;//表示跨度大小
	while (gap>1)
	{
		gap = gap / 3 + 1;//跨度的取值方式
		for (int i = gap; i < n; i++)
		{
			int end = i - gap;
			temp = arr[i];
			while (temp < arr[end] && end >= 0)
			{
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = temp;
		}
	}
	
}

/*
*基本选择排序,升序，每趟记录最大值并将最大值与最后一个元素交换；
*有多种优化方式，比如在找最大值的同时也找最小值
*不稳定
*/
void SelectSort(int *arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int max = 0;
		for (int j = 1; j < n - i ; j++)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}
		if (max != n - i - 1)
		{
			int temp = arr[n-i-1];
			arr[n - i - 1] = arr[max];
			arr[max] = temp;
		}
	}
}

/*
*堆排序，不稳定
*
*/

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



/*
*快速插入排序  不稳定 
*递归
*/
int partion(int*arr, int left, int right)
{
	int prev = left - 1;
	int pcur = left;
	int key = arr[right - 1];
	while (pcur < right)
	{
		if (arr[pcur] < key&&++prev != pcur)
		{
			int temp = arr[pcur];
			arr[pcur] = arr[prev];
			arr[prev] = temp;
		}
		++pcur;
	}
	if (++prev != right - 1)
	{
		int temp = arr[right-1];
		arr[right-1] = arr[prev];
		arr[prev] = temp;
	}
	return prev;
}
void QuickSort(int *array, int start, int end)
{
	assert(array != NULL);
	int tmp = partion1(array, start, end);

	if (tmp > start + 1)
	{
		QuickSort(array, 0, tmp - 1);
	}
	if (tmp < end - 1)
	{
		QuickSort(array, tmp + 1, end);
	}
}


void Print(int *arr, int n)
{
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[10] = { 3,8,9,0,6,2,5,7,4,1 };

	InsertSort(arr,10);
	printf("插入排序：");
	Print(arr, 10);

	ShellSort(arr, 10);
	printf("希尔排序：");
	Print(arr, 10);

	SelectSort(arr, 10);
	printf("选择排序：");
	Print(arr, 10);

	QuickSort(arr, 1, 10);
	printf("快速排序：");
	Print(arr, 10);

	HeapSort(arr);
	printf("快速排序：");
	Print(arr, 10);

	system("pause");
	return 0;
}