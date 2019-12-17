#include "dbinstrumentcmd.h"

dbinstrumentcmd::dbinstrumentcmd()
{
initdata();
}


void dbinstrumentcmd::initdata()
{
      tablename="instrumentcmd";
  columnName<<"instrumentId" << "cmdName" << "cmd";//QStringList赋值
}
