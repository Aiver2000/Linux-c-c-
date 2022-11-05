#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM 10000

int tickets = NUM;
pthread_mutex_t lock;

void* GetTicket(void* arg)
{
  int number = (int)arg;
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(tickets > 0)
    {
      usleep(100);
      printf("thread[%d] 抢票: %d\n",number,tickets--);
      pthread_mutex_unlock(&lock);
    }
    else 
    {
      pthread_mutex_unlock(&lock);
      break;
    }
  }

}
int main()
{
  pthread_t thds[5];
  pthread_mutex_init (&lock,NULL);
  for(int i = 0;i<5;i++)
  {
  
    pthread_create(&thds[i],NULL,GetTicket,(void*)i);
  }

  for(int i = 0;i<5;i++)
  {
    pthread_join(thds[i],NULL);
  }

  pthread_mutex_destroy(&lock);
  return 0;
}
