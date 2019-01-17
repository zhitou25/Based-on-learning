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
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.232.129");
	addr.sin_port = htons(9000);
	socklen_t len = sizeof(struct sockaddr_in);
	int cnt = connect(sock, (struct sockaddr*)&addr, len);
	if (cnt < 0)
	{
		perror("connect error!\n");
		return -1;
	}

	while (1)
	{
		char buff[1024] = { 0 };
		fgets(buff, sizeof(buff), stdin);
		buff[strlen(buff) - 1] = '\0';
		write(sock, buff, sizeof(buff));

		memset(buff, '\0', 1024);
		read(sock, buff, sizeof(buff));
		printf("server:%s\n", buff);
	}

	close(sock);
	return 0;
}






