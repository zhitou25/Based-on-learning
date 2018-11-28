/*
*用堆解决TOP K问题；
*获取大数建小堆，小数建大堆；
*假如要获取前k个大的数，一个整型大小为n的整型数组，先建一个含有k个元素的
*小堆（我们可以先把数组前k个元素当作数组前k个大的数来建堆）；然后从
*m（m=k+1）个数开始遍历数组后序元素，如果第m个数大于堆顶，则两者交换，
*并将堆重新调整为小堆
*/



#include<stdio.h>
#include<stdlib.h>
void HeapAdjust(int *a,int parent, int size)
{
	if (!size)
	{
		return;
	}
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&a[child] > a[child + 1])
			child++;
		if (a[child] < a[parent])
		{
			int temp = a[parent];
			a[parent] = a[child];
			a[child] = temp;
		}
		parent = child;
		child = parent * 2 + 1;
	}
}

int main()
{
	int a[12] = { 3,8,91,0,23,26,54,76,49,16,12,1 };
	int size = sizeof(a) / sizeof(a[0]);
	int k = 3;
	int n = k;
	int parent = (k - 2) / 2;
	for (int i = parent; i >= 0; i--)
	{
		HeapAdjust(a, parent, k);
	}
	
	while (k<size)
	{

		if (a[k] > a[parent])
		{
			a[parent] = a[k];
			for (int i = parent; i >= 0; i--)
			{
				HeapAdjust(a, parent, n);
			}
		}
		k++;
	}
	for (int i = 0; i < 3; i++)
	{
		printf("%d ", a[i]);
	}
	system("pause");
	return 0;
}