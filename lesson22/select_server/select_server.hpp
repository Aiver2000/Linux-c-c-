#pragma once 

#include "sock.hpp"
#include <sys/select.h>
#include <unordered_map>

#define BACKLOG 5
#define NUM 1024
#define DFL_FD -1

namespace ns_select{
    
  struct bucket
  {
    public:
    std::string inbuffer;

    std::string outbuffer;
    int in_curr;
    int out_curr;

    public:
    bucket():in_curr(0),out_curr(0)
    {}
  }

  class SelectServer{
    private:
      int listen_sock;
      unsigned short port;
      std::unordered_map<int,bucket> buckets;

    public:
      SelectServer(unsigned short _port) :port(_port)
      {}

      void InitSelectServer()
      {

        listen_sock = ns_sock::Sock::Socket();
        ns_sock::Sock::Bind(listen_sock,port); 
        ns_sock::Sock::Listen(listen_sock,BACKLOG);
      }

      void Run()
      {
        
        fd_set rfds;
        int fd_array[NUM] = {0};
        ClearArray(fd_array,NUM,DFL_FD);
        fd_array[0] = listen_sock;

        for( ; ; ){
          struct timeval timeout = {5,0};
          int max_fd = DFL_FD; 
          FD_ZERO(&rfds);
          for(auto i = 0; i <NUM;i++)
          {
              if(fd_array[i] == DFL_FD)
              {
                continue;
              }
              FD_SET(fd_array[i],&rfds);
              if(max_fd<fd_array[i])
              {
                max_fd = fd_array[i];
              }

          }
          switch(select(max_fd + 1 ,&rfds,nullptr,nullptr,/*&timeout*/nullptr)){
              case 0:
                std::cout<<"time out" <<std::endl;
                break;
              case -1:
                std::cerr<<"select error " <<std::endl;
                break;
              default:
                
                //std::cout <<"有事件发生。。。timeout:"<<timeout.tv_sec<<std::endl;

                HandlerEvent(rfds,fd_array,NUM);

                break;
          } //endl switch 
        } // end for 
      } 

      void HandlerEvent(const fd_set& rfds ,int fd_array[],int num) 
      {

        for(auto i = 0;i<num;i++)
        {
          if(fd_array[i] == DFL_FD)
          {
            continue;
          }
          if(fd_array[i] == listen_sock && FD_ISSET(fd_array[i],&rfds ))
          {
            //是一个合法fd，且链接事件就绪
            struct sockaddr_in peer; 
            socklen_t len = sizeof(peer);

            int sock =  accept(fd_array[i],(struct sockaddr*)&peer,&len);           
            if(sock <0)
            {
                std::cerr<<"accept error" <<std::endl;
                continue;
            }
            uint16_t  peer_port = htons(peer.sin_port);
            std::string peer_ip = inet_ntoa(peer.sin_addr);
            struct bucket b;
            buckets.insert({sock,b});
            std::cout<<"get a new link:"<<peer_ip<<":" <<peer_port <<std::endl;


            //recv?????select 等待数据就绪
            if(!AddFdToArray(fd_array,num,sock))
            {
                close(sock);
                std::cout <<"select server is full,close fd" <<std::endl;
            }
            
          }
          else 
          {
            //只处理正常的fd
            if(FD_ISSET(fd_array[i],&rfds))
            {
              //读数据事件就绪
              char buffer[1024];
              //1.定制协议
              //2.给每一个socket定义对应的缓冲区

              ssize_t s = recv( fd_array[i],buffer,sizeof(buffer)-1,0 ); 
              if(s > 0 )
              {

                buffer[s] = 0;
                buckets[fd_array[i]].inbuffer = buffer;
                std::cout <<"echo#" <<buffer <<std::endl;
              }
              
              else if(s == 0)
              {
                std::cout <<"client quit" <<std::endl;
                close (fd_array[i]);
                fd_array[i] = DFL_FD;

              }
              else 
              {
                std::cerr<<"recv error " <<std::endl;
              }
            }
            else 
            {

            }
          }
        }
      }

      ~SelectServer()
      {}

    private:
      void ClearArray(int fd_array[],int num,int default_fd)
      {
        for(auto i = 0; i< num;i++)
        {
          fd_array[i] = default_fd;
        }
      }
      bool AddFdToArray(int fd_array[],int num ,int sock)
      {
        for(int i = 0; i <num ;i++)
        {
          if(fd_array[i] == DFL_FD)
          {
            fd_array[i] = sock;
            return true;
          }
        }

        //没有空间了。
        
        return false;
      }


  };


}
