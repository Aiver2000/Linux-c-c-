#pragma once 

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

class UdpClient{
  private:
    int sockfd;
    std::string server_ip;
    int server_port;
  public:
    UdpClient(std::string _ip,int _port)
      :server_ip(_ip),server_port(_port)
    {
    }

    bool InitUdpClient()
    {
      sockfd = socket(AF_INET,SOCK_DGRAM,0);
      if(sockfd < 0)
      {
        std::cerr<<"socket error!"<<std::endl;
        return false;
      }

      //客户端需要port，不需要bind
      return true;
    }

    void Start()
    {
      struct sockaddr_in peer;
      memset(&peer,0,sizeof(peer));

      peer.sin_family = AF_INET;
      peer.sin_port = htons(server_port);
      peer.sin_addr.s_addr = inet_addr(server_ip.c_str());
      std::string msg;
      for(;;)
      {
        std::cout <<"Please Enter#";
        std::cin>>msg;
        sendto(sockfd,msg.c_str(),msg.size(),0,(struct sockaddr*)&peer,sizeof(peer));

        char buffer[128];
        struct sockaddr_in  temp;
        socklen_t len = sizeof(temp);
        ssize_t size = recvfrom(sockfd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&temp,&len);
        if(size >0)
        {
          buffer[size] = 0;
          std::cout <<buffer<<std::endl;
        }
      }
    }
    ~UdpClient()
    {
      if(sockfd >= 0) close(sockfd);
    }
    
    
};
