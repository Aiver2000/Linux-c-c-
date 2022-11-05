#include "comm.h"


int main()
{
  int fd = open(FILE_NAME,O_WRONLY);
  if(fd <0)
  {
    printf("open error!\n");
    return 1;
  }

  int in = open("file.txt",O_RDONLY); 
  char msg[128];

  while(1)
  {
    msg[0] = 0;
   // printf("Please Enter# ");
   // fflush(stdout);
    dup2(in,0);
    ssize_t s = read(0,msg,sizeof(msg));
    if(s == sizeof(msg) )
    {
      msg[s-1] = 0;
      write(fd,msg,s);
    }
    else if(s < sizeof(msg)){
      
      write(fd,msg,s);
      printf("read end of file!\n");
      break;
    }
    else{
      break;
    }
  }

  close(in); 
  close(fd);

  return 0;
}
