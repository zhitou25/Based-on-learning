// client.cpp : �������̨Ӧ�ó������ڵ㡣
//

// sever.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
int main()
{
	//1.�汾����
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (HIBYTE(wsaData.wVersion) == 2 && LOBYTE(wsaData.wVersion) == 2)
	{
		printf("request version success!\n");
	}
	else
	{
		printf("request version fail!\n");
		return -1;
	}
	//����SOCKET
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSocket)
	{
		printf("socket create fail!\n");
		return -2;
	}
	printf("socket create success!\n");
	//3.Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("172.20.10.2");
	addr.sin_port = htons(10086);
	//4.���ӷ�����
	int r = connect(ServerSocket, (sockaddr*)&addr, sizeof addr);
	if (SOCKET_ERROR == r)
	{
		printf("sever connect fail!\n");
		return -1;
	}
	printf("sever connect success!\n");

	//7.ͨ��
	char buff[256] = {0};
	while (1)
	{
		printf("input:");
		//scanf��ȡ����������ʱ��Ĭ�������ո���߻�����ֹ
		// %[^\n]:��\n֮ǰ�����ݷ��뵽cmd�� ��������\n��ֹ
		// %*c:��ʣ�µ��ַ�ȫ���ӻ�����ȡ����������
		//scanf("%c", buff);
		scanf("%[^\n]%*c", buff);
		send(ServerSocket, buff, strlen(buff), NULL);
	}
	system("pause");
	return 0;
}

