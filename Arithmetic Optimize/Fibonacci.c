#include<stdio.h>
#include<stdlib.h>



int FibonacciFirst(int n)
{
	if (n < 3)
		return 1;

	return FibonacciFirst(n - 2) + FibonacciFirst(n - 1);
}
int FibonacciSecond(int first,int  second,int n )
{
	if (1==n)
		return first;

	return FibonacciSecond(second, first + second, n - 1);
}
int FibonacciThird( int n)
{
	int num1 = 1, num2 = 1;
	int num3 = num1 + num2;
	if (n < 3)
		return num1;
	n = n - 2;
	while (n--)
	{
		num1 = num2;
		num2 = num1+num2;
		num3 = num1 + num2;
	}
	return num3;
}
int main()
{
	printf("%d ", FibonacciFirst(6));
	printf("%d ", FibonacciSecond(1,1,6));
	printf("%d ", FibonacciThird(6));
	printf("\n ");
	system("pause");
	return 0;
}