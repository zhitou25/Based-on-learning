/*
*�öѽ��TOP K���⣻
*��ȡ������С�ѣ�С������ѣ�
*����Ҫ��ȡǰk���������һ�����ʹ�СΪn���������飬�Ƚ�һ������k��Ԫ�ص�
*С�ѣ����ǿ����Ȱ�����ǰk��Ԫ�ص�������ǰk������������ѣ���Ȼ���
*m��m=k+1��������ʼ�����������Ԫ�أ������m�������ڶѶ��������߽�����
*���������µ���ΪС��
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