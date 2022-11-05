#include "comm.h"

int main()
{
  key_t k = ftok(PATHNAME,PROJ_ID);
  if(k<0){
    perror("ftok");
    return 1;
  }
  int shmid = shmget(k,SIZE,IPC_CREAT|IPC_EXCL|0644);
  if(shmid <0){
    perror("shmget");
    return 2;
  }

  
  char* mem = shmat(shmid,NULL,0);

  //TODO
  while(1){
    printf("client msg# %s \n",mem);
  
  } 

  


  shmdt(mem);

  shmctl(shmid,IPC_RMID,NULL);
  return 0;
}
