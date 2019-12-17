#include "dbfiveminutefactor.h"

dbfiveminutefactor::dbfiveminutefactor()
{
   initdata();
}
void dbfiveminutefactor::initdata()
{
     tablename="5minutefactor";
  columnName<<"name" << "dataTime" << "data" << "dataTitle";//QStringList赋值
}
