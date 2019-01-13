
//n!末尾连续零的个数
int Caln(int n)
{
	if (n < 5)
		return 0;
	return n / 5 + Caln(n / 5);
}