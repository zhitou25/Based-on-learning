#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

int main()
{
	////Vector 创建和打印
	//int a[] = { 1,2,3,4,5 }; 
	//vector<int>v1(a, a + sizeof(a) / sizeof(a[0]));
	vector<int>v2(6, 8);//6个整型空间，值为8
	//vector<int>v3(v2.begin(), v2.end());//迭代器构造v3
	//vector<int>v4(v2);//拷贝构造

	//vector<int>::iterator it = v2.begin();
	//while (it != v2.end())//正向迭代器打印
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;

	//for (unsigned int i = 0; i < v3.size(); i++)//数组方式打印
	//{
	//	cout << v3[i] << " ";
	//  //cout << v3.at(i);
	//}
	//cout << endl;
	//
	//for (auto i : v4)//范围for打印
	//{
	//	cout << i<<" ";
	//}
	//cout << endl;

	//v2.push_back(1);//尾插数据
	//v2.push_back(3);

	//vector<int>::reverse_iterator rit = v2.rbegin();
	//while (rit != v2.rend())//反向迭代器打印
	//{
	//	cout << *rit << " ";
	//	++rit;
	//}
	//cout << endl;
	//
	////capacity
	//unsigned int size = v2.size();//获取元素个数
	//unsigned int capa = v2.capacity();//获取容量
	//int ifempty = v2.empty();//检查是否为空
	//cout << size << " " << capa << " " << ifempty << endl;
	//v2.resize(7,8);//如果resize比原来size大且比capacity大，首先扩展capacity，然后将多余的位置使用设置的字符填充，如不设置则默认为0。否则只改变size，不改变capacity。
	//v2.reserve(7);//设置capacity，只有要设置的容量比原来的大，capacity才会改变
	//cout << v2.capacity() << endl;
	//
	////vector的增删改查
	//v2.push_back(2);
	//v2.pop_back();//尾删
	//v2._Pop_back_n(2);//尾删2个数据
	//v2.push_back(4);
	//vector<int>::iterator pos = find(v2.begin(), v2.end(), 4);// 使用find查找4所在位置的iterator
	//v2.insert(pos, 6);
	//pos = find(v2.begin(), v2.end(), 8);//从前到后查找第一个8所在位置的iterator
	//v2.erase(pos);
	//v2.swap(v3);//v2与v3交换
	//for (auto i : v2)//范围for打印
	//{
	//	cout << i<<" ";
	//}
	//cout << endl;

	//vector的失效问题
	v2.push_back(3);
	v2.push_back(9);//此时v2.size()=v2.capacity()
	vector<int>::iterator pos = v2.begin();
	/*vector<int>::iterator pos=v2.end();
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.push_back(3);//end返回的迭代器操作之后进行插入操作，修改了迭代器，使得迭代器失效*/
	v2.push_back(3);//当v2.capacity满的时候，发生内存拷贝，所有的迭代器均会失效
	while (pos != v2.end())
	{
		if (*pos % 2 == 0)
		{
			pos=v2.erase(pos);
		}
		else
		{
			++pos;
		}
	}
	for (auto i : v2)
	{
	cout << i << " ";
	}
	system("pause");
	return 0;
}