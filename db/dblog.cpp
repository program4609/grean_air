#include "dblog.h"

dblog::dblog()
{
initdata();
}

void dblog::initdata()
{
      tablename="log";
  columnName<<"dataTime" << "type" << "systemLog";//QStringList赋值
}
