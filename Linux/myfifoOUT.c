//命名管道的基本使用

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>


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
	  int fd =open("./test.fifo",O_RDONLY);
	  if(fd<0)
	  {
		    perror("open error!");
		    return -1;
	  }
	  printf("open fifo success!\n");
	  while(1)
	  {
		    char buff[1024]={0};
		    read(fd,buff,1023);
		    printf("read buff:%s\n",buff);
	  }
	  close(fd);
	  return 0;
}
