#include "proc.h"

void Count()
{
  int i = 10;
  while(i){
    printf("%2d\r",i--);
    fflush(stdout);
    sleep(1);
  }
}

void ProcBar()
{
  int i = 0;
  char proc[102];
  memset(proc,'\0',sizeof(proc));
  const char* lable="|/-\\";
  while(i<=100){

    printf("[\033[0m\033[1;31m%-100s\033[0m][%d%%][%c]\r",proc,i,lable[i%4]);
    //printf("[%-100s][%d%%][%c]\r",proc,i,lable[i%4]);
    fflush(stdout);
    proc[i] = '#'; 
    usleep(10000);
    i++;
    
  }
  printf("\n");
}
