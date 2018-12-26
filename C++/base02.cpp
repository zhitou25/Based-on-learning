#include<iostream>
#include<stdlib.h>

using namespace std;
//内存空间管理
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
	// 申请单个Test类型的空间
	Test* p1 = new Test;
	delete p1;
	//申请多个Test类型的空间
	Test *p2 = new Test[10];
	//delete[]所释放的字节数为10*sizeof(test)+1，表示申请空间的大小+用于存放申请元素个数所占用的一个字节
	delete[]p2;
}
void Test2()
{
	//p现在指向的只不过是与Test对象相同大小的一段空间，还不能算是一个对象，因为构造函数没有执行
	Test *p = (Test*)malloc(sizeof(Test));
	//定位new表达式在实际中一般是配合内存池使用。因为内存池分配出的内存没有初始化，所以如果是自定义
   //类型的对象，需要使用new的定义表达式进行显示调构造函数进行初始化。
	new(p) Test();
}

/*
*让一个类只能在堆上创建对象；
*创建对象有两个途径：1.调用构造函数   2.调用拷贝构造函数 
*封锁这两个途径
*/
class Test3 {
public:
	//提供在堆上创建对象的函数
	static Test3 *HeapCreate()
	{
		return new Test3;
	}
	
private:
	//声名构造函数和拷贝构造函数为私有(C++98)
	Test3() {};
	Test3(const Test3&) {};
	//C++11
	/*Test3(const Test3&)=delete;*/
};

/*
*让一个类只能在栈上创建对象；
*在堆上创建对象的途径：1.new  2.new[]  但new[]是对new多次使用，所以只需封锁new
*/
class Test4{
public:
	 Test4()
	 {}

private:
	void* operator new(size_t size){}//一般封锁了new，同时也封锁delete
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
