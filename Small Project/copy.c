#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
/*
*ģ��ʵ��Windows�µĿ�������
*/



int main()
{
	char src[1024];
	char dst[1024];
	printf("src path:");
	scanf("%s", src);
	printf("dst path:");
	scanf("%s", dst);

	FILE *srcp = fopen(src, "rb");//�Զ����ƶ��ķ�ʽ��
	FILE *dstp = fopen(dst, "wb");//�Զ�����д�ķ�ʽ��
	if (srcp == NULL || dstp == NULL)
	{
		printf("open file error!\n");
		return -1;
	}
	fseek(srcp, 0, SEEK_END);//���ļ�ָ��������ļ���β�����Ի�ȡ�ļ��ֽ���
	int size = ftell(srcp);
	rewind(srcp);//���µ����ļ�ָ�뵽�ļ���ʼ��

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