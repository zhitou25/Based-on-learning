#include<iostream>
#include<string>
#include<assert.h>
#include<string>
#pragma warning(disable:4996)
#include<assert.h>
using namespace std;

//string���ģ��ʵ��

////��ͳ�汾
//class String {
//public:
//	String(const char* str="")
//	{
//		if (str == nullptr)
//		{
//			assert(false);
//			return;
//		}
//		m_str = new char[strlen(str) + 1];
//		strcpy(m_str, str);
//	}
//
//	String(const String& s)
//	{
//		m_str = new char[strlen(s.m_str) + 1];
//		strcpy(m_str, s.m_str);
//	}
//	
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			char* str = new char[strlen(s.m_str) + 1];
//			strcpy(str, s.m_str);
//			delete[] m_str;//����һ����ֵ����������this�����Ѿ����ɣ����пռ�����ݣ����޸����ָ��֮ǰ�������ԭ��������
//			m_str = str;
//		}
//		return *this;
//	}
//	
//	~String()
//	{
//		if (m_str)
//		{
//			delete[]m_str;
//			m_str = nullptr;
//		}
//	}
//	friend ostream & operator<<(ostream & _cout, const String & ret);
//private:
//	char* m_str;
//};
//
//ostream & operator<<(ostream & _cout, const String & ret)
//{
//	_cout << ret.m_str; 
//	return _cout;
//}

//ǳ���������ü���
class String {
public:
	String(const char* str="")
		:m_str(new char[strlen(str) + 1])
		,m_pcount(new int(1))
	{
		strcpy(m_str, str);
	}
	String(const String& str)
	{
		if (this != &str)
		{
			m_str=str.m_str;
			m_pcount = str.m_pcount;
			++(*m_pcount);
		}
	}
	String& operator=(const String& str)
	{
		m_str = str.m_str;
		m_pcount = str.m_pcount;
		++(*m_pcount);
		return *this;
	}
	String& operator=(const char*str)
	{
			char* ptr = new char[strlen(str) + 1];
			m_str = ptr;
			strcpy(m_str, str);
			int *new_count = new int(1);
			int *old_count = new int(0);
			old_count = m_pcount;
			m_pcount=new_count;
			--(*old_count);
		return *this;
	}
	~String()
	{
		if (*m_pcount == 0)
		{
			delete[]m_str;
			m_str = nullptr;
			delete m_pcount;
			m_pcount = nullptr;
		}
	}
	friend ostream& operator<<(ostream&_cout, const String& ret);
private:
	char* m_str;
	int *m_pcount;
};

ostream & operator<<(ostream & _cout, const String & ret)
{
	_cout << ret.m_str;
	return _cout;
}

////�ִ��汾
//class String {
//public:
//	String(const char* str = "")
//	{
//		if (str == nullptr)
//		{
//			assert(false);
//			return;
//		}
//		m_str = new char[strlen(str) + 1];
//		strcpy(m_str, str);
//	}
//
//	String(const String& s)
//		:m_str(nullptr)//�����m_str��ʼ�����Է��ͷ����ֵ�ռ�
//	{
//		String temp(s.m_str);
//		swap(m_str, temp.m_str);
//	}
//
//	String& operator=(String s)//����ʹ�����÷�ʽ�������s���ᷢ�����죬ʹ�ý�����sָ��Ŀռ�ı�
//	{
//		if (this != &s)
//		{
//			swap(m_str, s.m_str);
//		}
//		return *this;
//	}
//	~String()
//	{
//		if (m_str)
//		{
//			delete[]m_str;
//			m_str = nullptr;
//		}
//	}
//	friend ostream & operator<<(ostream & _cout, const String & ret);
//private:
//	char* m_str;
//};
//
//ostream & operator<<(ostream & _cout, const String & ret)
//{
//	_cout << ret.m_str;
//	return _cout;
//}


int main()
{
	String s1("hello!");
	cout << s1 << endl;
	String s2(s1);
	cout << s2 << endl;
	String s3;
	s3 = s2;
	cout << s3 << endl;
	s3 = "TOP";
	system("pause");
	return 0;
} 