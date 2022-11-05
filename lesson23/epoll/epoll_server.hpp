#pragma once

#include "sock.hpp"

#include <sys/epoll.h>
namespace ns_epoll{

#define MAX_NUM 64
  const int back_log = 5;
  const int size = 256;

  class EpollServer{
      private:
        int listen_sock;
        int epfd;
        uint16_t port;
      public:
        EpollServer(int _port):port(_port)
        {}

      public:
        void InitEpollServer()
        {

          listen_sock = ns_sock::Sock::Socket();
          ns_sock::Sock::Bind(listen_sock,port);
          ns_sock::Sock::Listen(listen_sock,back_log);
          
          std::cout <<"debug.listen_sock:" <<listen_sock<<std::endl;
          if((epfd = epoll_create(size))<0)
          {
            std::cerr<<"epoll create error!\n" <<std::endl;
            exit(4);
          }
          std::cout<<"debug.epfd:"<<epfd<<std::endl;
        
        }

        void AddEvent(int sock,uint32_t event)
        {
          struct epoll_event ev;
          ev.events = 0;
          ev.events |= event;
          ev.data.fd = sock;
          if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev) <0)
          {
            std::cerr<<"epoll_ctl error ,fd :" <<sock<<std::endl;
          }
        }
        void DelEvent(int sock)
        {
          if(epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr) < 0)
          {
            std::cerr<<"epoll_ctl_error.fd"<<sock<<std::endl;
          }
        }
        void Run()
        {
          AddEvent(listen_sock,EPOLLIN);
          int timeout = -1;
          struct epoll_event revs[MAX_NUM];
          for(;;)
          {
              
              int num = epoll_wait(epfd,revs,MAX_NUM,timeout);
              if(num >0)
              {
                for(int i = 0;i<num;i++)
                {
                  int sock = revs[i].data.fd;
                  if(revs[i].events & EPOLLIN)
                  {
                      //1.listen链接事件就绪
                      //2.sock可读事件就绪
                      if(sock == listen_sock)
                      {
                          struct sockaddr_in peer;
                          socklen_t len = sizeof(peer);
                          int sk = accept(listen_sock,(struct sockaddr*)&peer,&len);     
                          if(sk<0)
                          {
                            std::cout <<"accept error" <<std::endl;
                            continue;
                          }
                          //read,recv?连上一定有数据吗？
                          std::cout<<"get a new link :" <<inet_ntoa(peer.sin_addr)<<":" <<ntohs(peer.sin_port)<<std::endl;
                          AddEvent(sk,EPOLLIN);
                          
                      }
                      else 
                      {
                          char buffer[1024];
                          ssize_t s = recv(sock,buffer,sizeof(buffer)-1,0);
                          //bug
                          if(s>0)
                          {
                            buffer[s] = 0;
                            std::cout <<buffer <<std::endl;
                          }
                          else
                          {
                            std::cout <<"client close"<<std::endl;
                            close(sock);
                            DelEvent(sock);
                          }
                      }

                  }
                  else if(revs[i].events & EPOLLOUT)
                  {

                  }
                  else 
                  {

                  }
                }

                //std::cout <<"有事件发生了"<<std::endl;
              }
              else if(num ==0)
              {
                  std::cout<<"timeout" <<std::endl;
              }
              else 
              {
                  std::cout<<"epoll error" <<std::endl;
              }
          }
        }

        ~EpollServer()
        {
          if(listen_sock >=0) close(listen_sock);
          if(epfd>=0) close(epfd);
        }


  };

}
