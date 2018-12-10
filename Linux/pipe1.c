#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

//匿名管道的使用
int main()
{
	  //int pipe(int pipefd[2])
	  //pipefd 用于获取管道的操作描述符
	  //pipefd[0] 用于从管道读取数据
	  //pipefd[1] 用于向管道写入数据
	  //返回值： 成功：0  失败：-1
	  int pipefd[2];
	  //创建匿名管道
	  int ret=pipe(pipefd);
	  if(ret<0)
	  {
		    perror("pipe error!");
		    return -1;
	  }
	  //创建子进程
	  int pid=fork();
	  if(pid<0)
	  {
		    perror("fork error!");
		    return -1;
	  }
	  else if(pid==0)
	  {
		    //子进程用于从管道中读取数据
		    //因为子进程读取在父进程写入之前，这时管道中没有数据，此时子进程挂起等待数据写入
		    close(pipefd[1]);
		    char buff[1024]={0};
		    read(pipefd[0],buff,1023);
		    printf("%s\n",buff);
          }
	  else
	  {
		    //父进程用于向管道中写入数据
		    close(pipefd[0]);
		    char *ptr="leagu of lengend!";
		    write(pipefd[1],ptr,strlen(ptr));
	  }
	  waitpid(pid,NULL,0);
	  close(pipefd[0]);
	  close(pipefd[1]);
	  return 0;
}

