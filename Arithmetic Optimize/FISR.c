
/*
*ƽ�����������㷨
*����C���sqrtʵ��(1.0f/sqrt(x))���˽���4����ʵ��ԭ����ţ�ٵ�����
*Ҳ��ƽ������һ���㷨������ִ�� x = x*(1.5f - (xhalf*x*x))��
*����y������(1.0f/sqrt(x))���õ��Ľ���������޽ӽ���������Ҫ�ľ��ȡ�
*�������ʵ�ֵ��㷨����Ϊ��Fast Inverse Square Root��, 
*��������ĵط����ں��������ʵ�ֲ�����һ�����صĳ�����0x5f3759df.
*�������˽������������ô�����Ŀ��Բο�http://h14s.p5r.org/2012/09/0x5f3759df.html
*/
#include<stdio.h>
#include<stdlib.h>


float FastInvSqrt(float x) {
	int count = 6;
	float xhalf = 0.5f * x;
	int i = *(int*)&x;         
	i = 0x5f3759df - (i >> 1); 
	x = *(float*)&i;
	while (count)
	{
		x = x*(1.5f - (xhalf*x*x));
		count--;
	}
	return x;
}
int main()
{
	float a=FastInvSqrt(0.25);
	printf("%f\n", a);
	system("pause");
	return 0;
}