#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#define BACKLOG 5


class TcpServer
{
  private:
    int port;
    int listen_sock;
  public:
    TcpServer(int _port) :port(_port),listen_sock(-1)
    {}
    
    bool InitTcpServer()
    {
        listen_sock = socket(AF_INET,SOCK_STREAM,0);
        if(listen_sock < 0 )
        {
           std::cerr <<"socket error"<<std::endl;
           return false;
        }

        struct sockaddr_in local;
        memset(&local,0,sizeof(local));
        
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;


        if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
        {
          std::cerr<<"bind error" <<std::endl;
          return false;
        }
        if(listen(listen_sock, BACKLOG) <0)
        {
          std::cerr<< "listen error" << std::endl;
          return false;
        }

        return true;
    }
    void Loop()
    {
      for(;;)
      {   
          struct sockaddr_in peer;
          socklen_t len = sizeof(peer);

          int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
          if(sock<0)
          {
              std::cout <<"accept error" <<std::endl;
              continue;
          }
          std::cout<<"get a new link : " <<sock<<std::endl;
      }
    }

    ~TcpServer()
    {}


};
