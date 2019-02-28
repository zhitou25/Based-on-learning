#include"FileCompress.h"

using namespace std;

void FileCompress::UNCompressFile(const std::string& strFilePath)
{
	string suffix = strFilePath.substr(strFilePath.rfind('.') + 1);
	if ("yzp" != suffix)
	{
		cout << "file format error!" << endl;
		return;
	}

	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		cout << "zip file open error!" << endl;
		return;
	}

	//从压缩文件获取文件后缀
	suffix = "";
	GetLine(fIn, suffix);
	//从压缩文件中获取字符编码信息
	string strContent;
	GetLine(fIn, strContent);
	size_t lineCount = atoi(strContent.c_str());

	size_t charCount;
	for (size_t i = 0; i < lineCount; ++i)
	{
		strContent = "";
		GetLine(fIn, strContent);
		if ("" == strContent)
		{
			strContent += "\n";
			GetLine(fIn, strContent);
		}
		charCount = atoi(strContent.c_str() + 2);
		u_char *str = (u_char*)strContent.c_str();
		_fileInfo[str[0]]._count = charCount;
	}

	//还原huffmanTree
	HuffmanTree<CharInfo> ht;
	ht.CreatHuffmanTree(_fileInfo, CharInfo(0));

	//解压缩
	string strUnFileName("2");
	strUnFileName += suffix;
	FILE* fOut = fopen(strUnFileName.c_str(), "wb");
	char* pReadBuff = new char[1024];
	int pos = 7;
	HTNode<CharInfo>* pCur = ht.GetRoot();
	long long fileSize = pCur->_weight._count;
	while (true)
	{
		size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
		if (0 == rdSize)
			break;

		for (size_t i = 0; i < rdSize; ++i)
		{
			pos = 7;
			size_t j = 0;
			while (j<8)
				// for (size_t j = 0; j < 8;++j);
			{
				j++;
				if (pReadBuff[i] & (1 << pos))

					pCur = pCur->_pRight;
				else
					pCur = pCur->_pLeft;

				if (nullptr == pCur->_pLeft&&nullptr == pCur->_pRight)
				{
					fputc(pCur->_weight._ch, fOut);
					pCur = ht.GetRoot();
					--fileSize;
					if (!fileSize)
						break;
				}
				pos--;
				if (pos < 0)
				{
					break;
				}
			}
		}
	}
	delete[]pReadBuff;
	fclose(fIn);
	fclose(fOut);
}
void FileCompress::GetLine(FILE* fp, string& strContent)
{
	while (!feof(fp))
	{
		char ch = fgetc(fp);
		if ('\n' == ch)
			return;
		strContent += ch;
	}
}