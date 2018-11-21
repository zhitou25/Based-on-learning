#include<stdio.h>
#include<stdlib.h>

void BubbleSort(int *array)
{
	int i, j,t;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
	}
}
int main()
{
	int i;
	int a[10] = { 12,23,43,65,212,454,67,87,45,32 };
	BubbleSort(a);
	for (i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}