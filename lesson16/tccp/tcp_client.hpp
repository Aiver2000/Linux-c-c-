#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>



class TcpClient{
  private:
    std::string svr_ip;
    int svr_port;
    int sock;
  public:
    TcpClient(std::string _ip,int _port):svr_ip(_ip),svr_port(_port),sock(-1)
    {}

    void InitTcpClient()
    {
      sock = socket(AF_INET,SOCK_STREAM,0);
      if(sock <0 )
      {
        std::cerr<<"socket error!" <<std::endl;
        exit(2);

      }

    }

    void Start()
    {

      struct sockaddr_in peer;
      memset(&peer,0,sizeof(peer));
      peer.sin_family = AF_INET;
      peer.sin_port = htons(svr_port);
      peer.sin_addr.s_addr = inet_addr(svr_ip.c_str()); 
      if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) == 0)
      {
          std::cout <<"connect success ..."<<std::endl;
          Request(sock); 
         
      }
      else 
      {
          std::cout <<"connect failed ..."<<std::endl;
      }
    }


    void Request(int sock)
    {
      std::string message;
      char buffer[1024];
      while(true)
      {
        std::cout<<"Please Enet # ";
        std::cin >> message;

        write(sock,message.c_str(),message.size());

        ssize_t s = read(sock,buffer,sizeof(buffer)-1);
        if(s>0) buffer[s] = 0;

        std::cout<<"server echo# " <<buffer<<std::endl;



      }
    }
    ~TcpClient()
    {
      if(sock >= 0 )  close (sock);

    }


};

