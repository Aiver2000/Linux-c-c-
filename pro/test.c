#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<stdlib.h>
int main()
{
//  while(1) 
//  {
//    sleep(1);
//    printf("pid:%d\n",getpid());
//    printf("ppid:%d\n",getppid());
//  }
//
  pid_t id  = fork();
  if(id<0)
  {
    perror("fork");
    return 1;

  }
  else if(id == 0)
  {
    //child
    printf("child:%d is begin",getpid());
    sleep(50);

    exit(EXIT_SUCCESS);
  
  }
  else
  {
    //father
    
    printf("parent:%d is sleeping.. \n",getpid());
    sleep(3);
  
  }
  
  return 0;
}

