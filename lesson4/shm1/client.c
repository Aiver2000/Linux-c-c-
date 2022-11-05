#include "comm.h"
int main()
{

  key_t k = ftok(PATHNAME,PROJ_ID);
  if(k<0){
    perror("ftok");
    return 1;
  }

  int shmid = shmget(k,SIZE,IPC_CREAT);
  if(shmid <0){
    perror("shmget");
    return 2;
  }


  char* mem = shmat(shmid,NULL,0);



  //TODO
  
  int i = 0;
  while(1){
    mem[i] = 'A'+i;
    i++;
    sleep(1);
    mem[i]= '\0';
  
  
  }


  shmdt(mem);

  return 0;
}
