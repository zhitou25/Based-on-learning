#include<iostream>
#include<stdlib.h>

using namespace std;
//�ڴ�ռ����
class Test
{
public:
	Test(int data=1)
		: _data(data)
	{
		cout << "Test():" << this << endl;
	}
	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};
void Test1()
{
	// ���뵥��Test���͵Ŀռ�
	Test* p1 = new Test;
	delete p1;
	//������Test���͵Ŀռ�
	Test *p2 = new Test[10];
	//delete[]���ͷŵ��ֽ���Ϊ10*sizeof(test)+1����ʾ����ռ�Ĵ�С+���ڴ������Ԫ�ظ�����ռ�õ�һ���ֽ�
	delete[]p2;
}
void Test2()
{
	//p����ָ���ֻ��������Test������ͬ��С��һ�οռ䣬����������һ��������Ϊ���캯��û��ִ��
	Test *p = (Test*)malloc(sizeof(Test));
	//��λnew���ʽ��ʵ����һ��������ڴ��ʹ�á���Ϊ�ڴ�ط�������ڴ�û�г�ʼ��������������Զ���
   //���͵Ķ�����Ҫʹ��new�Ķ�����ʽ������ʾ�����캯�����г�ʼ����
	new(p) Test();
}

/*
*��һ����ֻ���ڶ��ϴ�������
*��������������;����1.���ù��캯��   2.���ÿ������캯�� 
*����������;��
*/
class Test3 {
public:
	//�ṩ�ڶ��ϴ�������ĺ���
	static Test3 *HeapCreate()
	{
		return new Test3;
	}
	
private:
	//�������캯���Ϳ������캯��Ϊ˽��(C++98)
	Test3() {};
	Test3(const Test3&) {};
	//C++11
	/*Test3(const Test3&)=delete;*/
};

/*
*��һ����ֻ����ջ�ϴ�������
*�ڶ��ϴ��������;����1.new  2.new[]  ��new[]�Ƕ�new���ʹ�ã�����ֻ�����new
*/
class Test4{
public:
	 Test4()
	 {}

private:
	void* operator new(size_t size){}//һ�������new��ͬʱҲ����delete
	void operator delete(void *ptr){}
};

int main()
{
	//Test1();
	//Test2();
	//Test3 *p = Test3::HeapCreate();
	//Test4 *p=new Test4;
	//Test5 *p=Test5::GetInstance();

 	system("pause");
	return 0;
}
