#include "dbtempdata.h"

dbtempdata::dbtempdata()
{
     initdata();
}
void dbtempdata::initdata()
{
       tablename="dbtempdata";
       columnName<<"factorname" << "unit" << "Instrument"<< "status"<<"data";//QStringList赋值
}
