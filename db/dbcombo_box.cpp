#include "dbcombo_box.h"

dbcombo_box::dbcombo_box()
{
initdata();
}

void dbcombo_box::initdata()
{
     tablename="combo_box";
  columnName<<"label" << "value" << "data" << "type";//QStringList赋值
}
