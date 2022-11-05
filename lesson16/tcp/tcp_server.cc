#include "tcp_server.hpp"


int main()
{

  TcpServer tsvr(8081);
  tsvr.InitTcpServer();

  tsvr.Loop();
}

