
//����������������������������
void swap(int *a, int *b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}

//��ȡһ�����������������С�1���ĸ��� 
int get_onenum(int *num)
{
	int count = 0;	while (*num)
	{
		*num &= *num - 1;
		count++;
	}
	return count;
}
//�����Լ��
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
//����С������
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





