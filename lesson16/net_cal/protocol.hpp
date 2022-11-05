#pragma once 


typedef struct request{
  int x;
  int y;
  char op;


}request_t;


typedef struct response{
  int code; //0 ->success ,1,2,3,4 -> 不同的错误信息
  int result;

}response_t;
