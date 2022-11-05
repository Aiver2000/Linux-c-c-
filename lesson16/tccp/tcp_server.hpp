#pragma once 

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include "ThreadPool.hpp"
#include "Task.hpp"

#define DFL_PORT 8081
#define BACK_LOG 5


class Prama{
  public:
    int sock;
    std::string ip;
    int port;
  public:
    Prama(int _sock,std::string _ip,int _port)
      :sock(_sock),ip(_ip),port(_port)
    {}
    ~Prama()
    {}
};



class TcpServer
{
  private:
    int listen_sock;
    int port;
    ThreadPool<Task> *tp;
  public:
    TcpServer(int _port = DFL_PORT):port(_port),listen_sock(-1),tp(nullptr)
    {}
    
    void InitServer()
    {
        listen_sock = socket(AF_INET,SOCK_STREAM,0);
        if(listen_sock <0)
        {
            std::cerr<<"socket error" << std::endl;
            exit(2);
        }


        struct sockaddr_in local;
        memset(&local,0,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;


        if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
        {

            std::cerr<<"bind error" << std::endl;
            exit(3);
        }


        if(listen(listen_sock,BACK_LOG)<0)
        {
            std::cerr<<"listen_error" << std::endl;
            exit(4);
        }

        tp = new ThreadPool<Task>();
    }


    //static void* HandlerRequest(void * arg)
    //{
    //  Prama *p = (Prama*)arg;

    //  pthread_detach(pthread_self());
    //  Service(p->sock,p->ip,p->port);
    //  
    //  close(p->sock);
    //  delete p;
    //  return nullptr;

    //}
    void Loop()
    {
      //signal(SIGCHILD,SIG_IGN);
      tp->InitThreadPool();

      struct sockaddr_in peer;

      for(;;)
      {
         socklen_t len = sizeof(peer);
         int sock = accept(listen_sock,(struct sockaddr*)&peer,&len); 
         if(sock < 0)
         {
            std::cout <<"accept error,continue next" <<std::endl;
            continue;

         }
         std::string ip = inet_ntoa(peer.sin_addr);
         int port = ntohs(peer.sin_port);
         Task t(sock,ip,port);
         tp->Push(t);


        








         //pthread_t tid;
         //std::string ip = inet_ntoa(peer.sin_addr);
         //int port = ntohs(peer.sin_port);
         //Prama *p = new Prama(sock,ip,port);
         //pthread_create(&tid,nullptr,HandlerRequest,p);
         


         //pid_t id = fork();
         //if(id ==0)
         //{
         //  close(listen_sock);
         //  if(fork() >0)
         //  {
         //    //爸爸进程
         //    exit(0); 
         //    
         //  }
         //   std::string ip = inet_ntoa(peer.sin_addr);
         //   int port = ntohs(peer.sin_port);
         //   std::cout <<"get a new link ["<<ip<<"] : "<<port<<std::endl;
         //   
         //   Service(sock,ip,port); //孙子进程,孤儿进程
         //   exit(0);
         //     
         //}
         ////waitpid();

         //close(sock);
         //waitpid(id,nullptr,0);
         
      }
    }



    ~TcpServer()
    {
      if(listen_sock >= 0 ) close (listen_sock);
    }

};
