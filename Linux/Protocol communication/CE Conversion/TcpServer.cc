#include"thread_TcpServer.hpp"


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
	  
	  dict.insert(std::pair<std::string,std::string>("apple","苹果"));
	  dict.insert(std::pair<std::string,std::string>("banana","香蕉"));
	  dict.insert(std::pair<std::string,std::string>("lemon","柠檬"));
	  dict.insert(std::pair<std::string,std::string>("peach","桃子"));

	  int port=atoi(argv[2]);
	  std::string ip=argv[1];
	  TcpServer *tsp=new TcpServer(ip,port);
	  tsp->InitServer();
	  tsp->Start();
	  return 0;
}

