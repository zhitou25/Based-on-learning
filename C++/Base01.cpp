#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
#pragma warning(disable:4996)


//ǳ�����븳ֵ�����
class Quick{
public:
	Quick(int rear=1, int imag=1)
	{
		_rear = rear;
		_imag = imag;
	}
	Quick(const Quick& ret)
	{
		_rear = ret._rear;
		_imag = ret._imag;
		cout << "copy" << endl;
	}
		Quick& operator=(const Quick ret)
	{
		_rear = ret._rear;
		_imag = ret._imag;
		cout << "operator" << endl;
		return *this;
	}
private:
	int _rear;
	int _imag;
};


//��̬��Ա������ǳ����
class Hyottoko {
public:
	Hyottoko()
	{
		m_count++;
	}
	Hyottoko(const Hyottoko& data)
	{
		m_count++;
	}
	static int getCount()
	{
		return m_count;
	}
	~Hyottoko()
	{
		m_count--;
	}
private:
	int *m_next;
	int m_data;
	static int m_count;
};
int Hyottoko::m_count = 0;

//���
class String {
public:
	String(char*str = NULL)
	{
		m_str = new char[strlen(str)+1];
		strcpy(m_str, str);
	}
	String(String& str)
	{
		m_str = new char[strlen(str.m_str)+1];
		strcpy(m_str, str.m_str);
	}
	~String()
	{
		if (m_str)
			delete[]m_str;
	}
private:
	char *m_str;
};
//���������
class date {
public:	
   date(int year=2)
	 :m_year(year)
 {
 }
 //��+������
 date& operator+(int num)
 {
	 m_year += num;
	 return *this;
 }
 //��ǰ��++������
 date& operator++()
 {
	 ++m_year;
	 return *this;
 }
 //������++������
 const date& operator++(int)
 {
	 date temp = *this;
	 ++(*this);
	 return temp;
 }
 //��&�����أ�һ�㲻��Ҫ��������Ҫ����ָ����ַ��
 date* operator&()
 {
	 return this;
 }
 date &operator=(int num)
 {
	 m_year = num;
	 return *this;
 }
void printf()
 {
	 cout << m_year << endl;
 }
//��Ԫ��������
friend date operator+(int num, const date& ret);//����int+date
friend ostream & operator<<(ostream & _cout, const date & ret);//����<<
private:
	int m_year;
};
//��Ԫ��������
date operator+(int num, const date& ret)
{
	return date(ret.m_year + num);
}
ostream & operator<<(ostream & _cout, const date & ret)
{
	_cout << ret.m_year; 
	return _cout;
}
int main()
{
	date s1;
	s1 = 5 + s1;
	cout << s1;
	system("pause");
	return 0;
}



