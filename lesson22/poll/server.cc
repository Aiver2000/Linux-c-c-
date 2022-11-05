#include "poll_server.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

static void Usage(std::string proc)
{
    std::cerr <<"Usage: " <<"\n\t" <<proc << "port" <<std::endl;
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
      Usage(argv[0]);
      exit(4);
    }

    unsigned short port = atoi(argv[1]);


    ns_poll::PollServer *ps = new ns_poll::PollServer(port);
    ps->InitServer();
    ps->Run();
    return 0;
}
