#include "BlockQueue.hpp"
#include "Task.hpp"

void* Consumer(void* arg)
{
  auto bq = (BlockQueue<Task>*)arg;
  while(true)
  {
    sleep(1);
    int data = 0;
    Task t;
    bq->Pop(t);
    t.Run();
    
   // std::cout <<"Consumer: " << data <<std::endl;//消费数据
  }
}

void* Producter(void *arg)
{

  auto bq = (BlockQueue<Task>*)arg;
  const char* arr = "+-*/";
  while(true)
  {
    //sleep(1);
    int x = rand()%100 +1;
    int y = rand()%50;
    char op = arr[rand()%4];
    Task t(x,y,op);


    bq->Push(t);//生产数据
    std::cout <<"Producter task done: " <<std::endl;//消费数据
  }
}


int main()
{
  srand((unsigned long)time(nullptr));
  BlockQueue<Task> *bq = new BlockQueue<Task>();


  pthread_t c,p;
  pthread_create(&c,nullptr,Consumer,bq);
  pthread_create(&p,nullptr,Producter,bq);

  pthread_join(c,nullptr);
  pthread_join(p,nullptr);
  return 0;
}
