#include<iostream>
#include<vector>
#include<windows.h>
using namespace std;

int main()
{
	////Vector �����ʹ�ӡ
	//int a[] = { 1,2,3,4,5 }; 
	//vector<int>v1(a, a + sizeof(a) / sizeof(a[0]));
	vector<int>v2(6, 8);//6�����Ϳռ䣬ֵΪ8
	//vector<int>v3(v2.begin(), v2.end());//����������v3
	//vector<int>v4(v2);//��������

	//vector<int>::iterator it = v2.begin();
	//while (it != v2.end())//�����������ӡ
	//{
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;

	//for (unsigned int i = 0; i < v3.size(); i++)//���鷽ʽ��ӡ
	//{
	//	cout << v3[i] << " ";
	//  //cout << v3.at(i);
	//}
	//cout << endl;
	//
	//for (auto i : v4)//��Χfor��ӡ
	//{
	//	cout << i<<" ";
	//}
	//cout << endl;

	//v2.push_back(1);//β������
	//v2.push_back(3);

	//vector<int>::reverse_iterator rit = v2.rbegin();
	//while (rit != v2.rend())//�����������ӡ
	//{
	//	cout << *rit << " ";
	//	++rit;
	//}
	//cout << endl;
	//
	////capacity
	//unsigned int size = v2.size();//��ȡԪ�ظ���
	//unsigned int capa = v2.capacity();//��ȡ����
	//int ifempty = v2.empty();//����Ƿ�Ϊ��
	//cout << size << " " << capa << " " << ifempty << endl;
	//v2.resize(7,8);//���resize��ԭ��size���ұ�capacity��������չcapacity��Ȼ�󽫶����λ��ʹ�����õ��ַ���䣬�粻������Ĭ��Ϊ0������ֻ�ı�size�����ı�capacity��
	//v2.reserve(7);//����capacity��ֻ��Ҫ���õ�������ԭ���Ĵ�capacity�Ż�ı�
	//cout << v2.capacity() << endl;
	//
	////vector����ɾ�Ĳ�
	//v2.push_back(2);
	//v2.pop_back();//βɾ
	//v2._Pop_back_n(2);//βɾ2������
	//v2.push_back(4);
	//vector<int>::iterator pos = find(v2.begin(), v2.end(), 4);// ʹ��find����4����λ�õ�iterator
	//v2.insert(pos, 6);
	//pos = find(v2.begin(), v2.end(), 8);//��ǰ������ҵ�һ��8����λ�õ�iterator
	//v2.erase(pos);
	//v2.swap(v3);//v2��v3����
	//for (auto i : v2)//��Χfor��ӡ
	//{
	//	cout << i<<" ";
	//}
	//cout << endl;

	//vector��ʧЧ����
	v2.push_back(3);
	v2.push_back(9);//��ʱv2.size()=v2.capacity()
	vector<int>::iterator pos = v2.begin();
	/*vector<int>::iterator pos=v2.end();
	cout << v2.size() << " " << v2.capacity() << endl;
	v2.push_back(3);//end���صĵ���������֮����в���������޸��˵�������ʹ�õ�����ʧЧ*/
	v2.push_back(3);//��v2.capacity����ʱ�򣬷����ڴ濽�������еĵ���������ʧЧ
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