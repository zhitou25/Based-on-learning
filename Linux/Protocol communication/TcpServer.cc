#include"TcpServer.hpp"


void Usage(std::string proc)
{
	  std::cout<<"Usage: "<<proc<<" ip  port"<<std::endl;
}


int main(int argc,char* argv[])
{
	  if(argc!=3)
	  {
		    Usage(argv[0]);
		    exit(1);
	  }
	  int port=atoi(argv[2]);
	  std::string ip=argv[1];
	  TcpServer *tsp=new TcpServer(ip,port);
	  tsp->InitServer();
	  tsp->Start();
	  return 0;
}

