#include<iostream>
#include<stdlib.h>
#include<mutex>
#include<thread>
using namespace std;
//
///*
//*��������ص㣺
//*1.һ��������ֻ�ܴ���һ������
//*2.��������ɵ��������д���
//*3.�����������ⲿ�ṩʹ�ø�ʵ���ķ���
//*/
//
////����ģʽ������������ʱ����������ʵ������
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
////����ģʽ���߳�
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



//���̻߳����µ�����ģʽ
class Singleton
{
public:
	 static Singleton* GetInstance()
	{
		//ʹ��˫��У��������֤�̰߳�ȫ����Ϊ���ܴ��ڶ���߳�ͬʱ����single check
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
	//���յ���������Դ
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
	//����һ����̬��Ա�����������˳�ʱ�����Զ������������������ͷŵ�������
	static CGarbo Garbo;
private:
	Singleton()
	{}
	//������
	Singleton(const Singleton&);
	Singleton& operator=(Singleton const&);
	static mutex mutex;
	//����ʹ��volatileԭ�򲢷Ǳ������ڴ�ɼ��ԣ����ǽ�ָֹ���������Ż�
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