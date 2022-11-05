#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int count = 0;
void handler(int signo)
{
  alarm(1);
  printf("count:%d\n",count);

}

int main ()
{
    signal(SIGALRM,handler);

    alarm(1);

    while(1)
    {
      count++;
    }
}
