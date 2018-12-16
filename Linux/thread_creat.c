
//线程的创建和退出

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<pthread.h>

void *thr_start(void *arg)
{
	  
	  pthread_exit("common thread exit");//结束调用pthread_exit()的线程
	  while(1)
	  {
	  printf("i am common thread:) %p\n",pthread_self());//打印创建线程的入口地址
	  sleep(1);
	  }
	  return NULL;
}

 int main()
{
	  pthread_t tid;
	  int ret=pthread_create(&tid,NULL,thr_start,(void*)tid);//创建一个线程并接收整型返回值来判断线程是否创建成功
	  if(ret!=0)
	  {
		    perror("thread create is fail!\n");
		    return -1;
	  }
	 char* ptr;
	 pthread_join(tid,(void**)&ptr);//等待指定的线程退出，并用ptr接受其返回值
	 printf("common thread retval:%s\n",(char*)ptr);//打印返回值
	  while(1)
	  {
		    printf("i am main thread:)\n");
		    sleep(1);
	  }
	  return 0;
}
