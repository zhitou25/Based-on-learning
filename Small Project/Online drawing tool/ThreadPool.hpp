#ifndef _THREADPOOL_HPP_
#define _THREADPOOL_HPP_
#include<iostream>
#include<queue>
#include<pthread.h>


typedef void(*headler_t)(int);

class Task
{
	  private:
	       int sock;
	       headler_t headler;
	  public:
	       Task(int _sock,headler_t _headler):sock(_sock),headler(_headler)
	  {}
	       void Run()
	       {
		headler(sock);	 
	       }
	       ~Task()
	       {}
};
class ThreadPool
{
	  private:
	      int num;
	      int idle_num;//等待线程
	      std::queue<Task> task_queue;
	      pthread_mutex_t lock;
	      pthread_cond_t  cond;
	  public:
	      ThreadPool(int num_):num(num_),idle_num(0)
	  {
		    pthread_mutex_init(&lock,NULL);
		    pthread_cond_init(&cond,NULL);
	  }
	      void InitThreadPool()
	      {
			pthread_t tid;
			for(auto i=0;i<num;i++)
			{
			pthread_create(&tid,NULL,ThreadRoutine,(void*)this);
			}
	      }
	      bool IsTaskQueueEmpty()
	      {
			return task_queue.size()==0;
	      }
	      void LockQueue()
	      {
			pthread_mutex_lock(&lock);
	      }
	      void UnLockQueue()
	      {
			pthread_mutex_unlock(&lock);
	      }
	      void Idle()
	      {
			idle_num++;
			pthread_cond_wait(&cond,&lock);
			pthread_mutex_destroy(&lock);
			idle_num--;
	      }
	      Task PopTask()
	      {
			Task t=task_queue.front();
			task_queue.pop();
			return t;
	      }
	      void PushTask(Task& t)
	      {
			LockQueue();
			task_queue.push(t);
			UnLockQueue();
			Wakeup();
	      }
	      void Wakeup()
	      {
			pthread_cond_signal(&cond);
	      }
	      static void* ThreadRoutine(void* arg)
	      {
			pthread_detach(pthread_self());
			ThreadPool *tp=(ThreadPool*)arg;

			for(;;)
			{
				  tp->LockQueue();
				  while(tp->IsTaskQueueEmpty())
				  {
					    tp->Idle();
				  }
				  Task t=tp->PopTask();
				  tp->UnLockQueue();
				  std::cout<<"task by headler"<<pthread_self()<<std::endl;
				  t.Run();
			}
	      }
	      ~ThreadPool()
	      {
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
	      }
};

class singleton
{
	  private:
	       static ThreadPool *p;
	       static pthread_mutex_t lock;
	  public:
	       static ThreadPool* GetInstance()
	       {
			 if(NULL==p)
			 {
				   pthread_mutex_lock(&lock);
				   if(NULL==p)
				   {
					     p=new ThreadPool(5);
					     p->InitThreadPool();
				   }
				   pthread_mutex_unlock(&lock);
			 }
			 return p;
	       }
};
ThreadPool *singleton::p=NULL;
pthread_mutex_t singleton::lock=PTHREAD_MUTEX_INITIALIZER;

#endif
