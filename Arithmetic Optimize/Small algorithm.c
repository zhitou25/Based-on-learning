
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





