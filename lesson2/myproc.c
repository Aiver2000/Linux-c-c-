#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  pid_t id = fork();
  

  if(id == 0 )
  {
    char * myls[] = {
    "ls",
    "-a",
    "-l",
    NULL
    };
    execvp("ls",myls);
    exit(1);
  }
  
  int status = 0;
  pid_t ret = waitpid(id,&status,0);
  if(ret > 0)
  {
    if(WIFEXITED(status))
    {
      printf("child exit code:%d\n",WEXITSTATUS(status));
    }
  }




  return 0;
}
