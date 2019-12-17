#include "factordata.h"

factorData::factorData()// : QObject(parent)
{

}
/**
  * @brief factorData::initdata 因子数据初始化
  * @param id 因子id
  */
 void factorData::init()
 {
     initdata();
 }
 void  factorData:: setDatabaseDb(QSqlDatabase db)
 {
     m_db=db;
 }
 /**
  * @brief factorData::adddata  增加数据原则上每秒增加一个数据
  * @param data
  */
 void  factorData::adddata(float data,int modetype)
 {
   //  if((data<factorinfodata.maxdata&&data>factorinfodata.mindata))
   //  {
     minindex++;
     fiveminindex++;
     minsumdata=minsumdata+data;
     fivesumdata=fivesumdata+data;
     factorinfodata.mode=modetype;
     if(factorinfodata.type=="显示")
        factorinfodata.datastr=QString::number(data,'f',factorinfodata.dataNum);
     else
     {
         QString titlestr;
         QString datastr;
         titlestr=QString("factorid%1").arg(factorinfodata.id);
         datastr=QString("%1").arg(factorinfodata.data);
         titlestr=titlestr+"/"+datastr;
         factorinfodata.datastr=helpclass.getiniData("setting.ini",titlestr);
     }
     factorinfodata.data=data;
     if(hourmindata>data)
     {
         hourmindata=data;
         daymindata=data;
         minmindata=data;
         fiveminmindata=data;
     }
     if(hourmaxdata<data)
     {
         hourmaxdata=data;
         daymaxdata=data;
         minmaxdata=data;
         fiveminmaxdata=data;
     }
 //  }
 }
 /**
   返回因子信息
  * @brief factorData::getfactorinfo
  * @return
  */
 factorinfo  factorData:: getfactorinfo()
 {
     return factorinfodata;
 }
 /**
  * @brief factorData::initdata 数据初始化
  */
 void factorData::initdata()
 {
     oldminsumdata=0;
     minsumdata=0;
    initmindata();
    inithourdata();
    initfivemindata();
    initdaydata();
    dbfiveminutefactordata=new dbfiveminutefactor;
    minutefactordata=new minutefactor;
    dbhourfactordata=new dbhourfactor;
     dbtempdataclass=new  dbtempdata;
   //  dbfiveminutefactordata->setsqlDataDb(m_db);
   //  minutefactordata->setsqlDataDb(m_db);
    // dbhourfactordata->setsqlDataDb(m_db);
    // dbtempdataclass->setsqlDataDb(m_db);
    // query=new QSqlQuery ;
 }
 /**
  * @brief factorData::initmindata初始化分钟数据
  */
 void factorData::initmindata()
 {
     if(minindex>3)
       oldminsumdata=minsumdata;
       minindex=0;
       minsumdata=0;
       minmindata=9999999999;
       minmaxdata=0;
 }
 /**
  * @brief factorData::initfivemindata 初始化5分钟数据
  */
 void  factorData::initfivemindata()
 {
     fiveminindex=0;
     fivesumdata=0;
     fiveminmindata=9999999999;
     fiveminmaxdata=0;
 }
 /**
  *  @brief factorData::inithourdata初始化小时数据
  */
 void factorData::inithourdata()
 {
      hourindex=0;
      hoursumdata=0;
      hourmindata=9999999999;
      hourmaxdata=0;
 }
 /**
  * @brief factorData::inithourdata
  */
 void factorData::initdaydata()
 {
          dayindex=0;
          daysumdata=0;
          daymindata=9999999999;
          daymaxdata=0;
 }
 /**
   转化为需要保存进数据库中的数据
  * @brief factorData::getdbData
  * @param data 需要保存的数据
  * @return
  */
 QStringList factorData::getdbData(double data,double cou,double min,double max,QString title)
 {
     QStringList strlist;
  //  QString datastr;
  //  strlist.append(factorinfodata.name);
     QString datastr=QString::number(factorinfodata.id);
     strlist.append(datastr);
     strlist.append(helpclass.currenttimetostr());
     datastr=QString::number(data,'f',factorinfodata.dataNum);
     strlist.append(datastr);

     datastr=QString::number(cou,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(min,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(max,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     if(data>factorinfodata.maxdata||data<factorinfodata.mindata)
             title="D";
     strlist.append(title);
     return strlist;
 }

 /**
   转化为需要保存进数据库中的数据
  * @brief factorData::getdbData
  * @param data 需要保存的数据
  * @return
  */
 QStringList factorData::getfiveminutedbData(double data,double cou,double min,double max,QString title)
 {
     QStringList strlist;
  //  QString datastr;
  //  strlist.append(factorinfodata.name);
     QString datastr=QString::number(factorinfodata.id);
     strlist.append(datastr);
     strlist.append(helpclass.currenttimetostr());
     datastr=QString::number(data,'f',factorinfodata.dataNum);
     strlist.append(datastr);

     datastr=QString::number(cou,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(min,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(max,'f',factorinfodata.dataNum);
     strlist.append(datastr);

     if(data>factorinfodata.maxdata||data<factorinfodata.mindata)
             title="D";
     strlist.append(title);
     return strlist;
 }
 /**
   转化为需要保存进数据库的小时数据
  * @brief factorData::getdbData
  * @param data 需要保存的数据
  * @return
  */
 QStringList factorData::gethourdbData(double data,double cou,double min,double max,QString title)
 {
     QStringList strlist;
     QString datastr=QString::number(factorinfodata.id);
     //QString datastr=factorinfodata.name;
     strlist.append(datastr);
     strlist.append(helpclass.currenttimetostr());
     datastr=QString::number(data,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(cou,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(min,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     datastr=QString::number(max,'f',factorinfodata.dataNum);
     strlist.append(datastr);
     if(factorinfodata.mode==0)
     {
         if(data>factorinfodata.maxdata||data<factorinfodata.mindata)
              title="D";
     }
     else
     {
         switch(factorinfodata.mode)
         {
            case 0:
             title="N";
             break;
            case 1:
             title="CZ";
             break;
            case 2:
             title="CS";
             break;
         }
     }
     strlist.append(title);
     return strlist;
 }
 /**
  *  @brief factorData::savamindata 保存分钟数据
  */
 QStringList factorData::savemindata()
 {
    double data=0;
    QString title="N";
    QStringList resultdata;
    if(minindex>0)
    {
        data=minsumdata/minindex;
        resultdata=getdbData(data,minsumdata,minmindata,minmaxdata,title);
        initmindata();
         hoursumdata=hoursumdata+data;
         hourindex++;
    }
    return resultdata;
 }
 /**
  *  @brief factorData::savefivemindata 保存5分钟数据
  */
QStringList factorData::savefivemindata()
 {
     double data=0;
     QString title="N";
     QStringList resultdata;
     if(fiveminindex>0)
     {
         data=fivesumdata/fiveminindex;
         resultdata=getfiveminutedbData(data,fivesumdata,fiveminmindata,fiveminmaxdata,title);
     }
     initfivemindata();
     return resultdata;
 }
 /**
  *  @brief factorData::savehourdata保存小时数据
  */
QStringList factorData::savehourdata()
 {
     double data;
     QString title="N";
      QStringList resultdata;
   if(hourindex>0)
   {
       data=hoursumdata/hourindex;
       daysumdata=daysumdata+data;
       dayindex++;
     //  dbhourfactordata->insertdata(gethourdbData(data,hoursumdata,hourmindata,hourmaxdata ,title));
       resultdata=gethourdbData(data,hoursumdata,hourmindata,hourmaxdata ,title);
       factorinfodata.hourdata=data;
   }
   inithourdata();
       return resultdata;

 }

/**保存日数据
 *  @brief factorData::savehourdata
 */
QStringList factorData::savedaydata()
{
    double data;
    QString title="N";
     QStringList resultdata;
  if(dayindex>0)
  {
      data=daysumdata/dayindex;
    //  dbhourfactordata->insertdata(gethourdbData(data,hoursumdata,hourmindata,hourmaxdata ,title));
      resultdata=gethourdbData(data,daysumdata,daymindata,daymaxdata ,title);
  }
  initdaydata();
      return resultdata;

}
 /**
  * @brief factorData::setfactorinfo
  * @param factorinfotemp
  */
 void  factorData::setfactorinfo(factorinfo &factorinfotemp)
 {
     //memcpy(&factorinfodata,&factorinfotemp,sizeof(factorinfo));
     factorinfodata=factorinfotemp;
 }
 /**
 保存临时数据
  */
QStringList  factorData::savetempdata(bool connect)
 {
     //factorname" << "unit" << "Instrument"<< "status"<<"data"
//     bool result=false;
   //    QString sqlstr;
  //    int i=0;
       QStringList strlist;
     //  QStringList columndata;

            strlist.append(factorinfodata.name);
            strlist.append( factorinfodata.unit);
            strlist.append(factorinfodata.instrumentName);
            if(connect)
              strlist.append("在线");
            else
               strlist.append("离线");
            strlist.append(factorinfodata.datastr);
            return strlist;

 }
