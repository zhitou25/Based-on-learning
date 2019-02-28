#include"filecompress.h"
#include<time.h>
int main()
{
	clock_t start, finsh;
	double totaltime;
	start = clock();
	FileCompress fc;
	fc.CompressFile("1.txt");
	finsh = clock();
	totaltime = (double)(finsh - start) / CLOCKS_PER_SEC;
	std::cout << "time:" << totaltime << std::endl;
	fc.UNCompressFile("1.yzp");
	return 0;

}