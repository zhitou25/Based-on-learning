#include<iostream>
#include<string>
using namespace std;
//�̳еĻ�����ʽ�͹���
#if 0
class Person{
public:
	void Print()
	{
		cout << "name:"<<_name << endl;
		cout <<"age:"<< _age << endl;
	}
	
private:
	string _name="tom";
	int _age = 18;
protected:
	void top()
	{
		cout << "protected" << endl;
	}
};

class Student : public Person {
public:
	void Print()
	{
		Person::Print();
		Person::top();
		cout << "num:" << num << endl;
	}
 
private:
	char num[15]="201506022034";
};

struct Teacher : Person {
public:
	void Print()
	{
		Person::Print();
		cout << "num:" << num << endl;
	}

private:
	char num[15] = "38241502";
};

int main()
{
	Student s;
	Teacher t;
	
	s.Print();
	t.Print();
	 return 0;
}
#endif

#if 0
//ʵ��һ�����ܱ��̳е���

//C++98���캯��˽�л�
class NOInherit {
public:
	static NOInherit GetInstance()
	{
		return NOInherit();
	}
private:
	NOInherit()
	{}
};
//C++11ʹ�ùؼ���final
class NOInherit final{};
#endif

class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name; // ����
};
class Student : public Person
{

protected:
	int _stuNum; // ѧ��
};
void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	//cout << s._stuNum << endl;//�˴��ᱨ��
}
void main()
{
	Person p;
	Student s;
	Display(p, s);

	system("pause");
}