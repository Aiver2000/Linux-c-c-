#include "sock.hpp"
#include <poll.h>

namespace ns_poll{
  class PollServer{
      private:
        int listen_sock;
        int port;
      public:
        PollServer(int _port):port(_port)
        {}

        void InitServer()
        {
          listen_sock = ns_sock::Sock::Socket();
          ns_sock::Sock::Bind(listen_sock,port);
          ns_sock::Sock::Listen(listen_sock,5);
        }

        void Run()
        {
            struct pollfd rfds[64];
            for(int i = 0;i<64;i++)
            {
              rfds[i].fd = -1;
              rfds[i].events = 0;
              rfds[i].revents = 0;
            }
            
            rfds[0].fd = listen_sock;
            rfds[0].events |= POLLIN;
            rfds[0].revents = 0;
            for(;;)
            {
              switch(poll(rfds,64,-1)){
                case 0:
                  std::cout<<"timeout " <<std::endl;
                  break;
                case -1:
                  std::cerr<<"poll error"<<std::endl;
                  break;
                default:
                  for(int i = 0;i<64;i++)
                  {
                    if(rfds[i].fd == -1)
                    {
                      continue;
                    }
                    if(rfds[i].revents & POLLIN)
                    {
                      if(rfds[i].fd == listen_sock){
                        //accept
                        std::cout <<"get a new link!"<<std::endl;
                      }
                      else 
                      {
                        //recv
                      }
                    }
                  }

                  
                  break;
                  

              }//end switch 
              
            }//end for
        }//end run



        ~PollServer()
        {}
  };

}
