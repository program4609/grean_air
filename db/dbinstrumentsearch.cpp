#include "dbinstrumentsearch.h"

dbinstrumentsearch::dbinstrumentsearch()
{
   initdata();
}
void dbinstrumentsearch::initdata()
{
          tablename="instrumentsearch";
  columnName<< "cmd" << "addr" << "num"<<"factorId"<<"instrumentId"<<"formulaId";//QStringList赋值
}
