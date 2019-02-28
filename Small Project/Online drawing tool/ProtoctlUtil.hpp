#ifndef _PROTOCOLUTIL_HPP
#define _PROTOCOLUTIL_HPP_
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sstream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/sendfile.h>


#define BACKLOG 5
#define BUFF_NUM 1024
#define NORMAL 0
#define WARNING 1
#define ERROR 2

#define WWWROOT "wwwroot"
#define HOMEPAGE "index.html"
const char *ErrLevel[]={
	  "Normal",
	  "Warning",
	  "Error",
};

void log(std::string msg,int level,std::string file,int line)
{
	  std::cout<<" [ "<<file<<" : "<<line<<" ] "<<msg<<"  "<<ErrLevel[level]<<std::endl;
}

#define LOG(msg,level) log(msg,level,__FILE__,__LINE__);


class Util
{
	  public:
		    static void MakeKV(std::string s,std::string& k,std::string& v)
		    {
			      std::size_t pos=s.find(": ");
			      k=s.substr(0,pos);
			      v=s.substr(pos+2);
		    }
		    static std::string IntToString(int &x)
		    {
			      std::stringstream ss;
			      ss<<x;
			      return ss.str();
		    }
		    static std::string CodeToDesc(int code)
		    {
			      switch(code)
			      {
					case 200:
						  return "Ok";
					case 404:
						  return "Not Found";
					default:
						  break;
			      }	
			      return "UnKnow";
		    }
};
class SocketApi
{
	  public:
		    static int Socket()
		    {
			      int sock=socket(AF_INET,SOCK_STREAM,0);
			      if(sock<0)
			      {
					LOG("socket error!",ERROR);
					exit(2);
			      }
			      int opt=1;
			      setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
			      return sock;
		    }
		    static void Bind(int sock,int port)
		    {
			      struct sockaddr_in local;
			      //将local的置为0且包括‘\0’
			      bzero(&local,sizeof(local));
			      local.sin_family=AF_INET;
			      local.sin_port=htons(port);
			      local.sin_addr.s_addr=htonl(INADDR_ANY);

			      if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
			      {
					LOG("bind error!",ERROR);
					exit(3);
			      }
		    }
		    static void Listen(int sock)
		    {
			      if(listen(sock,BACKLOG)<0)
			      {
					LOG("listen error!",ERROR);
					exit(4);
			      }
		    }
		    static int Accept(int listen_sock,std::string &ip,int &port)
		    {
			      struct sockaddr_in peer;
			      socklen_t len=sizeof(peer);
			      int sock=accept(listen_sock,(struct sockaddr*)&peer,&len);
			      if(sock<0)
			      {
					LOG("accept error!",WARNING);
					return -1;
			      }
			      port=ntohs(peer.sin_port);
			      ip=inet_ntoa(peer.sin_addr);//结构体不能整体赋值，但可以整体初始化，这里相当于初始化
			      return sock;
		    }

};


class HttpResponse
{
	  public:
		    std::string status_line;//状态行
		    std::vector<std::string> response_header;//响应头部
		    std::string blank;//空行
		    std::string response_text;//响应正文
	  private:
		    int code;
		    std::string path;//响应资源的路径
		    int resource_size;
	  public:
		    HttpResponse():blank("\r\n"),code(200),resource_size(0)
	  {}
		    int &Code()
		    {
			      return code;
		    }
		    void MakeStatusLine()
		    {
			      status_line="HTTP/1.0";
			      status_line+=" ";
			      status_line+=Util::IntToString(code);
			      status_line+=" ";
			      status_line+=Util::CodeToDesc(code);
			      status_line+="\r\n ";
			      LOG("Make Status Line Finshed!",NORMAL);
		    }
		    void MakeResponseHeader()
		    {
			      std::string line;
			      std::cout<<"["<<line<<"]"<<std::endl;
			      line="Content-Length: ";
			      line+=Util::IntToString(resource_size);
			      line+="\r\n";
			      response_header.push_back(line);
			      line="\r\n";
			      response_header.push_back(line);
			      LOG("Make Response Header Finshed!",NORMAL);
		    }
		    void SetPath(std::string& _path)
		    {
			      path=_path;
		    }
		    std::string &Path()
		    {
			      return path;
		    }
		    void SetResourceSize(int size)
		    {
			      resource_size=size;
		    }
		    int ResourceSize()
		    {
			      return resource_size;
		    }
		    ~HttpResponse()
		    {}
};

class HttpRequest
{
	  public:
		    //基本协议字段
		    std::string request_line;//请求行
		    std::vector<std::string> request_header;//请求头部
		    std::string blank;//空行
		    std::string request_text;//正文

		    //解析字段
		    std::string method;
		    std::string uri;//path?arg
		    std::string path;
		    std::string version;
		    std::string query_string;//GET带参，参数的字符串
		    std::unordered_map<std::string,std::string> header_kv;
		    bool cgi;

	  public:
		    HttpRequest():path(WWWROOT),cgi(false),blank("\r\n")
	  {}
		    void RequestLineParse()
		    {
			      std::stringstream ss(request_line);
			      ss>>method>>uri>>version;
			      transform(method.begin(),method.end(),method.begin(),::toupper);
		    }
		    void UriParse()
		    {
			      if(method=="GET")
			      {
					std::size_t pos=uri.find('?');
					if(pos!=std::string::npos)
					{
						  cgi=true;
						  path+=uri.substr(0,pos);//第二个参数pos表示长度
						  query_string=uri.substr(pos+1);
					}
					else
					{
						  path+=uri;
					}
			      }
			      else
			      {
					cgi=true;
					path+=uri;
			      }
			      if(path[path.size()-1]=='/')
			      {
					path+=HOMEPAGE;
			      }

		    }
		    void HanderPrase()
		    {
			      std::string k,v;
			      for(auto it=request_header.begin();it!=request_header.end();it++)
			      {
					Util::MakeKV(*it,k,v);
					header_kv.insert({k,v});
			      }
		    }

		    bool IsMethodLegal()
		    {
			      if(method!="GET"&&method!="POST")
			      {
					return false;
			      }
			      return true;
		    }
		    //文件是否符合要求包括两个方面，一个是文件存在，另一个是是否可执行
		    //一种方式是通过是否能打开文件fopen()判断文件是否存在，但如果文件是一个二进制的可执行文件呢？
		    //判断文件是否可执行可通过文件属性是否具有可执行权限位
		    int IsPathLegal(HttpResponse* rsp)
		    {
			      struct stat st;
			      int rs=0;
			      if(stat(path.c_str(),&st)<0)
			      {
					path.erase(0);
					path+=WWWROOT;
					path+="/";
					path+="404.html";
					stat(path.c_str(),&st);
					rs=st.st_size;
					rsp->SetPath(path);
					rsp->SetResourceSize(rs);
					return 404;
			      }
			      else
			      {
					rs=st.st_size;
					//判断是否是一个目录
					if(S_ISDIR(st.st_mode))
					{
						  path+='/';
						  path+=HOMEPAGE;
						  rs=st.st_size;
					}
					else if((st.st_mode&S_IXUSR)||\
				                (st.st_mode&S_IXGRP)||\
					        (st.st_mode&S_IXOTH))
					{
						  cgi=true;
					}
					else
					{
						  cgi=false;//不需要再赋值
					}
					rsp->SetPath(path);
					rsp->SetResourceSize(rs);
					LOG("Path is correct!",NORMAL);
					return 0;
			      }
		    }
		    bool IsNeedRecv()
		    {
			      LOG("POST Method,Recv Again!",NORMAL);
			      return method=="POST";
		    }
		    bool IsCgi()
		    {
			      return cgi;
		    }
		    int ContentLength()
		    {
			      int content_length=-1;
			      std::string cl= header_kv["Content-Length"];
			      std::stringstream ss(cl);
			      ss>>content_length;
			      return content_length;
		    }
		    std::string GetParam()
		    {
			      if(method=="GET")
			      {
					return query_string;
			      }
			      return request_text;
		    }
		    ~HttpRequest()
		    {}

};



class Connect
{
	  private:
		    int sock;
	  public:
		    Connect(int sock_):sock(sock_)
	  {}
		    int RecvOneLine(std::string& line_)
		    {
			      char buff[BUFF_NUM];
			      char c='X';
			      int i=0;
			      while(c!='\n'&&i<BUFF_NUM-1)
			      {
					ssize_t size=recv(sock,&c,1,0);
					if(size>0)
					{
						  if(c=='\r')
						  {
							    recv(sock,&c,1,MSG_PEEK);
							    if(c=='\n')
							    {
								      recv(sock,&c,1,0);
							    }
							    else
							    {
								      c='\n';
							    }
						  }
						  //\r \r\n \n -> \n
						  buff[i++]=c;
					}
					else
					{
						  break;
					}
			      }
			      buff[i]=0;
			      line_=buff;
			      return i;
		    }
		    void RecvRequestHandler(std::vector<std::string>& v)
		    {
			      std::string line="X";
			      while(line!="\n")
			      {
					RecvOneLine(line);
					if(line!="\n")
					{
						  v.push_back(line);
					}
			      }
			      LOG("RecvRequestHandler is correct!",NORMAL);
		    }
		    void RecvText(std::string &text,int content_length)
		    {
			      char ch;
			      for(auto i=0;i<content_length;i++)
			      {
					recv(sock,&ch,1,0);
					text.push_back(ch);
			      }
		    }

		    void SendStatusLine(HttpResponse* rsp)
		    {
			      std::string& sl=rsp->status_line;
			      send(sock,sl.c_str(),sl.size()-1,0);
		    }
		    void SendHeader(HttpResponse* rsp)
		    {
			      std::vector<std::string> &v=rsp->response_header;
			      for(auto it=v.begin();it!=v.end();it++)
			      {
					send(sock,it->c_str(),it->size(),0);
			      }
		    }
		    void SendText(HttpResponse* rsp,bool cgi_)
		    {
			      if(!cgi_)
			      {
					std::string& path=rsp->Path();
					int fd=open(path.c_str(),O_RDONLY);
					if(fd<0)
					{
						  LOG("open file error!",WARNING);
						  return;
					}
					sendfile(sock,fd,NULL,rsp->ResourceSize());
			      }
			      else
			      {
					std::string &rsp_text=rsp->response_text;
					send(sock,rsp_text.c_str(),rsp_text.size(),0);
			      }
		    }
		    ~Connect()
		    {
			      close(sock);
		    }
};

class Entry
{
	  public:
		    static int ProcessCgi(Connect* conn,HttpRequest* rq,HttpResponse* rsp)
		    {
			      int input[2];
			      int output[2];
			      pipe(input);
			      pipe(output);// child process

			      std::string bin=rsp->Path();
			      std::string param=rq->GetParam();
			      int  size=param.size();
			      std::string param_size="CONTENT-LENGTH=";
			      param_size+=Util::IntToString(size);

			      std::string &response_text=rsp->response_text;

			      pid_t id=fork();
			      if(id<0)
			      {
					LOG("fork error!",WARNING);
					return 503;
			      }
			      else if(id==0)
			      {
					close(input[1]);
					close(output[0]);
					putenv((char *)param_size.c_str());
					dup2(input[0],0);
					dup2(output[1],1);

					execl(bin.c_str(),bin.c_str(),NULL);
					exit(1);
			      }
			      else
			      {
					char ch;
					close(input[0]);
					close(output[1]);
					for(auto i=0;i<size;i++)
					{
						  ch=param[i];
						  write(input[1],&ch,1);
					}
					waitpid(id,NULL,0);
					while(read(output[0],&ch,1)>0)
					{
						  response_text.push_back(ch);
					}
					rsp->MakeStatusLine();
					rsp->SetResourceSize(response_text.size());
					rsp->MakeResponseHeader();

					conn->SendStatusLine(rsp);
					conn->SendHeader(rsp);
					conn->SendText(rsp,true);
			      }
			    return 200;
		    }
		    static int ProcessNonCgi(Connect* conn,HttpRequest* rq,HttpResponse* rsp)
		    {
			      rsp->MakeStatusLine();
			      rsp->MakeResponseHeader();
			      //rsp->MakeResponseText(rq);

			      conn->SendStatusLine(rsp);
			      conn->SendHeader(rsp);//add \n
			      conn->SendText(rsp,false);
			      LOG("Send Response Finshed!",NORMAL);
		    }
		    static int ProcessResponse(Connect* conn,HttpRequest* rq,HttpResponse* rsp)
		    {
			      if(rq->IsCgi())
			      {
					LOG("MakeResponse Use Cgi!",NORMAL);
					ProcessCgi(conn,rq,rsp);
			      }
			      else
			      {
					LOG("Process Response Use Non Cgi",NORMAL);
					ProcessNonCgi(conn,rq,rsp);
			      }
		    }
		    static void HandlerRequest(int sock)
		    {
			      pthread_detach(pthread_self());
			      int code=200;
			      Connect *conn=new Connect(sock);
			      HttpRequest *rq=new HttpRequest;
			      HttpResponse *rsp=new HttpResponse;
			      code=rsp->Code();

			      conn->RecvOneLine(rq->request_line);
			      rq->RequestLineParse();

			      if(!rq->IsMethodLegal())
			      {
					code=404;
					LOG("Request Method Is not Legal",WARNING);
					//goto end;
			      }

			      rq->UriParse();
			      if(rq->IsPathLegal(rsp)!=0)
			      {
					code=404;
					LOG("file is not exist!",WARNING);
			      }

			      conn->RecvRequestHandler(rq->request_header);
			      rq->HanderPrase();
			      if(rq->IsNeedRecv())
			      {
					LOG("POST Method,Continue Recv!",NORMAL);
					conn->RecvText(rq->request_text,rq->ContentLength());
			      }
			      LOG("Request Recv finshed!",NORMAL);
			      ProcessResponse(conn,rq,rsp);
end:
			      delete conn;
			      delete rq;
			      delete rsp;
		    }
};
#endif
