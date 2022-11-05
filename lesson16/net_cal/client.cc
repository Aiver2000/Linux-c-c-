#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <pthread.h>
#include "protocol.hpp"

using namespace std;


int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    cout<<"Usage:" <<argv[0] << "server_ip server_port"<<endl;
    exit(1);
  }

  int sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock <0)
  {
    exit(2);
  }

  struct sockaddr_in peer;
  memset(&peer,0,sizeof(peer));
  peer.sin_family = AF_INET;
  peer.sin_addr.s_addr = inet_addr(argv[1]);
  peer.sin_port = htons(atoi(argv[2]));

  if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
  {
    cerr<<"connect failed..."<<endl;
    exit(3);
  }

  while(true){
    request_t rq;
    cout<<"输入第一个数据# ";
    cin>>rq.x;
    cout<<"输入第二个数据# ";
    cin>>rq.y;
    cout<<"输入你的操作[+-*/%]# ";
    cin>>rq.op;


    send(sock,&rq,sizeof(rq),0);

    response_t rsp;
    recv(sock,&rsp,sizeof(rsp),0);

    cout<<"status: "<<rsp.code <<endl;
    cout<<rq.x<<rq.op<<rq.y<<"="<<rsp.result<<endl;

  }








  return 0;
}
