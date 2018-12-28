#include<iostream>
using namespace std;
template<class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
//编译器由模板自动生成函数的过程叫做模板的实例化，生成的函数叫做模板函数
//通过 模板名<类型名1,类型名2，...>(显式定义)这种方式告诉编译器应该如何实例化模板函数template<class T>
template<class T>
T sum(int a)
{
	return a + 1;
}
//模板函数可以不只有一个参数
template<class T1,class T2>
T1 Print(T1 arg1, T2 arg2)
{
	cout << arg1 << " " << arg2 << endl;
	return arg1;
}
//模板重载
void test(int num1,int num2)
{
	cout << "noraml:"<< endl;
}

template<class T>
void test(T num1,T num2)
{
	cout << "templete:" << endl;
}

template<class T1,class T2>
void test(T1 num1,T2 num2)
{
	cout << "adjust templete:"  << endl;
}


int main()
{
	
	/*int a = 1, b = 2;
	Swap(a, b);
	cout << a << " " << b << endl;
	double c = 1.2, d = 1.0;
	Swap(c, d);
	cout << c << " " << d << endl;
	char e = 'E', f = 'F';
	Swap(e, f);
	cout << e << " " << f << endl;
	

	cout << sum<double>(4) / 2 << endl;

	int arg1 = 2;
	char*arg2 = "HELLO";
	cout << Print(arg1, arg2) << endl;*/

	//test(1, 2);
	test(1.2, 2);

	system("pause");
	return 0;
}

