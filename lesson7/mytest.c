#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

//void handler(int signo)
//{
//  printf("get a :%d!\n",signo);
//  int ret = 0;
//  while((ret = waitpid(-1,NULL,WNOHANG))>0)
//  {
//    printf("wait child %d  success\n!",ret);
//  }
//
//}
//
int main ()
{
  signal(17,SIG_IGN); //SIG

  if(fork() == 0)
  {
    printf("child is running ,begin dead %d\n!",getpid());
    sleep(3);
    exit(1);
  }

  while(1);

  return 0;
}




















//volatile int flag = 0;
//
//void handler(int signo)
//{
//  printf("get a %d\n",signo);
//  flag = 1;
//}
//
//int main()
//{
//  signal(2,handler);
//  while(!flag);
//  printf("Proc Normal Quit!\n");
//
//  return 0;
//}
//








//struct sigaction act,oact;
//
//void handler(int signo)
//{
//  printf("get a signal:%d\n",signo);
//  sigaction(SIGINT,&oact,NULL);
//}
//
//int main()
//{
//  memset(&act,0,sizeof(act));
//  memset(&oact,0,sizeof(oact));
//
//  act.sa_handler = handler;
//  act.sa_flags = 0;
//  sigemptyset(&act.sa_mask);
//  sigaction(SIGINT,&act,&oact);
//
//  while(1)
//  {
//    
//    printf("i am a process!\n");
//    sleep(1);
//  }
//
//  return 0;
//}
