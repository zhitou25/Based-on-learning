#include<iostream>
#include<string>
using namespace std;


int main()
{/*
	//string ��������   VS��sizeof(string)=28
	string s1;//����һ���ַ���s1
	string s2 = "hello!";//��C��ʽ�ַ�������string�����s2
	string s3(10, 'c');//��10���ַ�'c'����string�����s3
	string s4(s2);//��s2������s4���г�ʼ��
	string s5(s3,5);//��s3��ǰ����ַ�����s5

	//string��������������
	cout << s2.length() << endl;//��ȡs2����Ч����(������'\0')
	cout << s2.capacity() << endl;//s2�ռ��ܴ�С
	cout << s2.size() << endl;//��length����һ�£�size�Ĵ�����Ϊ�˺����������ӿڱ���ͳһ
	cout << s2 << endl;//string�����֧��ʹ��cin coutֱ���������
	s2.clear();//��s�е��ַ�����գ�ע�����ʱֻ�ǽ�size���㣬�����ı�ڲ�ռ��С
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	cout << s2.size() << endl;
	s2 = "hello!";
	s2.resize(10, 'c');//��s2����ЧԪ�ظ�����Ϊ10���������λʹ���ַ�c���
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.resize(15);//�ı�s2��ЧԪ�ظ���Ϊ15�������λ��ȱʡֵ'\0'���
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.reserve(16);//ΪstringԤ���ռ䣬���ı���ЧԪ�ظ�������reserve�Ĳ���С��s2�ײ�ռ��Сʱ�����ı���ײ�ռ��С
	cout << s2.capacity() << endl;
	s3 = "hello!";//ֱ�Ӷ�s3�����ݽ����޸�
	s3[1] = 'h';
	cout << s3 << endl;

	string str;
	str.append("hello"); // ��str��׷��һ���ַ�"hello"
	str.push_back(' '); // ��str�����ո�
	str += "wor"; // ��str��׷��һ���ַ�'b' 
	str += "ld"; // ��str��׷��һ���ַ���"it"
	cout << str << endl;
	cout << str.c_str() << endl; //��c���Եķ�ʽ��ӡ�ַ���,str.c_str()��������Ϊconst char*
	
	//��ȡ�ַ���file�ĺ�׺��".cpp"
	string file("string.cpp");
	size_t pos = file.rfind('.');//��ȡ�ַ�����ָ���ַ���λ��
	cout << pos << endl;
	string suffix(file.substr(pos, file.size() - pos));//posλ������ȡ<file.size() - pos>���ȵ��ַ���
	cout << suffix << endl;*/


	//��ȡurl������
	string url("http://www.cplusplus.com/reference/string/string/find/");
	cout << url << endl;
	size_t tail = url.rfind("://");//tailָ�򡮣���
	if (tail == string::npos)
	{
		cout << "invild url" << endl;
		return -1;
	}
	tail += 3;//tailָ���һ����W��
	size_t rear = url.find('/', tail);//��tailλ�������ҵ�һ�γ��֡�/���ַ���λ��
	string address = url.substr(tail, rear - tail);//��tail�������ң�rear-tail�������ȣ���������Ӵ�������һ���������Ľ�β��'\0'
	cout << address << endl;
	//��ȡurl��Э��ǰ׺
	size_t cont = url.find(":");//������ҵ�һ�γ����ַ�����λ�ã�û�ҵ����� string::npos
	cout << cont << endl;
	url.erase(cont, url.size() - cont);//��contλ���𣨰���coutλ�ã�����url.size()-cont����ʾ�����ĳ���
	cout << url << endl;

	string s6("Life");
	s6.push_back(' ');//β��ո��ַ�
	cout << s6 << endl;
	s6.append("is ");//׷���ַ���
	cout << s6 << endl;
	s6 += "not elsewhere";//׷���ַ������ַ���
	cout << s6 << endl;
	system("pause");
	return 0;
}
}