#include "dbalarm.h"

dbalarm::dbalarm()
{
initdata();
}

void dbalarm::initdata()
{
    tablename="alarm";
  columnName<<"data_Date" << "description" << "data" << "unit"<<"min"<<"max"<<"type";//QStringList赋值
}
