#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
/*
*模拟实现Windows下的拷贝功能
*/



int main()
{
	char src[1024];
	char dst[1024];
	printf("src path:");
	scanf("%s", src);
	printf("dst path:");
	scanf("%s", dst);

	FILE *srcp = fopen(src, "rb");//以二进制读的方式打开
	FILE *dstp = fopen(dst, "wb");//以二进制写的方式打开
	if (srcp == NULL || dstp == NULL)
	{
		printf("open file error!\n");
		return -1;
	}
	fseek(srcp, 0, SEEK_END);//将文件指针调整到文件结尾处，以获取文件字节数
	int size = ftell(srcp);
	rewind(srcp);//重新调整文件指针到文件起始处

	char*buf = (char*)malloc(size);
	if (buf == NULL)
	{
		printf("malloc error!\n");
		return -2;
	}
	fread(buf, size, 1, srcp);
	fwrite(buf, size, 1, dstp);
	fclose(srcp);
	fclose(dstp);
	free(buf);
	return 0;
}