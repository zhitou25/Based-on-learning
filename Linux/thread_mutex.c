#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sched.h>
/*
//多线程并发的操作共享变量
int ticket=10;
void *route(void *arg)
{
        char*id=(char*)arg;
	while(1)
	{
		  if(ticket>0)
		  {
			    //挂起调用该函数的线程，单位是微秒
			    usleep(1000);
			    printf("%s sells ticket:%d\n",id,ticket);
			    ticket--;
			    sleep(3);
		  }
		  else
		  {
			    break;
		  }
	}
}
*/
//通过添加互斥量解决并发问题
int ticket=10;
pthread_mutex_t mutex;
void *route(void *arg)
{
        char*id=(char*)arg;
	while(1)
	{
                  //添加互斥量
		  pthread_mutex_lock(&mutex);
		  if(ticket>0)
                  {
			    //挂起调用该函数的线程，单位是微秒
			    usleep(1000);
			    printf("%s sells ticket:%d\n",id,ticket);
			    ticket--;
			    //解锁互斥量
			    pthread_mutex_unlock(&mutex);
			    //放弃cpu，让其它线程也可以被执行
			    sched_yield();
		  }
		  else
		  {
			    pthread_mutex_unlock(&mutex);
			    break;
		  }
	}
}
int main(void)
{
	  pthread_t t1,t2,t3,t4;
          //初始化互斥量
	  pthread_mutex_init(&mutex,NULL);

	  pthread_create(&t1,NULL,route,"thread t1");
	  pthread_create(&t2,NULL,route,"thread t2");
	  pthread_create(&t3,NULL,route,"thread t3");
	  pthread_create(&t4,NULL,route,"thread t4");

	  pthread_join(t1,NULL);
	  pthread_join(t2,NULL);
	  pthread_join(t3,NULL);
	  pthread_join(t4,NULL);
          //销毁互斥量
	  pthread_mutex_destroy(&mutex);
	  
	 return 0; 
}


