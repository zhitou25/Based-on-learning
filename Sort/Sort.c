/*
*C���Եĸ��������㷨��
*�����㷨��ʱ�临�Ӷ����޲����ܳ���O(nlogn)
*���ݲ�ͬ�ĳ���ѡ����ʵ������㷨
*/

//������������Ϊ�ڲ�������ⲿ����


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
/*
*��������
*  �ȶ�
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
*�����򣬲��ȶ�
*
*/

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



/*
*���ٲ�������  ���ȶ� 
*�ݹ�
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
	printf("��������");
	Print(arr, 10);

	ShellSort(arr, 10);
	printf("ϣ������");
	Print(arr, 10);

	SelectSort(arr, 10);
	printf("ѡ������");
	Print(arr, 10);

	QuickSort(arr, 1, 10);
	printf("��������");
	Print(arr, 10);

	HeapSort(arr);
	printf("��������");
	Print(arr, 10);

	system("pause");
	return 0;
}