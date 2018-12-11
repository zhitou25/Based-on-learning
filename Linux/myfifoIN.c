//命名管道的基本使用

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	  int ret =mkfifo("./test.fifo",0664);
	  if(ret<0)
	  {
		    if(errno!=EEXIST)
		    {
			      perror("mkfifo error!");
			      return -1;
		    }
	  }
	  int fd =open("./test.fifo",O_WRONLY);
	  if(fd<0)
	  {
		    perror("open error!");
		    return -1;
	  }
	  printf("open fifo success!\n");
	  while(1)
	  {
		    char buff[1024]={0};
		    printf("please input:");
		    fflush(stdout);
		    scanf("%s",buff);
		    write(fd,buff,strlen(buff));
	  }
	  close(fd);
	  return 0;
}
