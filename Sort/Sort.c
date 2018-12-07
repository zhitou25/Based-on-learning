/*
*C���Եĸ��������㷨��
*�����㷨��ʱ�临�Ӷ����޲����ܳ���O(nlogn)
*���ݲ�ͬ�ĳ���ѡ����ʵ������㷨
*/

//������������Ϊ�ڲ�������ⲿ����


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

//��������int����
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
*��������
*  �ȶ�
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
*ϣ������(�Ż��Ĳ�������)
*���������һ��ң����ò�������˼�롣
*���ȶ�
*/
void ShellSort(int*arr, int n)
{
	int temp = 0;
	int gap = n;//��ʾ��ȴ�С
	while (gap>1)
	{
		gap = gap / 3 + 1;//��ȵ�ȡֵ��ʽ
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
*����ѡ������,����ÿ�˼�¼���ֵ�������ֵ�����һ��Ԫ�ؽ�����
*�ж����Ż���ʽ�������������ֵ��ͬʱҲ����Сֵ
*���ȶ�
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
*�����򣬲��ȶ�
*���öѵ����µ���
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
//������
void HeapSort(int *arr, int n)
{
	int j;
	int parent = ((n - 2) >> 1);
	//����
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
* ð��������С����
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
*���ٲ�������  ���ȶ�  ���нӽ�����ʱ������ʱ�临�ӶȽϴ�
*���Կ��Ų��ʺ���Ϊ�����������е����򷽷�
*/

/*
*����ѡȡ����Ԫ��Ϊ��Ԫ�ػ���βԪ�أ������л�������ʱ��ѡȡ�����м���ֵ��Сֵ�ĸ�������
*��������¿��ŵ�ʱ�临�Ӷ�̫�����Ըı�����Ԫ�ص�ѡȡ������
*����һ���м��ѡȡλ�ã�ͨ������λ�õıȽ���ѡȡ�м�Ԫ����Ϊ����Ԫ��
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
* ��������ָ�룬ͬʱ�Ӻ���ǰ�ʹ�ǰ���������ֱ������ָ���������ʾһ�����������
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
*�ڿӷ�
* �ͳ��������������ڽ�����Ԫ�ر�����������������Ԫ������λ�ÿ�ȱ��������������Ԫ���ṩλ��
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

* ���ڿ�������˼�룺ѡȡһ������Ԫ�أ�����Ԫ������Ԫ�ؾ�С���Ҳ��Ԫ�أ�

* �����������ͬʱ�Ӻ���ǰ�ʹ�ǰ���������ֱ������ָ��������

* �����������ֻ��ǰ�����������������Ԫ��С��Ԫ���ƶ�������֮ǰ��
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
	//�����е�Ԫ�ظ������ڵ���2���Ի��ֵ������������ٴν��п�������
	//��˵ݹ���ھ��������е�Ԫ�ظ���С��2
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
* ����ջ�Ŀ��ŷǵݹ�
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
*�鲢����   �ȶ�	�ʺ����ⲿ����
*�ݹ�
*��С����
*/

//���������������кϲ�Ϊһ������������
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
//�鲢�ݹ�
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

//�鲢�ǵݹ�
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
		Merge2(sourceArr, head, head + gap / 2 - 1, n - 1);//����ʣ��Ԫ�ظ�������gapʱ
		gap = gap << 1;
	}
	Merge2(sourceArr, 0, gap / 2 - 1, n - 1);//����gap���������Сʱ
}






//�ǱȽ�����
/*
*��������   �ȶ�	ʱ�䣺O(n+k)  �ռ䣺O(n+k)
*/

void CountSort(int *arr, int n)
{
	int min = arr[0];//������������Сֵ
	int max = arr[0];//�������������ֵ
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];

		if (arr[i] > max)
			max = arr[i];
	}
	int range = max - min + 1;//�����ռ�Ĵ�С
	int *count = (int *)malloc(range*sizeof(int));
	memset(count, 0, sizeof(int)*range);
	for (int i = 0; i < n; ++i)
	{
		count[arr[i] - min]++;//array[i]-min�ǽ�������Ӧ�������ռ���±꣬��¼���ֵĴ���
	}

	int index = 0;
	for (int i = 0; i < range; ++i)//���������ռ�
	{
		while (count[i]--)
		{
			arr[index++] = i + min;//���±괦������Ӧ��ԭ����
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
	printf("��������");
	Print(arr, 10);

	ShellSort(arr, 10);
	printf("ϣ������");
	Print(arr, 10);

	SelectSort(arr, 10);
	printf("ѡ������");
	Print(arr, 10);

	HeapSort(arr, 10);
	printf("������");
	Print(arr, 10);

	BubbleSort(arr,9);
	printf("ð������");
	Print(arr, 10);

	QuickSort1(arr, 0, 9);
	printf("���ٵݹ�����");
	Print(arr, 10);

	QuickSort2(arr, 10);
	printf("���ٷǵݹ�����");
	Print(arr, 10);

	MergeSort1(arr,arr,0,9);
	printf("�鲢�ݹ�����");
	Print(arr, 10);

	MergeSort2(arr, 10);
	printf("�鲢�ǵݹ�����");
	Print(arr, 10);*/

	CountSort(arr, 10);
	printf("��������");
	Print(arr, 10);

	system("pause");
	return 0;
}