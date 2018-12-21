#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

void* thread1(void*arg);
void* thread2(void*arg);
int flag=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
int main()
{
	  pthread_t tid1,tid2;
	  int ret1=pthread_create(&tid1,NULL,thread1,&tid2);
	  if(ret1!=0)
	  {
		    printf("thread2 creat fail!\n");
		    exit(-1);
	  }

	  int ret2=pthread_create(&tid2,NULL,thread2,NULL);
	  if(ret2!=0)
	  {
		    printf("thread2 creat fail!\n");
		    exit(-2);
	  }

	  pthread_cond_wait(&cond,&mutex);
	  printf("main exit!\n");
 	  pthread_exit(0);
}

void* thread1(void*arg)
{
	  printf("this is thread1!\n");
	  printf("flag:%d  tid1:%p\n",flag,pthread_self());
	  pthread_mutex_lock(&mutex);
	  if(flag==2)
	  {
		    pthread_cond_signal(&cond);
	  }
	  flag=1;
	  printf("flag=%d\n",flag);
	  pthread_mutex_unlock(&mutex);
	  pthread_join(*(pthread_t*)arg,NULL);
	  printf("thread1 exit!\n");
	  pthread_exit(0);
}

void* thread2(void*arg)
{
	  printf("this is thread2!\n");
	  printf("flag:%d  tid2:%p\n",flag,pthread_self());
	  pthread_mutex_lock(&mutex);
	  if(flag==1)
	  {
		    pthread_cond_signal(&cond);
	  }
	  flag=2;
	  printf("flag=%d\n",flag);
	  pthread_mutex_unlock(&mutex);
	  printf("thread2 exit!\n");
	  pthread_exit(0);
}
