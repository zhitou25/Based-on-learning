// sever.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
int main()
{
	//1.版本请求
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
	//创建SOCKET
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ServerSocket)
	{
		printf("socket create fail!\n");
		return -2;
	}
	printf("socket create success!\n");
	//3.协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("172.20.10.2");
	addr.sin_port = htons(10086);
	//4.绑定端口
	int r = bind(ServerSocket, (sockaddr*)&addr, sizeof addr);
	if (INVALID_SOCKET == ServerSocket)
	{
		printf("bind  fail!\n");
		return -2;
	}
	printf("bind  success!\n");
	//5.监听
	r = listen(ServerSocket, 10);//10表示可以处理多少个请求，你的连接请求队列可以有多长
	if (INVALID_SOCKET == r)
	{
		printf("listen  fail!\n");
		return -2;
	}
	printf("listen  success!\n");
	//6.接受连接
	//接受客户端的ip地址
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
	//7.通信
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

