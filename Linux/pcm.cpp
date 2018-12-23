#include<iostream>
#include<queue>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

/*
 *生产者与消费者模型
 *
 *多生产者，多消费者
 *
 */
class BlockQueue {
private:
	std::queue<int> _list;
	int _cap;
	pthread_mutex_t _mutex;
	pthread_cond_t _productor;
	pthread_cond_t _consumer;

	bool QueueIsFull()
	{
		return (_list.size() == _cap ? true : false);
	}
	bool QueueIsEmpty()
	{
		return (_list.size() == 0 ? true : false);
	}
public:
	BlockQueue(int cap = 10) :_cap(cap)
	{
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_productor, NULL);
		pthread_cond_init(&_consumer, NULL);
	}
	~BlockQueue()
	{
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_productor);
		pthread_cond_destroy(&_consumer);
	}
	bool QueuePush(int data)
	{
		pthread_mutex_lock(&_mutex);
		while (QueueIsFull())
		{
			printf("queue full!\n");
			pthread_cond_wait(&_productor, &_mutex);
		}
		_list.push(data);
		pthread_mutex_unlock(&_mutex);
		pthread_cond_signal(&_consumer);
	}
	bool QueuePop(int *data)
	{
		pthread_mutex_lock(&_mutex);
		while (QueueIsEmpty())
		{
			printf("queue empty!\n");
			pthread_cond_wait(&_consumer, &_mutex);
		}
		*data = _list.front();
		_list.pop();
		pthread_mutex_unlock(&_mutex);
		pthread_cond_signal(&_productor);
	}
};


void *pfun(void *arg)
{
	BlockQueue *q = (BlockQueue*)arg;
	int count = 0;
	while (1)
	{
		q->QueuePush(count++);
		printf("push data!\n");
		sleep(1);
	}
	return NULL;
}
void *cfun(void *arg)
{
	BlockQueue *q = (BlockQueue*)arg;
	int data;
	while (1)
	{
		q->QueuePop(&data);
		printf("pop data!\n");
	}
	return NULL;
}






int main()
{
	BlockQueue q;
	int ret = 0;
	pthread_t ptid[4], ctid[4];
	for (int i = 0; i < 4; i++)
	{
		ret = pthread_create(&ptid[i], NULL, pfun, (void*)&q);
		if (ret != 0)
		{
			printf("pthread create fail!\n");
			return -1;
		}

		pthread_create(&ctid[i], NULL, cfun, (void*)&q);
		if (ret != 0)
		{
			printf("pthread create fail!\n");
			return -1;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		pthread_join(ptid[i], NULL);
		pthread_join(ctid[i], NULL);
	}
	return 0;
}







