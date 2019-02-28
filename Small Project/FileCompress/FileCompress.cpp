#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"FileCompress.h"

using namespace std;
FileCompress::FileCompress()
{
	_fileInfo.resize(256);
	for (size_t i = 0; i < 256; i++)
	{
		_fileInfo[i]._ch = i;
		_fileInfo[i]._count = 0;
	}
}
//1.ͳ��Դ�ļ���ÿ���ַ����ֵĴ���
void FileCompress::CompressFile(const std::string& strFilePath)
{
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "file open fail!" << endl;
		return;
	}
	u_char *pReadBuff = new u_char[1024];
	while (true)
	{
		size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
		if (0 == rdSize)
			break;
		for (size_t i = 0; i < rdSize; ++i)
		{
			_fileInfo[pReadBuff[i]]._count++;
		}
	}

	//2.��ÿ���ַ����ֵĴ���ΪȨֵ����huffman��
	HuffmanTree<CharInfo> ht;
	ht.CreatHuffmanTree(_fileInfo, CharInfo(0));

	//3.ͨ��huffman����ȡÿ���ַ��ı���
	GetHuffmanCode(ht.GetRoot());
	//4.�û�ȡ��huffman���������¸�д�ļ�
	u_char ch = 0;
	int bitCount = 0;
	FILE* fOut = fopen("1.yzp", "wb");
	assert(fOut);

	WriteHeadInfo(fOut, strFilePath);
	rewind(fIn);
	while (true)
	{
		size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
		if (0 == rdSize)
			break;
		for (size_t i = 0; i < rdSize; ++i)
		{
			string& strCode = _fileInfo[pReadBuff[i]]._strCode;
			for (size_t j = 0; j < strCode.size(); ++j)
			{
				ch <<= 1;
				if ('1' == strCode[j])
					ch |= 1;

				bitCount++;
				if (8 == bitCount)
				{
					fputc(ch, fOut);
					ch = 0;
					bitCount = 0;
				}
			}
		}
	}
	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fOut);
	}
	delete[] pReadBuff;
	fclose(fIn);
	fclose(fOut);
}
void FileCompress::GetHuffmanCode(HTNode<CharInfo>* pRoot)
{
	if (nullptr == pRoot)
		return;

	if (nullptr == pRoot->_pLeft&&nullptr == pRoot->_pRight)
	{
		HTNode<CharInfo>* pcur = pRoot;
		HTNode<CharInfo>* pParent = pcur->_pParent;
		string& strCode = _fileInfo[pRoot->_weight._ch]._strCode;
		while (pParent)
		{
			if (pcur == pParent->_pLeft)
				strCode += '0';
			else
				strCode += '1';

			pcur = pParent;
			pParent = pcur->_pParent;
		}
		reverse(strCode.begin(), strCode.end());
	}
	GetHuffmanCode(pRoot->_pLeft);
	GetHuffmanCode(pRoot->_pRight);
}

void FileCompress::WriteHeadInfo(FILE* fp, const string& strFilePath)
{
	//Դ�ļ���׺
	string Suffix = strFilePath.substr(strFilePath.rfind('.'));
	//ͳ����Ч������������Ч�ַ��Լ����ֵĴ���
	string strCharCount;
	size_t lineCount = 0;
	char szCount[32] = { 0 };
	for (size_t i = 0; i < 256; ++i)
	{
		if (0 != _fileInfo[i]._count)
		{
			strCharCount += _fileInfo[i]._ch;
			strCharCount += ':';
			memset(szCount, 0, 32);
			_itoa(_fileInfo[i]._count, szCount, 10);
			strCharCount += szCount;
			strCharCount += "\n";
			lineCount++;
		}
	}

	string strHeadInfo;
	strHeadInfo += Suffix;
	strHeadInfo += "\n";

	memset(szCount, 0, 32);
	_itoa(lineCount, szCount, 10);
	strHeadInfo += szCount;
	strHeadInfo += "\n";
	strHeadInfo += strCharCount;

	fwrite(strHeadInfo.c_str(), 1, strHeadInfo.size(), fp);
}



