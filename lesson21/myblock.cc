#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


bool SetNonBlock(int fd)
{
  int fl =  fcntl(fd,F_GETFL);
  if(fl < 0){
    std::cerr <<"fcntl error" <<std::endl;
    return false;
  }

  fcntl(fd,F_SETFL,fl|O_NONBLOCK);
  return true;

}

void handler(int signal)
{
  std::cout <<"get a signal: "<<signal <<std::endl;
}




int main()
{
#define NUM 1024

  //SetNonBlock(0);
  
  signal(29,handler);
  while(true){
    std::cout <<"other thing......\n" <<std::endl;
    sleep(1);
    char buffer[NUM];
    ssize_t size = read(0,buffer,sizeof(buffer)-1);
    if(size <0){
      if(errno == EAGAIN||errno == EWOULDBLOCK){
        std::cout<<"数据未就绪，请轮询检测！" <<std::endl;
        sleep(1);
        continue;
      }
      if(errno == EINTR){
        std::cout <<"底层数据就绪未知，被信号打断导致返回！"<<std::endl;
        continue;
      }
      else{
        std::cerr <<"read error : " <<size <<"   errno:" << errno<< std::endl;
        break;
      }
      //break;
      continue;
    }
    buffer[size] = 0;
    std::cout<<"echo#" <<buffer<<std::endl;


  }

}
