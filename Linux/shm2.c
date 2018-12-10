//共享内存的基本操作


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/shm.h>
#include<string.h>
#define IPC_KEY 0x123456


int main()
{
	 int shmid=shmget(IPC_KEY,32,IPC_CREAT | 0664);
	 if(shmid<0)
	 {
		   perror("shmget error!");
		   return -1;
	 }
	 void *shm_start=shmat(shmid,NULL,0);
	 if(shm_start==(void*)-1)
	 {
		   perror("shmat error!");
		   return -1;
	 }
	 while(1)
	 {
		printf("shm:[%s]\n",shm_start);
		sleep(1);
	 }
	 shmdt(shm_start);
	 shmctl(shmid,IPC_RMID,NULL);
	 return 0;
}







