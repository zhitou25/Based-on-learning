#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>




int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("create socket fail!\n");
		return -1;
	}

	struct sockaddr_in addr;
	struct sockaddr_in client_socket;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.232.129");
	addr.sin_port = htons(9000);
	int ret = bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
	if (ret < 0)
	{
		perror("bind error!\n");
		return -1;
	}

	int lis = listen(sock, 5);
	if (lis < 0)
	{
		perror("listen error!\n");
		return -1;
	}
	struct sockaddr_in remote;
	socklen_t len = sizeof(struct sockaddr_in);
	int client_sock = accept(sock, (struct sockaddr*)&remote, &len);
	if (client_sock < 0)
	{
		perror("accept error!\n");
		return -1;
	}

	while (1)
	{
		char buff[1024] = { 0 };
		read(client_sock, buff, 1024);
		printf("client:%s\n", buff);

		memset(buff, 0x00, 1024);
		fgets(buff, 1024, stdin);
		buff[strlen(buff) - 1] = '\0';
		write(client_sock, buff, strlen(buff) + 1);
	}

	close(sock);
	return 0;
}














