#pragma once 
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

namespace ns_util{
    void SetNonBlock(int sock)
    {
      int fl = fcntl(sock,F_GETFL);
      fcntl(sock,F_SETFL,fl|O_NONBLOCK);
    }

    class StringUtil{

      public:
        static void Split(std::string & in ,std::vector <std::string> *out,std::string sep)
        {
            while(true)
            {
              size_t pos = in.find(sep);
              if(pos == std::string::npos)
              {
                break;
              }
              out->push_back(in.substr(0,pos));
              in.erase(0,pos+sep.size());

            }
        }


        static void Deserialize(std::string &in ,int *x,int *y)
        {

          size_t pos = in.find("+");
          std::string left = in.substr(0,pos);
          std::string right = in.substr(pos+1);

          *x = atoi(left.c_str());
          *y = atoi (right.c_str());
        }

    };
  

}
