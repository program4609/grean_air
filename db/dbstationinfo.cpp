#include "dbstationinfo.h"

dbstationinfo::dbstationinfo()
{
initdata();
}
void dbstationinfo::initdata()
{
       tablename="stationinfo";
  columnName<<"station_code" << "station_name" << "conservator";//QStringList赋值
}
