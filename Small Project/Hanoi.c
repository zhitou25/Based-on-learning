#include<stdio.h>
#include<stdlib.h>
int move(char i, char j)
{
	printf("%cµΩ%c\n", i, j);
	return 0;
}
int hanoi(int n, char one, char two, char three)
{
	if (n==1)
		move(one, three);
	else
	{
		hanoi(n - 1, one, three, two);
		move(one, three);
		hanoi(n - 1, two, one, three);
	}
	return 0;
}
int main()
{
	int m;
	printf("«Î ‰»Îhanoi≈Ã ˝:");
	scanf_s("%d", &m);
	hanoi(m, 'a', 'b', 'c');
	system("pause");
	return 0;
}
