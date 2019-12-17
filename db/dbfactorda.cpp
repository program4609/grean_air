#include "dbfactorda.h"

dbfactorda::dbfactorda()
{
initdata();
}

void dbfactorda::initdata()
{
     tablename="factorda";
  columnName<<"name" << "revDataMin" << "revDataMax" << "factorMin"<<"factorMax";//QStringList赋值
}
