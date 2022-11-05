#include "comm.h"
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
  if(mkfifo(FILE_NAME,0644) <0)
  {
    perror("mkfifo");
    return 1;
  }
  
  int fd = open(FILE_NAME,O_RDONLY);
  if(fd <0){
    perror("open error!\n");
    return 2;
  }
  
  int out = open("file-bak.txt",O_CREAT|O_WRONLY,0644);

  char msg[128];
  while(1){
      msg[0] = 0;
      ssize_t s = read(fd,msg,sizeof(msg)-1);
      if(s>0){
          write(out,msg,s);
      







//        msg[s] = 0;
//        printf("client# %s \n",msg);
//        char* p = msg;
//        int flag = 0;
//        const char* lable = "+-*/%";
//        while(*p){
//          switch(*p){
//            case '+':
//                flag = 0;
//                break;
//            case '-':
//                flag = 1;
//                break;
//            case '*':
//                flag = 2;
//                break;
//            case '/':
//                flag = 3;
//                break;
//
//            case '%':
//                flag = 4;
//                break;
//          }
//          p++;
//        }
//        char* data1 = strtok(msg,"+-*/%");
//        char* data2 = strtok(NULL,"+-*/%");
//        int x = atoi(data1);
//        int y = atoi(data2);
//
//        int z = 0;
//        switch(flag){
//          case 0:
//            z = x+y;
//            break;
//          case 1:
//            z = x-y;
//            break;
//          case 2:
//            z = x*y;
//            break;
//          case 3:
//            z = x/y;
//            break;
//          case 4:
//            z = x%y;
//            break;
//                   
//        }          
//
//        printf("%d %c %d = %d \n",x,lable[flag],y,z);
//


        //if(fork()==0)
        //{
        //  //child
        //  execlp(msg,msg,NULL);
        //  exit(1);
        //}
        //waitpid(-1,NULL,0);
      }
      else if(s==0){
        printf("client quit!\n");
        break;
      }
      else{
        printf("read error!\n");
        break;
      }
      
 }

  close (fd);
  close(out);
  return 0;
}
