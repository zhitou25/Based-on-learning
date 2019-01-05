
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include<string>
using namespace std;

class UdpSocket{

	  private:
	       int _sockfd;
	  public:
	       UdpSocket():_sockfd(-1){}
	       bool Socket()
	       {
			 _sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			 if(_sockfd<0)
			 {
				   perror("socket fail!\n");
				   return false;
			 }
			 return true;
	       }
	       bool Bind(string& ip,uint16_t port)
	       {
			 sockaddr_in addr;
			 addr.sin_family=AF_INET;
			 addr.sin_port=htons(port);
                         addr.sin_addr.s_addr=inet_addr(ip.c_str());
			 socklen_t len=sizeof(sockaddr_in);
			 int ret=bind(_sockfd,(sockaddr*)&addr,len);
			 if(ret<0)
			 {
				   perror("bind fail!\n");
				   return false;
			 }
			 return true;
	       }
	       ssize_t Recv(char *buff,sockaddr_in *addr=NULL)
	       {
			 sockaddr_in _addr;
			 ssize_t rlen;
			 socklen_t len=sizeof(sockaddr_in);
			 rlen=recvfrom(_sockfd,buff,1024,0,(sockaddr*)&_addr,&len);
			 if(rlen<0)
			 {
				   perror("recv fail!\n");
				   return -1;
			 }
			 if(addr)
			 {
				   memcpy((void*)addr,(void*)&_addr,len);
			 }
			 return len;
	       }
	       bool Send(char* buff,size_t len,sockaddr_in &addr)
	       {
			 int slen=0;
			 slen=sendto(_sockfd,buff,len,0,(sockaddr*)&addr,sizeof(sockaddr));
			 if(slen<0)
			 {
				   perror("send fail!\n");
				   return false;
			 }
			 return true;
	       }
	       bool Close()
	       {
			 if(_sockfd>=0)
			 {
				   close(_sockfd);
				   _sockfd=-1;
			 }
			 return true;
	       }
};


#define CHECK_RET(q) if(q==false){return -1;}

int main()
{
	  UdpSocket sock;
	  
	  CHECK_RET(sock.Socket());
	  sockaddr_in addr;
	  addr.sin_family=AF_INET;
	  addr.sin_port=htons(9000);
	  addr.sin_addr.s_addr=inet_addr("192.168.232.129");
	  while(1)
	  {
		    char buff[1024]={0};
		    scanf("%[^\n]%*c",buff);
		    sock.Send(buff,strlen(buff),addr);
		    printf("client say: %s\n",buff);

		    memset(buff,0x00,1024);
		    sock.Recv(buff);
		    printf("server buff: %s\n",buff);
	  }
	  sock.Close();
	  return 0;
}


		    
