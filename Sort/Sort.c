/*
*C语言的各种排序算法，
*排序算法的时间复杂度下限不可能超过O(nlogn)
*根据不同的场景选择合适的排序算法
*/

//根据数据量分为内部排序和外部排序


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>
#include<string.h>
#pragma warning(disable:4996)
#define size 100


typedef  int DataType;
typedef struct stack
{
	DataType *array;
	int top;
	int capacity;
}stack, *pstack;

void StackInit(pstack pt)
{
	pt->array = (DataType*)malloc(sizeof(int)*size);
	if (!pt->array)
		return;
	pt->top = 0;
	pt->capacity = size;
}
void StackPush(pstack pt, DataType data)
{
	if (pt->top == size)
	{
		pt->array = (DataType*)realloc(pt->array, sizeof(int)*size * 2);
	}
	pt->array[pt->top] = data;
	pt->top++;
}
void StackPop(pstack pt)
{
	if (!pt)
		return;
	if (pt->top > 0)
		pt->top--;
}
int StackTop(pstack pt)
{
	if (pt == NULL)
		return 0;
	return pt->array[pt->top - 1];
}
int StackEmpty(pstack pt)
{
	if (!pt)
		return 1;
	if (pt->top == 0)
		return 1;
	return 0;
}

//用于两个int交换
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
*插入排序
*  稳定
*/
void InsertSort(int*arr, int n)
{
	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		int end = i - 1;
		temp = arr[i];
		while (temp < arr[end] && end >= 0)
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
		for (int j = 1; j < n - i; j++)
		{
			if (arr[max] < arr[j])
			{
				max = j;
			}
		}
		if (max != n - i - 1)
		{
			int temp = arr[n - i - 1];
			arr[n - i - 1] = arr[max];
			arr[max] = temp;
		}
	}
}

/*
*堆排序，不稳定
*采用堆的向下调整
*/

void AdjustDown(int *arr, int parent, int n)
{
	int child = (parent * 2) + 1;
	while (child < n)
	{
		if (child + 1 < n&&arr[child + 1] > arr[child])
			child++;
		if (arr[child] <= arr[parent])
			break;
		int temp = arr[child];
		arr[child] = arr[parent];
		arr[parent] = temp;
		parent = child;
		child = 2 * parent + 1;
	}
}
//堆排序
void HeapSort(int *arr, int n)
{
	int j;
	int parent = ((n - 2) >> 1);
	//建堆
	for (j = parent; j >= 0; j--)
	{
		AdjustDown(arr, j, n);
	}
	int i;
	int temp;
	int num = n;
	while (n > 1)
	{
		for (i = n - 1; i > 0; i--)
		{
			temp = arr[0];
			arr[0] = arr[i];
			arr[i] = temp;
			n--;
			AdjustDown(arr, 0, n);
		}
	}
}
/*
* 冒泡排序，由小到大
*/
void BubbleSort(int *array, int n)
{
	int i, j, t;
	int flag = 0;
	for (i = 0; i < n; i++)
	{
		flag = 1;
		for (j = 0; j < n - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				flag = 0;
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
		if (1 == flag)
		{
			return;
		}
	}
}

/*
*快速插入排序  不稳定  序列接近有序时，快排时间复杂度较大，
*所以快排不适合作为基本有序序列的排序方法
*/

/*
*由于选取枢轴元素为首元素或者尾元素，在序列基本有序时，选取数组中极大值或极小值的概率增大
*这种情况下快排的时间复杂度太大，所以改变枢轴元素的选取方法，
*增加一个中间的选取位置，通过三个位置的比较来选取中间元素作为枢轴元素
*/

int GetMidNum(int *array, int left, int right)
{
	int mid = (left + ((right - left) >> 1));
	if (array[left] < array[right])
	{
		if (array[mid] < array[left])
			return left;
		else if (array[mid]>array[right])
			return right;
		else
			return mid;
	}
	else
	{
		if (array[mid] < array[right])
			return right;
		else if (array[mid]>array[left])
			return left;
		else
			return mid;
	}
}

/*
* 给定两个指针，同时从后往前和从前往后遍历，直至两个指针相遇则表示一次排序结束；
*/

int Partition1(int*arr, int left, int right)
{
	int start = left;
	int end = right;
	int key = arr[right];
	while (start != end)
	{
		while (arr[start] <= key&&start != end)
		{
			start++;
		}

		while (arr[end] >= key&&start != end)
		{
			end--;
		}
		Swap(&arr[start], &arr[end]);
	}
	if (start != right)
	{
		Swap(&arr[start], &arr[right]);
	}
	return start;
}
/*
*挖坑法
* 和常规做法区别在于将枢轴元素保存起来，并将枢轴元素所在位置空缺出来，给交换的元素提供位置
*/

int Partition2(int *arr, int head, int tail)
{
	int key = arr[head];
	while (head != tail)
	{
		while (arr[tail] >= key && head != tail)
		{
			tail--;
		}
		arr[head] = arr[tail];
		while (arr[head] <= key && head != tail)
		{
			head++;
		}
		arr[tail] = arr[head];
	}
	arr[head] = key;
	return head;

}
/*

* 基于快速排序思想：选取一个枢轴元素，枢轴元素左侧的元素均小于右侧的元素；

* 常规的做法是同时从后往前和从前往后遍历，直至两个指针相遇；

* 下面的做法是只从前往后遍历，将比枢轴元素小的元素移动到枢轴之前。
*/
int Partition3(int *arr, int head, int tail)
{
	int temp;
	int i, j;
	int pivot = head;
	for (i = head + 1; i <= tail; i++)
	{
		if (arr[i] < arr[pivot])
		{
			temp = arr[i];
			for (j = i - 1; j >= pivot; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[pivot++] = temp;
		}
	}
	return pivot;
}

void QuickSort1(int *arr, int head, int tail)
{
	assert(arr != NULL);
	int pivot = Partition3(arr, head, tail);
	//子序列的元素个数大于等于2，对划分的两个字序列再次进行快速排序；
	//因此递归出口就是子序列的元素个数小于2
	if (head != pivot&&head != pivot - 1)
	{
		QuickSort1(arr, head, pivot - 1);
	}
	if (pivot != tail&&pivot + 1 != tail)
	{
		QuickSort1(arr, pivot + 1, tail);
	}
}

/*
* 利用栈的快排非递归
*/
void QuickSort2(int *array, int n)
{
	assert(array);
	stack p;
	StackInit(&p);
	StackPush(&p, n);
	StackPush(&p, 0);
	while (!StackEmpty(&p))
	{
		int head = StackTop(&p);
		StackPop(&p);

		int tail = StackTop(&p);
		StackPop(&p);

		if (tail - head > 1)
		{
			int div = Partition2(array, head, tail);

			StackPush(&p, head);
			StackPush(&p, div + 1);

			StackPush(&p, div);
			StackPush(&p, tail);
		}
	}
}

/*
*归并排序   稳定	适合做外部排序
*递归
*从小到大
*/

//将两个有序子序列合并为一个有序子序列
void Merge1(int *sourceArr, int *targetArr, int head, int mid, int tail)
{
	int i, j, k;
	i = head;
	k = head;
	j = mid + 1;
	for (; i <= mid&&j <= tail; k++)
	{
		if (sourceArr[i] <= sourceArr[j])
		{
			targetArr[k] = sourceArr[i++];
		}
		else
		{
			targetArr[k] = sourceArr[j++];
		}
	}
	if (i <= mid)
	{
		for (; k <= tail; k++)
		{
			targetArr[k] = sourceArr[i++];
		}
	}
	if (j <= tail)
	{
		for (; k <= tail; k++)
		{
			targetArr[k] = sourceArr[j++];
		}
	}
}
//归并递归
void MergeSort1(int *sourceArr, int *targetArr, int head, int tail)
{
	int mid = head + ((tail - head) >> 1);
	int *temp = (int *)malloc(sizeof(int)*(tail - head + 1));
	if (head == tail)
	{
		targetArr[head] = sourceArr[head];
	}
	else
	{
		MergeSort1(sourceArr, temp, head, mid);
		MergeSort1(sourceArr, temp, mid + 1, tail);
		Merge1(temp, targetArr, head, mid, tail);
	}
}

//归并非递归
void Merge2(int *sourceArr, int head, int mid, int tail)
{
	int i, j, k;
	i = head;
	k = 0;
	j = mid + 1;
	int *targetArr;
	targetArr = (int *)malloc(sizeof(int)*(tail - head + 1));

	for (; i <= mid&&j <= tail; k++)
	{
		if (sourceArr[i] > sourceArr[j])
		{
			targetArr[k] = sourceArr[j++];
		}
		else
		{
			targetArr[k] = sourceArr[i++];
		}
	}

	if (i <= mid)
	{
		for (; k < tail - head + 1; k++)
		{
			targetArr[k] = sourceArr[i++];
		}
	}

	if (j <= tail)
	{
		for (; k < tail - head + 1; k++)
		{
			targetArr[k] = sourceArr[j++];
		}
	}

	for (i = head, k = 0; i <= tail; i++, k++)
	{
		sourceArr[i] = targetArr[k];
	}
}
void MergeSort2(int*sourceArr, int n)
{
	int head;
	int gap = 2;
	while (gap <= n)
	{
		for (head = 0; head + gap <= n; head += gap)
		{
			Merge2(sourceArr, head, head + gap / 2 - 1, head + gap - 1);
		}
		Merge2(sourceArr, head, head + gap / 2 - 1, n - 1);//处理当剩余元素个数不足gap时
		gap = gap << 1;
	}
	Merge2(sourceArr, 0, gap / 2 - 1, n - 1);//处理当gap大于数组大小时
}






//非比较排序
/*
*计数排序   稳定	时间：O(n+k)  空间：O(n+k)
*/

void CountSort(int *arr, int n)
{
	int min = arr[0];//保存数组中最小值
	int max = arr[0];//保存数组中最大值
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];

		if (arr[i] > max)
			max = arr[i];
	}
	int range = max - min + 1;//辅助空间的大小
	int *count = (int *)malloc(range*sizeof(int));
	memset(count, 0, sizeof(int)*range);
	for (int i = 0; i < n; ++i)
	{
		count[arr[i] - min]++;//array[i]-min是将该数对应到辅助空间的下标，记录出现的次数
	}

	int index = 0;
	for (int i = 0; i < range; ++i)//遍历辅助空间
	{
		while (count[i]--)
		{
			arr[index++] = i + min;//将下标处的数对应回原数组
		}
	}
	free(count);
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

	/*InsertSort(arr,10);
	printf("插入排序：");
	Print(arr, 10);

	ShellSort(arr, 10);
	printf("希尔排序：");
	Print(arr, 10);

	SelectSort(arr, 10);
	printf("选择排序：");
	Print(arr, 10);

	HeapSort(arr, 10);
	printf("堆排序：");
	Print(arr, 10);

	BubbleSort(arr,9);
	printf("冒泡排序：");
	Print(arr, 10);

	QuickSort1(arr, 0, 9);
	printf("快速递归排序：");
	Print(arr, 10);

	QuickSort2(arr, 10);
	printf("快速非递归排序：");
	Print(arr, 10);

	MergeSort1(arr,arr,0,9);
	printf("归并递归排序：");
	Print(arr, 10);

	MergeSort2(arr, 10);
	printf("归并非递归排序：");
	Print(arr, 10);*/

	CountSort(arr, 10);
	printf("计数排序：");
	Print(arr, 10);

	system("pause");
	return 0;
}