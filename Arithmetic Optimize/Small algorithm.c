
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





