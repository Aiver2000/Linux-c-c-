#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>


const int port = 8081;
const int num = 5;
void* Routinue (void* arg)
{
  pthread_detach(pthread_self());
  int fd = *(int*)arg;
  delete (int*)arg;

  std::cout <<"get a new link:"<<fd <<std::endl;

  while(1){
    std::cout <<"thread is running :"<<pthread_self()<<std::endl;
    sleep(1);
  }
  return nullptr;
}

int main()
{
  int lsock = socket(AF_INET,SOCK_STREAM,0);
  if(lsock <0){
    std::cerr<<"socket error" <<std::endl;
    return 1;
  }
  int opt = 1;
  setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  struct sockaddr_in local;
  memset(&local,0,sizeof(local));
  local.sin_port = htons(port);
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = INADDR_ANY;
  if(bind(lsock,(struct sockaddr*)&local,sizeof(local)) < 0){
    std::cerr << "bind error" <<std::endl;
    return 2;
  }
  if(listen(lsock,num) < 0){
    std::cerr<<"listen error " <<std::endl;
    return 3;
  }

  struct sockaddr_in peer;
  for(;;){
    socklen_t len = sizeof(peer);
    int sock = accept(lsock,(struct sockaddr*)&peer,&len);
    if(sock <0){
      std::cerr<<"accept error" <<std::endl;
      continue;
    }

    int *p = new int(sock);
    pthread_t tid;
    pthread_create(&tid,nullptr,Routinue,p);

  }





  return 0;
}
