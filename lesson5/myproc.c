#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo)
{
  printf("got a singal! signo:%d\n",signo);
}

int main()
{
    for(int signo = 1;signo<32;signo++)
    {
      signal(signo,handler);
    }
    while(1)
    {
      sleep(1);
    }
     













//  signal(2,handler);
  

  //while(1){
  //printf("hello bit\n");
  //sleep(1);
  //int a[10];
  //for(int i = 0;i<100000;i++)
  //{
  //  a[i] = i;
  //}
  //
  //}
//  if(fork() == 0)
//  {
//    printf("I an a child,pid:%d \n",getpid());
//    sleep(3);
//    //int a = 10;
//    int* p =NULL;
//    *p = 100;
//    
//    exit(0);
//  }
//  
//  int status = 0; 
//
//  waitpid(-1,&status,0);
//  printf("exit code:%d ,core dump:%d,signal:%d \n",(status>>8)&0xff,
//      status&0x80,status & 0x7f);
//  
//
//
//
//








}
