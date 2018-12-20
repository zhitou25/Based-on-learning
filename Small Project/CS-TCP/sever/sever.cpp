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
	//4.�󶨶˿�
	int r = bind(ServerSocket, (sockaddr*)&addr, sizeof addr);
	if (INVALID_SOCKET == ServerSocket)
	{
		printf("bind  fail!\n");
		return -2;
	}
	printf("bind  success!\n");
	//5.����
	r = listen(ServerSocket, 10);//10��ʾ���Դ�����ٸ������������������п����ж೤
	if (INVALID_SOCKET == r)
	{
		printf("listen  fail!\n");
		return -2;
	}
	printf("listen  success!\n");
	//6.��������
	//���ܿͻ��˵�ip��ַ
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof cAddr;
	SOCKET ClientSocket = accept(ServerSocket, (sockaddr*)&cAddr, &len);
	if (ClientSocket == INVALID_SOCKET)
	{
		printf("client connect fail!");
		closesocket(ServerSocket);
		return -3;
	}
	printf("client connect success:%s\n", inet_ntoa(cAddr.sin_addr));
	//7.ͨ��
	char buff[256] = {0};
	while (1)
	{
		r = recv(ClientSocket, buff, 255, 0);
		if (r > 0)
		{
			printf("->%s\n", buff);
		}
		memset(buff, ' ', (strlen(buff) + 1));
	}
	//system("pause");
    return 0;
}

