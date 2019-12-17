#include "dbminutefactor.h"

minutefactor::minutefactor()
{
    initdata();
}
 void minutefactor::initdata()
{
   tablename="minutefactor";
   columnName<<"name" << "dataTime" << "data" << "dataTitle";//QStringList赋值
}
