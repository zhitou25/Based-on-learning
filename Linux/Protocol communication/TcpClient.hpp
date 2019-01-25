#ifndef _TCP_CLIENT_HPP
#define _TCP_CLIENT_HPP

#include<iostream>
#include<string>
#include<strings.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

class TcpClient
{
	  private:
		    int sock;
		    std::string ip;
		    int port;
	  public:
		    TcpClient(std::string _ip,int _port):ip(_ip),port(_port)
	  {}
		    void InitClient()
		    {
			      sock=socket(AF_INET,SOCK_STREAM,0);
			      if(sock<0)
			      {
					std::cerr<<"socket error!"<<std::endl;
					exit(2);
			      }
		    }
		    void Start()
		    {
			     struct sockaddr_in peer;
			     bzero(&peer,sizeof(peer));
			     peer.sin_family=AF_INET;
			     peer.sin_port=htons(port);
			     peer.sin_addr.s_addr=inet_addr(ip.c_str());

			      if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
			      {
					std::cerr<<"connect error!"<<std::endl;
					exit(3);
			      }
			      std::string in;
			      while(1)
			      {
					char buf[1024];
					std::cout<<"please enter: "<<std::endl;
					std::cin>>in;
					write(sock,in.c_str(),in.size());
					ssize_t s=read(sock,buf,sizeof(buf)-1);
					if(s>0)
					{
						  buf[s]=0;
						  std::cout<<"server echo: "<<buf<<std::endl;
					}
			      }
		    }
		    ~TcpClient()
		    {
			      if(sock)
					close(sock);
		    }
};






#endif
