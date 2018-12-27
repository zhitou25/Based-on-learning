#include<iostream>
#include<stdlib.h>
#include<mutex>
#include<thread>
using namespace std;
//
///*
//*单例类的特点：
//*1.一个单例类只能创建一个对象
//*2.这个对象由单例类自行创建
//*3.单例类需向外部提供使用改实例的方法
//*/
//
////饿汉模式：程序在启动时将单例对象实例化好
//
//class Singleton {
//public:
//	static Singleton* GetInstance()
//	{
//		return &m_instance;
//	}
//
//private:
//	Singleton()
//	{}
//	Singleton(const Singleton&);
//
//
//	static Singleton m_instance;
//};
//Singleton Singleton::m_pinstance;
//
//
//
////懒汉模式单线程
//
//class Singleton
//{
//public:
//	static Singleton* GetInstance()
//	{
//		if (nullptr == m_pinstance)
//		{
//			m_pinstance = new Singleton;
//		}
//		return m_pinstance;
//	}
//private:
//	Singleton()
//	{}
//	Singleton(const Singleton&);
//	static  Singleton* m_pinstance;
//};
//Singleton* Singleton::m_pinstance=nullptr;



//多线程环境下的懒汉模式
class Singleton
{
public:
	 static Singleton* GetInstance()
	{
		//使用双重校验锁来保证线程安全；因为可能存在多个线程同时进入single check
		if (nullptr == m_pinstance)//single check
		{
			mutex.lock();
			if (nullptr == m_pinstance)//double check
			{
				m_pinstance = new Singleton();
				mutex.unlock();
			}
		}
		return m_pinstance;
	}
	//回收单例对象资源
	class CGarbo {
	public:
		~CGarbo()
		{
			if (Singleton::m_pinstance)
			{
				delete m_pinstance;
			}
		}
	};
	//定义一个静态成员变量，程序退出时，会自动调用它的析构函数释放单例对象
	static CGarbo Garbo;
private:
	Singleton()
	{}
	//防拷贝
	Singleton(const Singleton&);
	Singleton& operator=(Singleton const&);
	static mutex mutex;
	//这里使用volatile原因并非保持其内存可见性，而是禁止指令重排序优化
	 static  Singleton* m_pinstance;
};
 Singleton* Singleton::m_pinstance = nullptr;
mutex Singleton::mutex;
Singleton::CGarbo Garbo;

void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}


int main()
{
	thread t1(func, 10);
	thread t2(func, 10);
	t1.join();
	t2.join();
	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;
	return 0;
}