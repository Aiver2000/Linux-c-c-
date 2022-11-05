#pragma once 

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEFAULT 8081
class UdpServe{
  private:
      int port;
      int sockfd;
      //std::string ip;
      
  public:
      UdpServe(int _port = DEFAULT):port(_port),sockfd(-1)
      {}

      bool InitUdpServer()
      {
          sockfd = socket(AF_INET,SOCK_DGRAM,0);
          if(sockfd < 0)
          {
              std::cerr<<"socket error " << std::endl;
              return false;
          }

          std::cout <<"socket create success ,sockfd :" <<sockfd <<std::endl;


          struct sockaddr_in local;
          memset(&local,'\0',sizeof(local));
          local.sin_family = AF_INET;
          local.sin_port = htons(port);
         // local.sin_addr.s_addr = inet_addr(ip.c_str());
          local.sin_addr.s_addr = INADDR_ANY;
          if(bind(sockfd,(struct sockaddr*)&local,sizeof(local))< 0)
          {
            std::cerr<<"bind error" <<std::endl;
            return false;
          }
          std::cout <<"bind success :" <<std::endl;
          
          return true;
      }

      void Start()
      {
#define SIZE 128
        char buffer[SIZE];
        for(;;)
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            ssize_t size = recvfrom(sockfd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&peer,&len);

            if(size > 0 )
            {
              buffer[size] = 0;
              int _port = ntohs(peer.sin_port);
              std::string _ip = inet_ntoa(peer.sin_addr);
              std::cout << _ip<<":" <<_port <<"#"<<buffer<<std::endl;
              std::string echo_msg = "server get -> ";
              echo_msg += buffer;
              sendto(sockfd,echo_msg.c_str(),echo_msg.size(),0,(struct sockaddr*)&peer,len);
            }
            else 
            {
              std::cerr<<"recvfrom error" <<std::endl;
            }

        }


      }


      ~UdpServe(){
        if(sockfd>=0) close (sockfd);
      }

};

