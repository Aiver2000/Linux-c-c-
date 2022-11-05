#include "tcp_server.hpp"

void Usage(std::string proc)
{
  std::cout<<"Usage"<<proc <<" port" <<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc != 2) 
  {
    Usage(argv[0]);
    exit(1);
  }

  TcpServer tsvr(atoi(argv[1]));

  tsvr.InitServer();
  tsvr.Loop();
   

  
  
  return 0;
}
