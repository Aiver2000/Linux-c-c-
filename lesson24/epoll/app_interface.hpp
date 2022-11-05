#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include "epoller.hpp"
#include "util.hpp"

namespace ns_appinterface{

  using namespace ns_epoll;

  int recver(EventItem* item);
  int sender(EventItem* item);
  int errorer(EventItem* item);

  int accepter(EventItem *item)
  {

     
     std::cout <<"get a new link: " <<item ->sock <<std::endl;
     while(true)
     {
       struct sockaddr_in peer;
       socklen_t len = sizeof(peer);
       int sock = accept(item->sock,(struct sockaddr*)&peer,&len);
       if(sock <0){
         if(errno == EAGAIN|| errno ==EWOULDBLOCK){
           return 0;
         }
         if(errno == EINTR){
           continue;
         }
         else{
           return -1;
         }
       }
       else{
         ns_util::SetNonBlock(sock);
         EventItem tmp;
         tmp.sock = sock;
         tmp.R = item->R;
         tmp.ManagerCallBack(recver,sender,errorer);
         Epoller* epoller = item->R;
         epoller->AddEvent(sock,EPOLLIN|EPOLLET,tmp);

       } 


     }
     return 0;
  }

//0:读取成功 
//-1：读取失败
  int recver_helper(int sock,std::string * out)
  {
    while(true)
    {
      char buffer[128];

      ssize_t size = recv(sock,buffer,sizeof(buffer)-1,0);
      if(size < 0 )
      {
        if(errno == EAGAIN ||errno == EWOULDBLOCK)
        {
          //循环读取完毕
          return 0; 
        }
        else if(errno == EINTR )
        {
          //被信号中断，继续尝试
          continue;
        }
        else 
        {
          return -1;
        }
      }
      else 
      {
        buffer[size] = 0;
        *out += buffer;

      }
    }

  }


  int recver(EventItem *item)
  {

     std::cout <<"recv event ready:"<<item->sock <<std::endl;
     //1,非阻塞读
     if(recver_helper(item->sock,&(item->inbuffer))< 0 )
     {
        //item->error_handler
        return -1;
     }
     std::cout<<"client#" <<item->inbuffer <<std::endl;
     //2.防止粘包,涉及协议定制！！
     std::vector<std::string> messages;
     ns_util::StringUtil::Split(item->inbuffer,&messages,"X");
    // for(auto s : messages)
    // {
    //   std::cout <<s<<std::endl;
    // }
      
     //3.报文协议反序列化 decode
     struct data{
          int x;
          int y;
     };

     for(auto s:messages)
     {

      struct data d;
      ns_util::StringUtil::Deserialize(s,&d.x,&d.y);
      //task t(d);
      //thread_pool->oush(t);
      //4.业务处理
      int z = d.x+d.y;
      //5.形成响应报文，序列化为一个字符串encode
      std::string response;
      response += std::to_string(d.x);
      response += "+";
      response += std::to_string(d.y);
      response += "=";
      response += std::to_string(z);

      item->outbuffer += response;
      //5.1 设置分隔符
      item->outbuffer+="X";
     }
     //6.写回
     if(!item->outbuffer.empty()) item->R->EnableReadWrite(item->sock,true,true);
     return 0;
  }

  int sender_helper(int sock,std::string& in)
  {
    while(true){
      size_t total = 0;
      ssize_t s = send(sock,in.c_str()+total,in.size()-total,0);
      if(s>0)
      {
        total += s;
        if(total >= in.size())
        {
          return 0;
        }
      }
      else if(s <0)
      {
        if(errno == EAGAIN || errno == EWOULDBLOCK)
        {
          in.erase(total);
          return 1; //已经将缓冲区打满
        }
        else if(errno == EINTR)
        {
          continue;
        }
        else 
        {
          //TODO
          return -1;
        }
      }
    }
  }
  int sender(EventItem *item)
  {
      int ret = sender_helper(item->sock,item->outbuffer);
      if(ret == 0)
      {
          item->R->EnableReadWrite(item->sock,true,false);
      }
      else if(ret == 1)
      {
          
          item->R->EnableReadWrite(item->sock,true,true);
      }
      else 
      {
        // 
      }
      return 0;
  }

  int errorer(EventItem * item)
  {

    return 0;
  }

}
