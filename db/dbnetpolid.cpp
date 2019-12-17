#include "dbnetpolid.h"

dbnetpolid::dbnetpolid()
{
initdata();
}
void dbnetpolid::initdata()
{
        tablename="netpolid";
  columnName<<"protocalId" << "factorId" << "polId";//QStringList赋值
}
