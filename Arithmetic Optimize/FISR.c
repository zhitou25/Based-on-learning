
/*
*平方根倒数速算法
*比用C库的sqrt实现(1.0f/sqrt(x))快了将近4倍。实现原理是牛顿迭代，
*也是平方根的一般算法，反复执行 x = x*(1.5f - (xhalf*x*x))；
*其中y趋向于(1.0f/sqrt(x))，拿到的结果可以无限接近于我们想要的精度。
*这个函数实现的算法被称为‘Fast Inverse Square Root’, 
*而它神奇的地方在于函数里面的实现采用了一个神秘的常数：0x5f3759df.
*向深入了解这个常数是怎么得来的可以参考http://h14s.p5r.org/2012/09/0x5f3759df.html
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