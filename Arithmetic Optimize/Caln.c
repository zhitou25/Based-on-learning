
//n!ĩβ������ĸ���
int Caln(int n)
{
	if (n < 5)
		return 0;
	return n / 5 + caln(n / 5);
}