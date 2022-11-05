#pragma once

#include "sock.hpp"
#include <string>
#include <sys/epoll.h>
#include <unordered_map>
namespace ns_epoll{

#define MAX_NUM 64

  class Epoller;
  class EventItem; 

  typedef int(*callback_t)(EventItem*);
  const int size = 256;


  class EventItem{

    public:
      int sock;
      Epoller *R;

      callback_t recv_handler;
      callback_t send_handler;
      callback_t error_handler;
      
      std::string inbuffer;
      std::string outbuffer;
    public:
      EventItem():sock(0),R(nullptr),recv_handler(nullptr),send_handler(nullptr),error_handler(nullptr)
      {}

      void ManagerCallBack(callback_t _recv,callback_t _send,callback_t _err)
      {
          recv_handler = _recv;
          send_handler = _send;
          error_handler = _err;

      }


      ~EventItem()
      {

      }

  };


  class Epoller{
      private:
        int epfd;
        std::unordered_map<int,EventItem> event_items;
      public:
        Epoller():epfd(-1)
        {}

      public:
        void InitEpoller()
        {
          if((epfd = epoll_create(size))<0)
          {
            std::cerr<<"epoll create error!\n" <<std::endl;
            exit(4);
          }
        }

        void AddEvent(int sock,uint32_t event,const EventItem& item)
        {
          struct epoll_event ev;
          ev.events = 0;
          ev.events |= event;
          ev.data.fd = sock;
          if(epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev) <0)
          {
            std::cerr<<"epoll_ctl error ,fd :" <<sock<<std::endl;
          }
          else 
          {
            event_items.insert({sock,item});
          }
          std::cout <<"debug:" <<"添加："<<sock<<"到epoller中,finished"<<std::endl;
        }
        void DelEvent(int sock)
        {
          if(epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr) < 0)
          {
            std::cerr<<"epoll_ctl_error.fd"<<sock<<std::endl;
          }
          event_items.erase(sock);
        }


        void EnableReadWrite(int sock,bool read,bool write)
        {
          struct epoll_event evt;
          evt.data.fd = sock;
          evt.events = (read ? EPOLLIN:0) |(write ?EPOLLOUT:0) |EPOLLET;
          if(epoll_ctl(epfd,EPOLL_CTL_MOD,sock,&evt)<0)
          {
              std::cerr<<"epoll_ctl_mod error,fd:" <<sock<<std::endl;
          }
        }

        void Dispatch(int timeout)
        {
          struct epoll_event revs[MAX_NUM];
          int num = epoll_wait(epfd,revs,MAX_NUM,timeout);
          for(int i = 0;i<num;i++)
          {
              int sock = revs[i].data.fd;
              if((revs[i].events &EPOLLERR )||(revs[i].events & EPOLLHUP))
                if(event_items[sock].error_handler) event_items[sock].error_handler(&event_items[sock]);
              if(revs[i].events & EPOLLIN)
                if(event_items[sock].recv_handler) event_items[sock].recv_handler(&event_items[sock]);
              if(revs[i].events & EPOLLOUT)
                if(event_items[sock].send_handler) event_items[sock].send_handler(&event_items[sock]);
          }
        }

        ~Epoller()
        {
          if(epfd>=0) close(epfd);
        }


  };

}
