
//交换两个数，不创建第三个变量
void swap(int *a, int *b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}

//求取一个整数二进制序列中‘1’的个数 
int get_onenum(int *num)
{
	int count = 0;	while (*num)
	{
		*num &= *num - 1;
		count++;
	}
	return count;
}
//求最大公约数
int Gcd1(int a, int b)
{
	while (a*b)
	{
		if (a > b)
		{
			a -= b;
		}
		else
		{
			b -= a;
		}
	}
	return a == 0 ? b : a;
}
//求最小公倍数
int Gcd2(int a, int b)
{

	int temp1 = a;
	int temp2 = b;
	while (a*b)
	{
		if (a > b)
		{
			a %= b;
		}
		else
		{
			b %= a;
		}
	}
	return (temp1*temp2) / (a == 0 ? b : a);
}





