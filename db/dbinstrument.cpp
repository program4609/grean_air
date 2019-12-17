#include "dbinstrument.h"

dbinstrument::dbinstrument()
{
  initdata();
}

void dbinstrument::initdata()
{
        tablename="instrument";
  columnName<<"name" << "type" << "baudrate" <<"parity"<<"port"<<"ip"<<"stopBit"<<"checked"<<"communicationType"<<"autoReadType"<<"comID"<<"waittime"<<"mode";//QStringList赋值
}
