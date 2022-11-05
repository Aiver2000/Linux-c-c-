#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
int my_daemon(int nochdir,int noclose)
{
  umask(0);
  if( fork()>0){
    //father
    exit(0);
  }
  signal(SIGCHLD,SIG_IGN);
  setsid();

  if(fork()>0)
  {
    //father,防御性编程
    exit(0);
  }

  if(nochdir ==0){
    
  chdir("/");
  }
  if(noclose == 0){

    close(0);

    int fd = open("dev/null",O_RDWR);
    if(fd<0){
      return ;
    }
    dup2(fd,1);
    dup2(fd,2);
  }

  //孙子进程
  
}

int main()
{
  my_daemon(0,0);
  while(1){
    sleep(1);
  }
}
