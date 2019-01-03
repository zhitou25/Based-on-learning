#include<iostream>
#include<string>
#pragma warning(disable:4996)
using namespace std;



struct Match {
	static bool get()
	{
		return true;
	}
};

struct unMatch {
	static bool get()
	{
		return false;
	}
};

template <class T>
struct TypeTraits
{
	typedef unMatch type;
};

template<>
struct TypeTraits<int>
{
	typedef Match type;
};

template<>
struct TypeTraits<short>
{
	typedef Match type;
};

template<>
struct TypeTraits<char>
{
	typedef Match type;
};

template<>
struct TypeTraits<float>
{
	typedef Match type;
};

template<>
struct TypeTraits<double>
{
	typedef Match type;
};

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	//T是否为内置类型通过将模板特化为绝对类型来判断
	if (TypeTraits<T>::type::get())
	{
		memcpy(dst, src, sizeof(T)*size);
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
	}
}

int main()
{
	int src[] = { 1,2,3,4,5,6,7,8,9,0 };
	int dst[sizeof(src) / sizeof(src[0])];
	Copy(dst, src, sizeof(src) / sizeof(src[0]));

	string str1[] = { "aaa","bbb","ccc","ddd" };
	string str2[sizeof(str1) / sizeof(str1[0])];
	Copy(str2, str1, sizeof(str1) / sizeof(str1[0]));
	return 0;
}