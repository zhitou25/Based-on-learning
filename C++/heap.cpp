#include<iostream>
#include<assert.h>
using namespace std;
/*
*堆的创建：使用向下调整的方法创建大堆
*堆的排序：堆排序使用的是堆删除的方式，将堆顶元素和堆尾元素互换，然后再采用堆向下调整
*的方法来对堆重新排序，每次堆调整的元素个数要依次减一，直到只剩一个元素，此时完成排序
*大堆排序是升序
*堆尾的插入：插入操作会涉及到扩容问题，这里由于采用的是静态数组，所以使用a[10]里只对前
*九个赋值，最后一个元素默认为零，在堆尾插入时，用插入的元素来填充数组最后一个元素，仅演
*示插入操作的基本方式。
*插入采用的是堆的向上调整
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
		//判断插入位置
		if (child + 1 < size)
			child++;
		//无child！=0条件，造成死循环
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