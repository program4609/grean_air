#include "dbcontrol.h"

DbControl::DbControl()
{
   pdbfactor=new dbfactor;
   pdbinstrument=new  dbinstrument;
   pdbinstrumentcmd=new dbinstrumentcmd;
   pdbinstrumentsearch=new dbinstrumentsearch;
   pdbnetpolid=new  dbnetpolid;
   pdbnetworkset=new    dbnetworkset;
   pdbcfg_user=new dbcfg_user;
   pdblog=new dblog;
   qmaintain=new maintain;
}
/**因子插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::factorinsertData(QStringList valuedata)
{
    pdbfactor->insertdata(valuedata);
    return true;
}
/**因子修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::factorupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
    pdbfactor->updata(columndata,valuedata,valuedatanum);
    return true;
}
/**因子删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::factordelete(QStringList columndata,QStringList valuedata)
{
          pdbfactor->deletedata(columndata,valuedata);
          return true;
}

/**仪器插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::instrumentinsertData(QStringList valuedata)
{
    pdbinstrument->insertdata(valuedata);
    return true;
}
/**仪器修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::instrumentupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbinstrument->updata(columndata,valuedata,valuedatanum);
   return true;
}
/**仪器删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::instrumentdelete(QStringList columndata,QStringList valuedata)
{
   pdbinstrument->deletedata(columndata,valuedata);
   return true;
}

/**控制命令插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::CtrlCmdinsertData(QStringList valuedata)
{
   pdbinstrumentcmd->insertdata(valuedata);
   return true;
}
/**控制命令修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::CtrlCmdupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbinstrumentcmd->updata(columndata,valuedata,valuedatanum);
   return true;
}
/**控制命令删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::CtrlCmddelete(QStringList columndata,QStringList valuedata)
{
   pdbinstrumentcmd->deletedata(columndata,valuedata);
   return true;
}
/**查询命令插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::searchCmdinsertData(QStringList valuedata)
{
   pdbinstrumentsearch->insertdata(valuedata);
   return true;
}
/**查询命令修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::searchCmdupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbinstrumentsearch->updata(columndata,valuedata,valuedatanum);
   return true;
}
/**查询命令删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::searchCmddelete(QStringList columndata,QStringList valuedata)
{
   pdbinstrumentsearch->deletedata(columndata,valuedata);
   return true;
}

/**网络因子插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::netpolidinsertData(QStringList valuedata)
{
   pdbnetpolid->insertdata(valuedata);
   return true;
}
/**网络因子修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::netpolidupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbnetpolid->updata(columndata,valuedata,valuedatanum);
   return true;
}
/**网络因子删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::netpoliddelete(QStringList columndata,QStringList valuedata)
{
   pdbnetpolid->deletedata(columndata,valuedata);
   return true;
}
/**网络协议插入
 * @brief DbControl::insertData
 * @param valuedata
 * @return
 */
bool DbControl::networksetinsertData(QStringList valuedata)
{
   pdbnetworkset->insertdata(valuedata);
   return true;
}
/**网络协议修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::networksetupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbnetworkset->updata(columndata,valuedata,valuedatanum);
   return true;
}
/**网络协议删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::networksetdelete(QStringList columndata,QStringList valuedata)
{
   pdbnetworkset->deletedata(columndata,valuedata);
   return true;
}
/** 用户数据插入
 * @brief DbControl::userinsertData
 * @param valuedata
 * @return
 */
bool DbControl::userinsertData(QStringList valuedata)
{
     pdbcfg_user->insertdata(valuedata);
     return true;
}
/**用户修改
 * @brief DbControl::factorupdateData
 * @param columndata
 * @param valuedata
 * @param valuedatanum
 * @return
 */
bool DbControl::userupdateData(QStringList columndata,QStringList valuedata,int valuedatanum)
{
   pdbcfg_user->updata(columndata,valuedata,valuedatanum);
   return true;
}

/**用户删除
 * @brief DbControl::factordelete
 * @param columndata
 * @param valuedata
 * @return
 */
bool DbControl::userdelete(QStringList columndata,QStringList valuedata)
{
   pdbcfg_user->deletedata(columndata,valuedata);
   return true;
}

/** 日志数据插入
 * @brief DbControl::loginsertData
 * @param valuedata
 * @return
 */
bool DbControl::loginsertData(QStringList valuedata)
{
    QString timestr;
    timestr=helpclass.currenttimetostrinterface();
    valuedata.insert(0,timestr);
     pdblog->insertdata(valuedata);
     return true;
}
/**维护日志插入
  * @brief DbControl::maintaininsertData
  * @param valuedata
  * @return
  */
 bool  DbControl::maintaininsertData(QStringList valuedata)
 {
     QString timestr;
       timestr=helpclass.currenttimetostrinterface();
       valuedata.insert(0,timestr);
       qmaintain->insertdata(valuedata);
        return true;
 }
