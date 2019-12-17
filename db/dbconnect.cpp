#include "dbconnect.h"

dbconnect::dbconnect()
{

}
bool dbconnect::connectmysql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
       db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    // db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
       db.setPort(3306);                 //连接数据库端口号，与设置一致
        db.setDatabaseName("grean_air");      //连接数据库名，与设置一致
       db.setUserName("root");          //数据库用户名，与设置一致
       db.setPassword("188122133");    //数据库密码，与设置一致
      //  db.setPassword("123456");    //数据库密码，与设置一致
       if(!db.open())
       {
           return false;
       }
       else
       {
          return true;
      }
}
