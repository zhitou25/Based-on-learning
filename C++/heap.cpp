#include<iostream>
#include<assert.h>
using namespace std;
/*
*�ѵĴ�����ʹ�����µ����ķ����������
*�ѵ����򣺶�����ʹ�õ��Ƕ�ɾ���ķ�ʽ�����Ѷ�Ԫ�غͶ�βԪ�ػ�����Ȼ���ٲ��ö����µ���
*�ķ������Զ���������ÿ�ζѵ�����Ԫ�ظ���Ҫ���μ�һ��ֱ��ֻʣһ��Ԫ�أ���ʱ�������
*�������������
*��β�Ĳ��룺����������漰���������⣬�������ڲ��õ��Ǿ�̬���飬����ʹ��a[10]��ֻ��ǰ
*�Ÿ���ֵ�����һ��Ԫ��Ĭ��Ϊ�㣬�ڶ�β����ʱ���ò����Ԫ��������������һ��Ԫ�أ�����
*ʾ��������Ļ�����ʽ��
*������õ��Ƕѵ����ϵ���
*/

class heap {
private:
	void swap(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}
	void HeapAdjust(int *arr, int parent, int size)
	{
		int child = parent * 2 + 1;
		while (child < size)
		{
			if (child + 1 < size&&arr[child] < arr[child + 1])
				child += 1;
			if (arr[child] > arr[parent])
				swap(arr[child], arr[parent]);

			parent = child;
			child = 2 * child + 1;
		}
	}
	void HeapInsertAdjust(int* arr, int size)
	{
		int parent = (size - 2) / 2;
		int child = 2 * parent + 1;
		//�жϲ���λ��
		if (child + 1 < size)
			child++;
		//��child��=0�����������ѭ��
		while (parent >= 0 )
		{
			if (arr[child] <= arr[parent])
				break;
			swap(arr[child], arr[parent]);
			child = parent;
			parent = (child-1) / 2;
		}
	}
public:
	void CreatHeap(int *arr, int size)
	{
		int parent = (size - 2) / 2;
		for (int i = parent; i >= 0; i--)
		{
			HeapAdjust(arr, i, size);
		}
	}
	
	void HeapInsertRear(int* arr, int size,int val)
	{
		arr[size-1] = val;
		HeapInsertAdjust(arr, size);
	}
	void HeapSort(int* arr, int size)
	{
		int isize = size;
		for (int i = 0; i < size - 1; i++)
		{
			swap(arr[0], arr[isize - 1]);
			HeapAdjust(arr,0, isize-1);
			isize--;
		}
	}
	void Printf(int* arr, int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

int main()
{
	heap h1;
	int arr[10] = { 3,8,1,0,6,2,5,7,4};
	h1.CreatHeap(arr, sizeof(arr) / sizeof(arr[0]));
	h1.Printf(arr, sizeof(arr) / sizeof(arr[0]));

	h1.HeapInsertRear(arr, sizeof(arr) / sizeof(arr[0]), 9);
	h1.Printf(arr, sizeof(arr) / sizeof(arr[0]));

	h1.HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	h1.Printf(arr, sizeof(arr) / sizeof(arr[0]));
	return 0;
}