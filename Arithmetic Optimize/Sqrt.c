#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//获取一个正整数的平方根
//获取val的平方根，t为精度

//二分法
double Sqrt(int val, double t)
{
	if (val < 0 || t<0)
		return 0;

	double left = 0;
	double right = val;
	double mid = (right + left) / 2;
	double offset = 2*t ;
	int count = 0;
	while (offset>t)
	{
		double sq = mid*mid;
		if (sq > val)
		{
			right = (left + right) / 2;
			offset = sq - val;
		}
		if (sq <= val)
		{
			left = (left + right) / 2;
			offset = val - sq;
		}
		mid = (left + right) / 2;
		count++;
	}
	printf("count:%d\n", count);
	return mid;
}
//牛顿迭代法
double SqrtIterator(int val,double t)
{
	double k = val;
	int count = 0;
	while (fabs(k*k-val)>t)
	{
		k=(k+val/k) / 2.0;
		count++;
	}
	printf("count:%d\n", count);
	return k;
}



int main()
{
	printf("%f\n", Sqrt(10, 0.00001));
	printf("%f\n", SqrtIterator(10, 0.00001));
	
	system("pause");
	return 0;
}