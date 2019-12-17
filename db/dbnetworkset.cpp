#include "dbnetworkset.h"

dbnetworkset::dbnetworkset()
{
initdata();
}

void dbnetworkset::initdata()
{
          tablename="networkset";
  columnName<<"protocol" << "ip" << "port"<<"mn"<<"password"<<"st"<<"name"<<"used"<<"hourdatetime"<<"minutedatetime"<<"sendFlag"<<"requestFlag"<<"crc";//QStringList赋值
}
