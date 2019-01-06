#include<iostream>
#include<list>
#include<vector>
#include<windows.h>
using namespace std;

template<class T>
void printList(const list<T>& s)
{
	for (const auto i : s)
		cout << i << "-->";
	cout << "NULL" << endl;
}
void test1()
{
	list<int>s1;
	list<int>s2(6,8);
	int array[] = { 1,2,3,4,5,6 };
	list<int>s3(array,array+sizeof(array)/sizeof(array[0]));
	list<int>s4{1,2,3,4,5,6};
	list<int>s5(s4.begin(), s4.end());
	list<int>s6(s5);
	printList(s2);
	printList(s3);
	printList(s4);
	printList(s5);
	printList(s6);
}

void test2()
{
	list<int>s7{1,3,5,7,9 };
	cout << s7.back() << endl;//����βԪ��
	cout << s7.front() << endl;//������Ԫ��
	s7.push_back(11);//β��Ԫ��
	s7.push_front(6);//ͷ��Ԫ��
	printList(s7);
	s7.reverse();//����
	printList(s7);
	s7.sort();//����
	printList(s7);
	s7.pop_back(); 
	s7.pop_front();
	printList(s7);

	s7.push_back(9);
	printList(s7);
	s7.unique();//ɾ���ظ�Ԫ��
	printList(s7);

}

int main()
{
	//test1();
	test2();
	 
	system("pasue");
	return 0;
}