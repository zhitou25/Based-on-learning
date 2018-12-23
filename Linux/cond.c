/*
 * 演示线程同步
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_cond_t cond1;
pthread_cond_t cond2;
pthread_mutex_t mutex;
int ticket = 0;
/*
 * 一个生产者，一个消费者；
 * fun1看作生产者，fun2看作消费者；
 *使用条件变量来同步生产者和消费者之间的操作，即线程同步；
 *在tid1、tid2线程中加锁是因为当有多个tid2（消费者）时（这里只创建了一个tid2）* *，会发生争抢；
 *
 *
 * 当tid2（消费者）先获得cpu片时间，但因为ticket=0，所以此时会在条件变量cond2处 *阻塞，等到tid1（生产者）获得cpu片时间，先判断ticket是否等于1，也就是判断ticke *t是否被售出，如果没有则等待售出，这里ticket初始化为0，表示已售出，所以改变tic *ket的值，然后发送信号给tid2，tid2获得信号，改变阻塞状态，继续执行。
 */

void *fun1(void*arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		while (ticket == 1)
		{
			pthread_cond_wait(&cond1, &mutex);
		}
		printf("ticket=1\n");
		ticket = 1;
		pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *fun2(void*arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		while (ticket == 0)
		{
			pthread_cond_wait(&cond2, &mutex);
		}
		sleep(1);
		printf("ticket=0\n");
		ticket = 0;
		pthread_cond_signal(&cond1);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}


int main()
{
	pthread_t tid1, tid2;
	int ret;
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_mutex_init(&mutex, NULL);
	ret = pthread_create(&tid1, NULL, fun1, NULL);
	if (ret != 0)
	{
		printf("thread1 create fail!\n");
		return -1;
	}
	ret = pthread_create(&tid2, NULL, fun2, NULL);
	if (ret != 0)
	{
		printf("thread2 create fail!\n");
		return -1;
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond2);
	pthread_mutex_destroy(&mutex);
	return 0;
}



