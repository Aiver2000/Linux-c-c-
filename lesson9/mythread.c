#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

int tickets =2000;

void* TicketGrabbing(void* arg)
{
  const char* name = (char*)arg;
  while(1){
    if(tickets > 0)
    {
      usleep(10000);

      printf("[%s] get a ticket :%d \n",name,tickets--);
    }
    else{
      break;
    }
  }
  printf("%s quit!\n",name);
  pthread_exit((void*)0);

}
int main()
{
  pthread_t t1,t2,t3,t4;
  pthread_create(&t1,NULL,TicketGrabbing,"thread 1");
  pthread_create(&t2,NULL,TicketGrabbing,"thread 2");
  pthread_create(&t3,NULL,TicketGrabbing,"thread 3");
  pthread_create(&t4,NULL,TicketGrabbing,"thread 4");
  

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);


  return 0;
}























//void* Routine(void* arg)
//{
//  while(1)
//  {
//    printf("newthread:%p\n",pthread_self());
//    sleep(1);
//  }
//
//
//
//  //pthread_detach(pthread_self());
//  //char* msg =(char*)arg;
//  //int count = 0;
//  //while(count <5){
//  //  printf("%s:pid:%d ,ppid:%d ,tid:%lu\n",msg,getpid(),getppid(),pthread_self());
//  //  sleep(1);
//
// ////int a = 1/0;
//  //  count ++;
//  //}
//  //return (void*) 10;
// //exit(1); 终止进程。
// //pthread_exit((void*)19);
// //pthread_cancel(pthread_self());
//
//
//
//}
//int main()
//{
//    pthread_t tid;
//    pthread_create(&tid,NULL,Routine,NULL);
//    
//
//    while(1){
//      printf("main thread id:%p\n",pthread_self());
//      sleep(2);
//    }
//
//    pthread_join(tid,NULL);
//
//
//
//
//
//
//
////  pthread_t tid[5];
////  for(int i = 0;i<5;i++){
////    char *buffer = (char*)malloc(64);
////    sprintf(buffer,"thread %d" , i);
////    pthread_create(&tid[i],NULL,Routine,(void*)buffer);
////    printf("%s tid is : %lu \n ",buffer,tid[i]);
////  }
////  //pthread_cancel(tid[0]);
////
////  //pthread_cancel(tid[3]);
////while(1)
////{
////
////  printf("main thread :pid:%d ,ppid:%d,tid:%lu \n",getpid(),getppid(),pthread_self());
////  sleep(1);
////}
//  //printf("main thread :pid:%d ,ppid:%d,tid:%lu \n",getpid(),getppid(),pthread_self());
////  for(int i = 0;i<5;i++)
////  {
////    void* ret = NULL;
////    pthread_join(tid[i],&ret);
////
////    printf("thread %d[%lu] ... quit,code:%d \n",i,tid[i],(int)ret);
////  }
//
//  return 0;
//}

