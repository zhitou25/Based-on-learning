#include<stdio.h>
#include<stdlib.h>

void BubbleSort1(int *array)
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
void BubbleSort2(int *array)
{
	int i, j, t;
	int true=0;
	for (i = 0; i < 9; i++)
	{
		true = 1;
		for (j = 0; j < 9 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				 true = 0;
				t = array[j];
				array[j] = array[j + 1];
				array[j + 1] = t;
			}
		}
		if (1 == true)
		{
			return;
		}
	}
}

int main()
{
	int i;
	int a[10] = { 12,23,43,65,212,454,67,87,45,32 };
	BubbleSort2(a);
	for (i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}