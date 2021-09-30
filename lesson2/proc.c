#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main ()
{
  pid_t id = fork();
  if(id == 0)
  {
    printf("i am child process\n");
    sleep(10);
    exit(7);
  }

  int status = 0;
  pid_t ret = waitpid(id,&status,0);
  if(ret > 0)
  {
   if(WIFEXITED(status))
   {
     printf("child exit code : %d\n",WEXITSTATUS(status));
   }
   else{
     printf("child not normal exit\n");
   }
  }







  return 0;
}
