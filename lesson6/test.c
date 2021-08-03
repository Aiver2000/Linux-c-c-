#include <stdio.h>
#define M 100
//#define OS 0  //0 -》win  1-》centos
int main()
{
#if OS 
  printf("hello centos!\n");

#else
  printf("hello windows\n");
#endif 
  //printf("hello Linxu !\n");
  //printf("hello %d\n",M);
  //printf("hello Linxu !\n");
  //printf("hello Linxu !\n");
  //printf("hello Linxu !\n");
  //printf("hello Linxu !\n");
  //printf("hello Linxu !\n");
  

  return 0;
}
