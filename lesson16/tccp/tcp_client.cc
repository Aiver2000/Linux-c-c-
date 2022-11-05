#include "tcp_client.hpp"

void Usage(std::string proc)
{
  std::cout <<"Usage:"<<proc<<" server_ip server_port"<<std::endl;
}


int main(int argc,char* argv[])
{
  if(argc != 3)
  {
      Usage(argv[0]);
      exit(1);
  }

  TcpClient tcli(argv[1],atoi(argv[2]));
  tcli.InitTcpClient();
  tcli.Start();


  return 0;
}
