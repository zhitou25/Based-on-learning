#include<iostream>
using namespace std;
template<class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
//��������ģ���Զ����ɺ����Ĺ��̽���ģ���ʵ���������ɵĺ�������ģ�庯��
//ͨ�� ģ����<������1,������2��...>(��ʽ����)���ַ�ʽ���߱�����Ӧ�����ʵ����ģ�庯��template<class T>
template<class T>
T sum(int a)
{
	return a + 1;
}
//ģ�庯�����Բ�ֻ��һ������
template<class T1,class T2>
T1 Print(T1 arg1, T2 arg2)
{
	cout << arg1 << " " << arg2 << endl;
	return arg1;
}
//ģ������
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

