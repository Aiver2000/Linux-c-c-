#pragma once 
#include <iostream>
class Task{

  public:
    Task(int _x,int _y,char _op):x(_x),y(_y),op(_op)
  {
    
  }
    Task()
    {}
    void Run()
    {
      int result = 0;
      switch(op)
      {
          case '+':
            result = x+y;
            break;
          case '-':
            result = x-y;
            break;
          case '*':
            result = x*y;
            break;
          case '/':
            if(y==0)
            {
              std::cout <<"Warning :div zero"<<std::endl;
              result = -1;
            }
            else 
            {
              result = x/y;
            }
            break;
          default:
            break;
        
      }
      std::cout<<x<<op<<y<<"="<<result<<std::endl;
    }
    ~Task()
    {}
    



  private:
    int x;
    int y;
    char op;


};
