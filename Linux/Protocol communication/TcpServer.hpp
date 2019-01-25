#ifndef _TCP_SERVER_HPP_
#define _TCP_SERVER_HPP_

#include<stdio.h>
#include<iostream>
#include<string>
#include<strings.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>

class TcpServer{
	  private:
		    int listen_sock;
		    std::string ip;
		    int port;
	  public:
			      TcpServer(std::string _ip,int _port):ip(_ip),port(_port),listen_sock(-1)
	  {}

			      void InitServer()
			      {
					listen_sock=socket(AF_INET,SOCK_STREAM,0);
					if(listen_sock<0)
					{
						  std::cerr<<"socket error!"<<std::endl;
						  exit(2);
					}
					setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&OPT,sizeof(opt));//服务器关闭再次重启会发生bind错误，通过设置该选项可解决该问题

					sockaddr_in local;
					local.sin_family=AF_INET;
					local.sin_port=htons(port);
					local.sin_addr.s_addr=inet_addr(ip.c_str());
					socklen_t len=sizeof(local);
					if(bind(listen_sock,(struct sockaddr*)&local,len)<0)
					{
						  std::cerr<<"bind error!"<<std::endl;
						  exit(3);
					}
					if(listen(listen_sock,5)<0)
					{
						  std::cerr<<"listen error!"<<std::endl;
						  exit(4);
					}
					signal(SIGCHLD,SIG_IGN);//忽略SIGCHLD信号，并不会产生僵尸
			      }
					
				     
			      void Service(int sock,std::string _ip,int _port)
			      {
					while(1)
					{
						  char buf[1024];
						  ssize_t s=read(sock,buf,sizeof(buf)-1);
						  buf[s]=0;
						  std::cout<<"[ "<<_ip<<"::"<<_port<<" ]"<<buf<<std::endl;
						  if(s>0)
						  {
							    buf[s]=0;
							    write(sock,buf,strlen(buf));
						  }
						  else if(s==0)
						  {
							    std::cout<<"client quit!"<<std::endl;
							    break;
						  }
						  else
						  {
							    std::cout<<"read error!"<<std::endl;
							    break;
						  }
					}
					close(sock);
			      }
			      void Start()
			      {
					struct sockaddr_in peer;
					socklen_t len;
					for(;;)
					{
						  int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
						  if(sock<0)
						  {
						  std::cerr<<"accept error!"<<std::endl;
						  continue;
						  }
						  std::cout<<"Get a new client "<<sock<<std::endl;
						  
						 int _port=ntohs(peer.sin_port);
						 std::string _ip=inet_ntoa(peer.sin_addr);
						 

						  pid_t id=fork();
						  if(id<0)
						  {
							    perror("fork error!");
							    close(sock);
							    continue;
						  }
						  else if(id=0)
						  {
							    close(listen_sock);
							    Service(sock,_ip,_port);
							    exit(0);
						  }
						  else
						  {
							    close(sock);
						  }
					}
			      }
							    

			      ~TcpServer()
			      {
					if(listen_sock)
						  close(listen_sock);
			      }
};





#endif

