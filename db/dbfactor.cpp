#include "dbfactor.h"

dbfactor::dbfactor()
{
   initdata();
}

void dbfactor::initdata()
{
  tablename="factor";
 columnName<<"name" << "min" << "max" << "unit"<<"dataNum"<<"type"<<"modulus"<<"need_upload";//QStringList赋值
}
