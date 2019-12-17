#include "instrumentmanage.h"
#include <QTime>

instrumentManage::instrumentManage()
{
    dbinstrumentclass=new dbinstrument;
   //  dbtempdataclass=new dbtempdata;

}

/*
void instrumentManage::ComSend()
{
  //ctrlInstrumentmap["温湿度计"].ComSend2();
   m_ctrlInstrument[0]->ComSend2();
}
*/

/**
 * @brief instrumentManage::init
 */
void instrumentManage::init()
{
    QString sqlstr;
    QSqlQuery query;
    instrumentIndex=0;
 //   qmanagethread=new managethread;
    sqlstr="select * from instrument where checked='是'";
    query.exec("SET NAMES UTF8");
    if(query.exec(sqlstr))
    {
        while(query.next()&&instrumentIndex<MAX_INSTRUMENT)
       {
           ctrlInstrument *ctrlInstrumenttemp;
             ctrlInstrumenttemp=new ctrlInstrument();
           // m_ctrlInstrument[i];
           instrumentinfo instrument;
           instrument.autoReadType= query.value("autoReadType").toString();
           instrument.baudrate=query.value("baudrate").toInt();
           instrument.comID=query.value("comID").toInt();
           instrument.communicationType=query.value("communicationType").toString();
           instrument.id=query.value("id").toInt();
           instrument.ip=query.value("ip").toString();
           instrument.name=query.value("name").toString();

           instrument.parity=query.value("parity").toString();
           instrument.port=query.value("port").toInt();
           instrument.stopBit=query.value("stopBit").toInt();
           instrument.type=query.value("type").toString();
           instrument.waittime=query.value("waittime").toInt();
              instrumentNameList.append(instrument.name);
           ctrlInstrumenttemp->init(instrument);
           ctrlInstrumenttemp->start();
           connect(ctrlInstrumenttemp ,SIGNAL(instrumentcomSend(QString,QString)) ,this ,SLOT(comRecv(QString,QString)));
           m_ctrlInstrument[instrumentIndex++]=ctrlInstrumenttemp;
       }
    }
}
/**设置仪器测试模式
 * @brief instrumentManage::settestmode
 * @param instrumentName
 * @param mode
 */
void instrumentManage::settestmode(QString instrumentName,int mode)
{
    for(int i=0;i<instrumentIndex;i++)
    {
        if(m_ctrlInstrument[i]->instrumentinfodata.name==instrumentName)
        {
           m_ctrlInstrument[i]->settestmode(mode);
        }
    }
}
/**得到所有因子信息
 * @brief instrumentManage::getFactorinfo
 * @return
 */
factorInfotype instrumentManage::getFactorinfo()
{
    factorInfotype factorInfoMap;
   // factorinfo tempfactorinfo;
   // factorDatatype tempfactorDataMap;
    for(int i=0;i<instrumentIndex;i++)
    {
        //tempfactorDataMap=m_ctrlInstrument[i]->getfactorDataMap();
       //  QMapIterator<int,factorData> item(tempfactorDataMap);
        QMapIterator<int,factorData> item(m_ctrlInstrument[i]->getfactorDataMap());
         while(item.hasNext())
        {
              item.next();
            //  tempfactorinfo=item.value().factorinfodata;
              factorInfoMap.insert(item.value().factorinfodata.id,item.value().factorinfodata);
        }
    }
    return factorInfoMap;
}

/**得到单个因子信息
 * @brief instrumentManage::getFactorinfo
 * @return
 */
factorinfo instrumentManage::getFactorinfo(QString factorName)
{
  factorinfo factorinfotemp;
  //memset(factorinfotemp,0,sizeof(factorinfotemp));
  factorinfotemp.data=0;
  factorinfotemp.instrumentName="";
  factorinfotemp.name="";
    for(int i=0;i<instrumentIndex;i++)
    {
        QMapIterator<int,factorData> item(m_ctrlInstrument[i]->getfactorDataMap());
         while(item.hasNext())
        {
              item.next();
           if(factorName==item.value().factorinfodata.name)
              return item.value().factorinfodata;
        }
    }
    return factorinfotemp;

}
/**得到本台仪器的所有信息
 * @brief instrumentManage::getfactordata
 * @return
 */
factorDatatype instrumentManage::getfactordata(QString Name)
{
    for(int i=0;i<instrumentIndex;i++)
    {
        if(m_ctrlInstrument[i]->getinstrumentinfo().name==Name)
        {
            return m_ctrlInstrument[i]->getfactorDataMap();
        }
    }
}
/**
 * @brief instrumentManage::getInstrumetNameinfo
 * @return
 */
QStringList  instrumentManage::getInstrumetNameinfo()
{
  return  instrumentNameList;
}
int instrumentManage::getinstrumentIndex()
{
    QString instrumentname, cmd;
 // sendcomdata (instrumentname, cmd);
    return instrumentIndex;
}

void instrumentManage::comRecv(QString instrumentname,QString cmd)
{
    comSend(instrumentname, cmd);
}
