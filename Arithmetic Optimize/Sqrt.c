#include<stdio.h>
#include<stdlib.h>
//��ȡһ������ƽ����
//��ȡint val��ƽ������tΪ����

//���ַ�
double Sqrt(int val, double t)
{
	if (val < 0 || t<0)
		return 0;

	double left = 0;
	double right = val;
	double mid = (right + left) / 2;
	double m = t + 1;
	while (m>t)
	{
		double sq = mid*mid;
		if (sq > val)
		{
			right = (left + right) / 2;
			m = sq - val;
		}
		if (sq <= val)
		{
			left = (left + right) / 2;
			m = val - sq;
		}
		mid = (left + right) / 2;
	}
	return mid;
}
//ţ�ٵ�����

//�����½��������ٽ��ߣ�

//̩�չ�ʽչ��

int main()
{
	printf("%f\n", Sqrt(10, 0.00001));
	system("pause");
	return 0;
}