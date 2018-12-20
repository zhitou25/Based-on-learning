// client.cpp : 定义控制台应用程序的入口点。
//

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
	//4.连接服务器
	int r = connect(ServerSocket, (sockaddr*)&addr, sizeof addr);
	if (SOCKET_ERROR == r)
	{
		printf("sever connect fail!\n");
		return -1;
	}
	printf("sever connect success!\n");

	//7.通信
	char buff[256] = {0};
	while (1)
	{
		printf("input:");
		//scanf读取缓冲区数据时候，默认遇到空格或者换行终止
		// %[^\n]:将\n之前的数据放入到cmd中 设置遇到\n终止
		// %*c:将剩下的字符全都从缓冲区取出来，丢弃
		//scanf("%c", buff);
		scanf("%[^\n]%*c", buff);
		send(ServerSocket, buff, strlen(buff), NULL);
	}
	system("pause");
	return 0;
}

