#include "epoller.hpp"
#include "app_interface.hpp"
#include <string>
#include <cstdlib>
#include "sock.hpp"
#include "util.hpp"

const int back_log = 5;
static void Usage(std::string proc)
{
  std::cout<<"Usage:" <<"\n\t" <<proc <<"port" <<std::endl;
}

int main(int argc,char* argv[])
{
  if(argc != 2)
  {
    Usage(argv[0]);
    exit(5);
  }

  uint16_t port = atoi(argv[1]);
  int listen_sock  = ns_sock::Sock::Socket();
  ns_util::SetNonBlock(listen_sock);
  ns_sock::Sock::Bind(listen_sock,port);
  ns_sock::Sock::Listen(listen_sock,back_log);

  ns_epoll::Epoller epoller;
  epoller.InitEpoller();

  ns_epoll::EventItem item;
  item.sock = listen_sock;
  item.R = &epoller;

  item.ManagerCallBack(ns_appinterface::accepter,nullptr,nullptr);

  epoller.AddEvent(listen_sock,EPOLLIN|EPOLLET,item);
  
  while(true)
  {
    int timeout =1000;
    epoller.Dispatch(timeout);
  }

  return 0;

}
