#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Huffman.hpp"
#pragma warning(disable:4996)

typedef unsigned char u_char;
struct CharInfo
{
	u_char _ch;
	unsigned long long _count;
	std::string _strCode;
	CharInfo(unsigned long long count = 0)
		:_count(count)
	{}
	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}
	bool operator>(const CharInfo& info)
	{
		return _count > info._count;
	}
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
};
class FileCompress
{
public:
	FileCompress();
	void CompressFile(const std::string& strFilePath);
	void UNCompressFile(const std::string& strFilePath);
private:
	void GetHuffmanCode(HTNode<CharInfo>* pRoot);
	void WriteHeadInfo(FILE* pf, const std::string& strFilePath);
	void GetLine(FILE* fp, std::string& strContent);

	std::vector<CharInfo> _fileInfo;
};
