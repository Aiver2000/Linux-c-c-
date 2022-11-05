#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
//child -> write  ,father -> read
int main()
{
  int fd[2] = {0};
  if(pipe(fd)<0)
  {
    perror("pipe!");
    return 1;
  }

  //printf("fd[0]: %d \n",fd[0]);
  //printf("fd[0]: %d \n",fd[1]);
  
  pid_t id = fork();
  if(id == 0)
  {
    //child
    
    close(fd[0]); 
    const char* msg = "hello father, im child";
    int count = 5;
    while(count)
    {
      if(count ==2 )
      {
        sleep(1000); 
      }
      else 
      {
        count--;
        write(fd[1],msg,strlen(msg));
      }

     // count--;
      //printf(".");
     // fflush(stdout);
    //  sleep(1);
    }
    close(fd[1]);
    exit(0);

  }

  close(fd[1]);
  char buff[64];
  while(1)
  {
   
   ssize_t s = read(fd[0],buff,sizeof(buff));
   if(s>0)
   {
     buff[s] = '\0';
     printf("child send to father# %s\n",buff);
   }
   else if(s == 0)
   {
     printf("read file end!\n");
     break;
   }
   else 
   {
     printf("read error!\n");
     break;
   }
  }
  //father
  waitpid(id,NULL,0);
  return 0;
}
