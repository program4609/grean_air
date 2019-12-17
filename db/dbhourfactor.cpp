#include "dbhourfactor.h"

dbhourfactor::dbhourfactor()
{
   initdata();
}

void dbhourfactor::initdata()
{
    tablename="hourfactor";
    columnName<<"name" << "dataTime" << "data" <<"coudata"<<"mindata"<<"maxdata"<<"dataTitle";//QStringList赋值
}
