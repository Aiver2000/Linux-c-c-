#include <iostream>
#include <string>
#include <unordered_map>
#include <sys/epoll.h> 
#include "./include/mysql.h"

const std::string host = "43.143.138.8";
const std::string user = "lwz";
const std::string passwd = "wyjdc";
const std::string db = "100_test";
const int port = 3306;
int main()
{
    //std::cout <<"mysql client version :" <<mysql_get_client_info()<<std::endl <<std::endl;

    //创建了一个mysql句柄
    MYSQL *my = mysql_init(nullptr);

    //连接数据库
    if(nullptr == mysql_real_connect(my,host.c_str(),user.c_str(),passwd.c_str(),db.c_str(),port,nullptr,0))
    {
        std::cerr <<"mysql connect error " <<std::endl;
        return 1;
    } 
    //设置编码
    mysql_set_character_set(my,"utf8");

    std::cout <<"mysql 连接成功" <<std::endl;

    
    std::string sql = "insert into students values (3,\'王五\')";
    mysql_query(my,sql.c_str());
    //std::string sql = "update students set name=\'Jimmy\' where id = 3";
    //std::string sql = "delete from students where id = 3";

    std::string select_sql = "select * from students";


    if(0!=  mysql_query(my,select_sql.c_str()))
    {
        std::cout <<"execute : "<<select_sql<<"failed!"<<std::endl;
        return 2;
    }
    
    std::cout <<"execute : ["<<select_sql<<"] success "<<std::endl;

    //获取数据
    MYSQL_RES *res = mysql_store_result(my);
    
    //获取行列信息
    int rows = mysql_num_rows(res);
    int cols = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_field(res);
    for(int i = 0;i<cols;i++)
    {
        std::cout <<fields[i].name <<"\t";
    }
    std::cout <<std::endl;

    for(int i = 0;i<rows;i++)
    {
        MYSQL_ROW row = mysql_fetch_row(res);
        for(int j = 0;j<cols;j++)
        {
            std::cout <<row[j] <<"\t";
        }
        std::cout<<std::endl;
    }


    free(res);
    mysql_close(my);
    std::cout<<"关闭mysql" <<std::endl;



    return 0;
}