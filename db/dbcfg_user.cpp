#include "dbcfg_user.h"

dbcfg_user::dbcfg_user()
{
initdata();
}

void dbcfg_user::initdata()
{
      tablename="cfg_user";
  columnName<<"user" << "type" << "password" << "description"<<"add_time"<<"update_time"<<"login_time";//QStringList赋值
}
