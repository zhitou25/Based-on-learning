#include<iostream>
#include<string>
using namespace std;


int main()
{/*
	//string 常见构造   VS下sizeof(string)=28
	string s1;//定义一个字符串s1
	string s2 = "hello!";//用C格式字符串构造string类对象s2
	string s3(10, 'c');//用10个字符'c'构造string类对象s3
	string s4(s2);//将s2拷贝至s4进行初始化
	string s5(s3,5);//用s3的前五个字符构造s5

	//string类对象的容量操作
	cout << s2.length() << endl;//获取s2的有效长度(不包括'\0')
	cout << s2.capacity() << endl;//s2空间总大小
	cout << s2.size() << endl;//和length作用一致，size的存在是为了和其它容器接口保持统一
	cout << s2 << endl;//string类对象支持使用cin cout直接输入输出
	s2.clear();//将s中的字符串清空，注意清空时只是将size清零，并不改变第层空间大小
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	cout << s2.size() << endl;
	s2 = "hello!";
	s2.resize(10, 'c');//将s2的有效元素个数变为10个，多余的位使用字符c填充
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.resize(15);//改变s2有效元素个数为15，多余的位用缺省值'\0'填充
	cout << s2 << endl;
	cout << s2.capacity() << endl;
	s2.reserve(16);//为string预留空间，不改变有效元素个数，当reserve的参数小于s2底层空间大小时，不改变其底层空间大小
	cout << s2.capacity() << endl;
	s3 = "hello!";//直接对s3的内容进行修改
	s3[1] = 'h';
	cout << s3 << endl;

	string str;
	str.append("hello"); // 在str后追加一个字符"hello"
	str.push_back(' '); // 在str后插入空格
	str += "wor"; // 在str后追加一个字符'b' 
	str += "ld"; // 在str后追加一个字符串"it"
	cout << str << endl;
	cout << str.c_str() << endl; //以c语言的方式打印字符串,str.c_str()返回类型为const char*
	
	//获取字符串file的后缀名".cpp"
	string file("string.cpp");
	size_t pos = file.rfind('.');//获取字符串种指定字符的位置
	cout << pos << endl;
	string suffix(file.substr(pos, file.size() - pos));//pos位置向后获取<file.size() - pos>长度的字符串
	cout << suffix << endl;*/


	//获取url的域名
	string url("http://www.cplusplus.com/reference/string/string/find/");
	cout << url << endl;
	size_t tail = url.rfind("://");//tail指向‘：’
	if (tail == string::npos)
	{
		cout << "invild url" << endl;
		return -1;
	}
	tail += 3;//tail指向第一个‘W’
	size_t rear = url.find('/', tail);//从tail位置向后查找第一次出现‘/’字符的位置
	string address = url.substr(tail, rear - tail);//从tail处向后查找（rear-tail）个长度，并将这段子串赋给另一个对象，它的结尾无'\0'
	cout << address << endl;
	//获取url的协议前缀
	size_t cont = url.find(":");//正向查找第一次出现字符串的位置，没找到返回 string::npos
	cout << cont << endl;
	url.erase(cont, url.size() - cont);//从cont位置起（包括cout位置），（url.size()-cont）表示擦除的长度
	cout << url << endl;

	string s6("Life");
	s6.push_back(' ');//尾插空格字符
	cout << s6 << endl;
	s6.append("is ");//追加字符串
	cout << s6 << endl;
	s6 += "not elsewhere";//追加字符或者字符串
	cout << s6 << endl;
	system("pause");
	return 0;
}
}