/*
*功能：基于udp协议的简单网络通信程序
*时间：2019/1/2 20:33
*/



#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>


int main()
{
	  //1.创建套接字
	  int sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	  if(sockfd<0)
	  {
		    perror("socket fail!\n");
		    return -1;
	  }
	  //2.为套接字绑定地址信息
	  struct sockaddr_in addr;
	  addr.sin_family=AF_INET;
	  addr.sin_port=htons(9000);
	  addr.sin_addr.s_addr=inet_addr("192.168.232.129");
	  socklen_t len=sizeof(struct sockaddr_in);
	  int ret =bind(sockfd,(struct sockaddr*)&addr,len);
	  if(ret<0)
	  {
		    perror("bind error!\n");
		    return -1;
	  }
	  //3.接收数据
	  while(1)
	  {
		    char buff[1024]={0};
		    struct sockaddr_in cli_addr;
		    recvfrom(sockfd,buff,1023,0,
					(struct sockaddr*)&cli_addr,&len);
		    printf("client say: %s\n",buff);
		    //4.发送数据
		    memset(buff,0x00,1024);
		    scanf("%s",buff);
		    sendto(sockfd,buff,strlen(buff),0,
					(struct sockaddr*)&cli_addr,len);
		    printf("server say: %s\n");
	  }
	  //5.关闭套接字
	  close(sockfd);
	  return 0;
}
