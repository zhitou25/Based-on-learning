#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int int_cmp(const void*s1, const void* s2)//对整形进行排序
{
	return *(int*)s1 > *(int*)s2;
}
int char_cmp(const void*s1, const void* s2)//对字符进行排序
{
	return *(char*)s1 > *(char*)s2;
}
int str_cmp(const void*s1, const void*s2)//对字符串进行排序
{
	return strcmp((char*)s1, (char*)s2);
}
void swap(void*p, void* q, int count)
{
	for (int i = 0; i < count; i++)
	{
		char temp = *((char*)p + i);
		*((char*)p + i) = *((char*)q + i);
		*((char*)q + i) = temp;
	}
}
void my_qsort(void*base, int count, int size, int(*str_cmp)(void*p, void*q))
{
	int i = 0;
	int j = 0;
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - 1 - i; j++)
		{
			if (str_cmp((char*)base + j*size, (char*)base + (j + 1)*size)>0)
			{
				swap(((char*)base + j*size), ((char*)base + (j + 1)*size), size);
			}
		}
	}
}
void qint_cmp()
{
	int arr1[] = { 1,3,5,7,9,2,4,6,8,0 };
	my_qsort(arr1, sizeof(arr1) / sizeof(arr1[0]), sizeof(int), int_cmp);
	for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");
}
void qchar_cmp()
{
	char arr2[] = { 'e','d','c','b','a','f' };
	my_qsort(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(char), char_cmp);
	for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
	{
		printf("%c ", arr2[i]);
	}
	printf("\n");
}
void qstr_cmp()
{
	char arr3[5][5] = { "bcbb","dwdd","cvcc","aaac","aaab" };
	my_qsort(arr3, 5, sizeof(arr3[0]), str_cmp);
	for (int i = 0; i < 5; i++)
	{
		printf("%s ", arr3[i]);
	}
	printf("\n");
}
int main()
{
	int choice;
	while(1)
	{
	printf("please choose:");
	scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			qint_cmp();
			break;
		case 2:
			qchar_cmp();
			break;
		case 3:
			qstr_cmp();
			break;
		default:
			printf("error!\n");
			break;
		}
	}
	system("pause");
	return 0;
}



