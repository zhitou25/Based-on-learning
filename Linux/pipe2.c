//用匿名管道来实现管道符
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main()
{
	  int pid1;
	  int pid2;
	  int pipefd[2];
        int ret=  pipe(pipefd);
	if(ret<0)
	{
		  perror("pipe error!");
		  return -1;
	}
	  if((pid1=fork()==0))
	  {
		    close(pipefd[0]);
		    dup2(pipefd[1],1);
		    execlp("ls","ls","-l",NULL);
	  }
	  if((pid2=fork()==0))
	  {
		    close(pipefd[1]);
		    dup2(pipefd[0],0);
		    execlp("grep","grep","mypipe2.c",NULL);
	  }
	  close(pipefd[0]);
	  close(pipefd[1]);
	  waitpid(pid1,NULL,0);
	  waitpid(pid2,NULL,0);
	  return 0;
}
