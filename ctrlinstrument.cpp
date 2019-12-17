#include "ctrlinstrument.h"
#include<QMessageBox>
#include<QWaitCondition>
#include <QTime>

ctrlInstrument::ctrlInstrument()// : QObject(parent)
{

}
/**
  类初始化
 * @brief ctrlInstrument::init
 */
void ctrlInstrument:: init(instrumentinfo instrument)
{
    db=QSqlDatabase::addDatabase("QMYSQL",instrument.name);
    db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("grean_air");      //连接数据库名，与设置一致
    db.setUserName("root");          //数据库用户名，与设置一致
    db.setPassword("188122133");    //数据库密码，与设置一致
    if(openDb())
       initdata(instrument);
    instrumentinfodata.testmode=0;
}
/**数据初始化
 * @brief ctrlInstrument::initdata
 */
void ctrlInstrument::initdata(instrumentinfo instrument)
{
    instrumentinfodata=instrument;
    setconnectionstatus(false);
    setsearchcmd();
    setCtrlcmd();
    setfactor();
     if(instrumentinfodata.autoReadType=="是")
         autoReadType=true;
     else
         autoReadType=false;

}
/**设置仪器运行模式
 * @brief ctrlInstrument::settestmode
 */
void ctrlInstrument::settestmode(int mode)
{
    instrumentinfodata.testmode=mode;
}
/**
 * @brief ctrlInstrument::getinstrumentinfo
 * @return
 */
instrumentinfo  ctrlInstrument::getinstrumentinfo()
{
    return instrumentinfodata;
}
/**
 * @brief ctrlInstrument::ComSend
 */



  /**
    线程打开数据库
  * @brief mythread::openDb
  * @return
  */
 bool  ctrlInstrument ::openDb()
 {

     if(!db.open())
     {
         return false;
     }
     else
     {
        return true;

    }

 }
  /**设置串口
   * @brief mythread::setcomport
   */
  bool ctrlInstrument::setcomport()
  {
          m_serial =new QSerialPort;
          QString  comname= QString("COM%1").arg(instrumentinfodata.comID);
           m_serial->setPortName(comname);
           m_serial->setBaudRate(instrumentinfodata.baudrate);
           m_serial->setDataBits(static_cast<QSerialPort::DataBits>(8));
           int parity=0;
           if(instrumentinfodata.parity=="无"||instrumentinfodata.parity=="无校验")
           {
               parity=0;
           }
           else if(instrumentinfodata.parity=="偶校验")
           {
                 parity=2;
           }
           else if(instrumentinfodata.parity=="奇校验")
           {
                 parity=3;
           }
           else if(instrumentinfodata.parity=="标记校验")
           {
                 parity=5;
           }

           m_serial->setParity(static_cast<QSerialPort::Parity>(parity));
           m_serial->setStopBits(static_cast<QSerialPort::StopBits>(instrumentinfodata.stopBit));
           m_serial->setFlowControl(QSerialPort::NoFlowControl);
           return m_serial->open(QIODevice::ReadWrite);
  }

  QByteArray ctrlInstrument::hexstrTobyte(QString str)
   {
      bool ok;
      QByteArray byte_arr;
       int len=str.length();
      for(int i=0;i<len;i+=2){
          if(i==len-1)
             byte_arr.append(char(str.mid(i,1).toUShort(&ok,16)));
          else
              byte_arr.append(char(str.mid(i,2).toUShort(&ok,16)));
      }
      return byte_arr;
  }

  /**数据发送
   * @brief mythread::ComSend
   */
  void ctrlInstrument ::ComSend()
  {
          QMapIterator<int,instrumentsearch> i(instrumentsearchmap);
          QMutex mutex;
          mutex.lock();
          QByteArray responseData;
          QString oldcmd;
          bool result=true;
          int time=1000;
          while (i.hasNext())
          {
                  i.next();
                 QByteArray requestData ;
                 if(oldcmd!=i.value().cmd)
                 {
                     oldcmd=i.value().cmd;
                     requestData= hexstrTobyte(i.value().cmd);

                  /*   m_serial->write(requestData);
                 if(instrumentinfodata.waittime>0&&instrumentinfodata.waittime<100000)
                      time=instrumentinfodata.waittime;
                 if (m_serial->waitForBytesWritten(time)) {
                     if (m_serial->waitForReadyRead(1000)) {
                          responseData = m_serial->readAll();
                         if(m_serial->waitForReadyRead())
                             responseData += m_serial->readAll();

                     //senddata(responseData,requestData);
                         if(responseData.size()>0)
                            GetFactorData(responseData,i.value().factorId);
                     } else {
                          break;
                     }
                 } else {
                     break;

                 }*/
                    result=senddata(requestData,responseData,time);
                     if(result==true&&responseData.size()>0)
                         GetFactorData(responseData,i.value().factorId);
                     else
                         break;
                 }
                 else
                 {
                      if(responseData.size()>0)
                         GetFactorData(responseData,i.value().factorId);
                 }
           }
               mutex.unlock();
  }
  /**
    直接接收串口数据
   * @brief ctrlInstrument::ComRev
   */
  void ctrlInstrument::ComRev()
  {
/*
         QMapIterator<int,instrumentsearch> i(instrumentsearchmap);
           QMutex mutex;
           int time=1000;
        //  while (i.hasNext())
        //  {
           //    i.next();
                mutex.lock();
                if(instrumentinfodata.communicationType=="串口")
                {
                  if (m_serial->waitForReadyRead(1000)) {
                       if(factorDatamap[i.value().factorId].factorinfodata.name=="门禁")
                       {
                            QByteArray responseData = m_serial->readAll();
                           int index= responseData.size();
                           int count=0;
                            while(responseData[index-1]!=0x0b&&count<7)
                            {
                               if(m_serial->waitForReadyRead(1000))
                               {
                                 responseData += m_serial->readAll();
                                 index= responseData.size();
                                 count=0;
                               }
                               else
                                  count++;
                            }
                            checkPassword(responseData);
                       }
                       else
                       {
                           QByteArray responseData = m_serial->readAll();
                           if(instrumentinfodata.waittime>0&&instrumentinfodata.waittime<100000)
                                time=instrumentinfodata.waittime;
                           while (m_serial->waitForReadyRead(time))
                               responseData += m_serial->readAll();
                           while (i.hasNext())
                            {
                                         i.next();
                                         if(responseData.size()>0)
                                            GetFactorData(responseData,i.value().factorId);
                                         else
                                             break;
                           }
                       }
                  }
                }
                else
                {
                    if(tcpClient->waitForReadyRead(time))
                    {
                        QByteArray responseData=  tcpClient->readAll();
                        while (i.hasNext())
                         {
                                      i.next();
                                      if(responseData.size()>0)
                                         GetFactorData(responseData,i.value().factorId);
                                      else
                                          break;
                        }
                    }
                }
                mutex.unlock();
       //   }
       */
      QMapIterator<int,instrumentsearch> i(instrumentsearchmap);
                QMutex mutex;
                int time=1000;
       if(instrumentinfodata.communicationType=="串口")
       {
               while (i.hasNext())
               {
                    i.next();
                     mutex.lock();
                       if (m_serial->waitForReadyRead(1000)) {
                            if(factorDatamap[i.value().factorId].factorinfodata.name=="门禁")
                            {
                                 QByteArray responseData = m_serial->readAll();
                                int index= responseData.size();
                                int count=0;
                                 while(responseData[index-1]!=0x0b&&count<7)
                                 {
                                    if(m_serial->waitForReadyRead(1000))
                                    {
                                      responseData += m_serial->readAll();
                                      index= responseData.size();
                                      count=0;
                                    }
                                    else
                                       count++;
                                 }
                                 checkPassword(responseData);
                            }
                            else
                            {
                                QByteArray responseData = m_serial->readAll();
                                if(instrumentinfodata.waittime>0&&instrumentinfodata.waittime<100000)
                                     time=instrumentinfodata.waittime;
                                while (m_serial->waitForReadyRead(time))
                                    responseData += m_serial->readAll();
                                   GetFactorData(responseData,i.value().factorId);
                            }



                       } else {
                            mutex.unlock();
                         break ;
                       }
                     mutex.unlock();
               }
       }
       else
       {
           if(tcpClient->waitForReadyRead(time))
           {
               QByteArray responseData=  tcpClient->readAll();
               while (i.hasNext())
                {
                             i.next();
                             if(responseData.size()>0)
                                GetFactorData(responseData,i.value().factorId);
                             else
                                 break;
               }
           }
       }

  }

  void  ctrlInstrument ::checkPassword(QByteArray responseData)
  {
      QString str;
      int size=responseData.size();
      for(int m=0;m<size;m++)
       {
                    if(responseData[m]!=0x0b)
                    {
                     responseData[m]=(responseData[m]+0x30)^0x7b;
                     str=str+responseData[m];
                    }
                    else
                    {
                        break;
                    }
       }
      /*
      QString ComType=helpclass.getiniData("setting.ini","instrumentctrl/password");
     if(ComType==str)
      {
                 helpclass.setiniData("setting.ini","instrumentctrl/type","open");
      }*/
      QString instrumentname,cmd;
     // helpclass.setiniData("setting.ini","instrumentctrl/type","close");
      instrumentname=helpclass.getiniData("setting.ini","instrumentctrl/instrumentName");
      cmd=helpclass.getiniData("setting.ini","instrumentctrl/instrumentcmd");
      instrumentcomSend(instrumentname,cmd);
  }

/**
 * @brief mythread::run
 */

void  ctrlInstrument ::run()
{
    QMutex mutex;
    bool save=true;
    QStringList valuelist,columnNamelist;
    columnNamelist<<"dataTime" << "type" << "systemLog";
    valuelist.append(helpclass.currenttimetostrinterface());
    valuelist.append("系统日志");
    bool open=false;
    QString  comname;
    if(instrumentinfodata.communicationType=="串口")
    {
       open=setcomport();
       if(open)
       {
           comname= QString("COM%1").arg(instrumentinfodata.comID);
           comname=comname+"打开成功";
       }
    }
    else
    {
         initclient()   ;
         netconnect=open=connectServer(instrumentinfodata.ip,instrumentinfodata.port);
         if(open)
         {
             comname=instrumentinfodata.ip+"连接成功";
         }
    }
     if(open)
     {

               valuelist.append(comname);
               insertdata(valuelist,columnNamelist,"log");
      while(true)
      {
          QTime current_time =QTime::currentTime();
         // SavetempData();
          sendinstrumentCmd();
          if(current_time.second()<50&&save==true)
              {
                   mutex.lock();
                     SaveData(1);//保存分钟数据
                  if(current_time.minute()==0)
                  {
                     SaveData(3);//保存小时数据
                  }
                  if(current_time.minute()%5==0)
                  {
                     SaveData(2);//保存5分钟数据
                  }
                  if(current_time.minute()==59&&current_time.hour()==23)
                  {
                     SaveData(4);//保存日数据
                  }
                  mutex.unlock();
                   save=false;
              }
          else if(current_time.second()>50)
          {
              save=true;
          }
          if(autoReadType==false)
          {

              ComSend();
              int out=0;
              while(out++<5)
              {
                   if(menjingtype==true)
                       break;
                 sleep(1);
              }
          }
          else
          {
              ComRev();
              msleep(200);
          }

          if(instrumentinfodata.communicationType=="网口"&&current_time.minute()%10==0&&current_time.second()<5&&netconnect==false)
             {
                            netconnect=connectServer(instrumentinfodata.ip,instrumentinfodata.port);
                            sleep(5);
             }
    }
      }
     else
     {
           QString  comname= QString("COM%1").arg(instrumentinfodata.comID);
           valuelist.append(comname+"打开失败");
           insertdata(valuelist,columnNamelist,"log");
     }
}

/**
  获取仪器查询命令
 * @brief ctrlInstrument::setsearchcmd
 */
void ctrlInstrument::setsearchcmd()
{
    QString sqlstr;
     QSqlQuery query(db),queryfactorAd(db);
  //  sqlstr="select * from instrumentsearch where instrumentId=";
     sqlstr="select cmd,addr,num,label,factorId,instrumentId from instrumentsearch a,combo_box b where a.formulaId=b.value and b.type='formula_type' and a.instrumentId=";
    sqlstr=sqlstr+QString("%1").arg(instrumentinfodata.id);
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    queryfactorAd.exec("select * from factorda");
    QMap<int , factorAd>factorAdList;
    while(queryfactorAd.next())
    {
       factorAd tempfactorad;
       tempfactorad.factorId=queryfactorAd.value("factorId").toInt();
       tempfactorad.revDataMin=queryfactorAd.value("revDataMin").toFloat();
       tempfactorad.revDataMax=queryfactorAd.value("revDataMax").toFloat();
       tempfactorad.factorMin=queryfactorAd.value("factorMin").toFloat();
       tempfactorad.factorMax=queryfactorAd.value("factorMax").toFloat();
       factorAdList.insert(tempfactorad.factorId,tempfactorad);
    }
    while(query.next()){
         instrumentsearch instrumentsearchtemp;
        QString data=query.value("cmd").toString();
        instrumentsearchtemp.cmd=data;
        data=query.value("addr").toString();
        instrumentsearchtemp.addr=data;
        int num=query.value("num").toInt();
        instrumentsearchtemp.num=num;
        data=query.value("label").toString();
        instrumentsearchtemp.formula=data;
        num=query.value("factorId").toInt();
        instrumentsearchtemp.factorId=num;
        num=query.value("instrumentId").toInt();
        instrumentsearchtemp.instrumentId=num;
        QMapIterator<int,factorAd> item(factorAdList);
        instrumentsearchtemp.factorAd=false;
        while(item.hasNext())
        {
            item.next();
            if(instrumentsearchtemp.factorId==item.value().factorId)
            {
                instrumentsearchtemp.factorAd=true;
                instrumentsearchtemp.revDataMin=item.value().revDataMin;
                instrumentsearchtemp.revDataMax=item.value().revDataMax;
                instrumentsearchtemp.factorMin=item.value().factorMin;
                instrumentsearchtemp.factorMax=item.value().factorMax;
                break;
            }
        }
        instrumentsearchmap.insert(instrumentsearchtemp.factorId,instrumentsearchtemp);
    }

}

/**
  获取仪器控制命令
 * @brief ctrlInstrument::setsearchcmd
 */
void ctrlInstrument::setCtrlcmd()
{
    QString sqlstr;
     QSqlQuery query(db);
     sqlstr="select cmdName,cmd from instrumentcmd where instrumentId= ";
    sqlstr=sqlstr+QString("%1").arg(instrumentinfodata.id);
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);

    while(query.next()){
         instrumentcmd instrumentcmdtemp;
        QString data=query.value("cmd").toString();
        instrumentcmdtemp.cmd=data;
        data=query.value("cmdName").toString();
        instrumentcmdtemp.name=data;
        instrumentcmdtypelist.insert(instrumentcmdtemp.name,instrumentcmdtemp);
    }
}
/**
 * @brief ctrlInstrument::sendinstrumentCmd
 * @param cmd
 * @return
 */
bool   ctrlInstrument::setinstrumentCmd(QString cmdname)
{

    m_cmdname=cmdname;
    menjingtype=true;
   // sendinstrumentCmd();

}
/**发送外部控制命令
 * @brief ctrlInstrument::sendinstrumentCmd
 * @return
 */
bool   ctrlInstrument::sendinstrumentCmd()
{
   //const QByteArray requestData;
    QString cmd;
     QMutex mutex;
       QString timestr;
    if(!m_cmdname.isEmpty())
    {
       cmd=instrumentcmdtypelist[m_cmdname].cmd;
       QStringList cmdlist=cmd.split(",");
       mutex.lock();
       for(int i=0;i<cmdlist.size();i++)
       {
           cmd=cmdlist.at(i);

         const QByteArray requestData= hexstrTobyte(cmd.toUtf8());
          if(instrumentinfodata.communicationType=="串口")
          {
           m_serial->write(requestData);

           if(m_serial->waitForBytesWritten(1000))
               ;
           else {
                  timestr=helpclass.currenttimetostridnomm();
                helpclass.setiniData("SendCMD.ini",timestr,"timeout");
           }
           if(m_serial->waitForReadyRead(1000))
               m_serial->readAll();
         }
          else
          {
              tcpClient->write(requestData);
              tcpClient->waitForBytesWritten(1000);//
              if(tcpClient->waitForReadyRead())
                   tcpClient->readAll();
          }
           timestr=helpclass.currenttimetostridnomm();
           helpclass.setiniData("SendCMD.ini",timestr,cmd);
           msleep(300);
       }
       mutex.unlock();
        m_cmdname="";

    }

    menjingtype=false;
    return true;
}

/** 设置仪器因子信息
 * @brief ctrlInstrument::setfactor
 */
void  ctrlInstrument::setfactor()
{
    QString sqlstr;
    QSqlQuery query(db);
    float floatdata=0;
  //  sqlstr="SELECT * FROM factor a LEFT OUTER JOIN instrumentsearch b ON a.id=b.factorId WhERE b.instrumentId=";
    sqlstr="SELECT * FROM factor a,instrumentsearch b ,combo_box c WHERE a.id=b.factorId and c.type='unit' and a.unit=c.`value` and b.instrumentId= ";
    sqlstr=sqlstr+QString("%1").arg(instrumentinfodata.id);
  //  query=dbinstrumentsearchclass->searchdata(sqlstr);
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    while(query.next())
    {
         int num=query.value("id").toInt();
          factorinfo factorinfodata;
          factorData factorDatatemp;
          factorinfodata.id=num;
          QString data=query.value("name").toString();
          factorinfodata.name=data;
          floatdata=query.value("min").toFloat();
          factorinfodata.mindata=floatdata;
          floatdata=query.value("max").toFloat();
          factorinfodata.maxdata=floatdata;//unit
          data=query.value("label").toString();
          factorinfodata.unit=data;
          num=query.value("dataNum").toInt();
          factorinfodata.dataNum=num;
          data=query.value("type").toString();
          factorinfodata.type=data;
          floatdata=query.value("modulus").toFloat();
          factorinfodata.modulus=floatdata;
          num=query.value("need_upload").toInt();
          factorinfodata.need_upload=num;

          factorinfodata.instrumentName=instrumentinfodata.name;
          factorDatatemp.init();
          factorDatatemp.setfactorinfo(factorinfodata);
          factorDatatemp.setDatabaseDb(db);
          factorDatamap.insert(factorinfodata.id,factorDatatemp);
    }
}

/**
 * @brief ctrlInstrument::GetFactorData
 * @param data
 * @return
 */
float ctrlInstrument::GetFactorData(QByteArray data,int factorid)
{

   floatdata floatdatatemp;
   int index=0,len=0,datacount=0;
   float factordata=0,tempdata=1;
   datacount=data.size();
   if(factorid<0)
       return 0;
   if(instrumentsearchmap[factorid].addr.toInt()-1>0)
   {
       index=instrumentsearchmap[factorid].addr.toInt()-1;
       if(index<0||index>=datacount)
           return 0;
   }
   len=instrumentsearchmap[factorid].num;
   if(instrumentsearchmap[factorid].formula=="四字节float大端模式")
   {
       if(index<datacount-3)
       {
       floatdatatemp.buf[3]=data[index];
       floatdatatemp.buf[2]=data[index+1];
       floatdatatemp.buf[1]=data[index+2];
       floatdatatemp.buf[0]=data[index+3];
       factordata=floatdatatemp.data;
       }
   }
   else if(instrumentsearchmap[factorid].formula=="四字节float小端模式")
   {
        if(index<datacount-3)
        {
          floatdatatemp.buf[0]=data[index];
          floatdatatemp.buf[1]=data[index+1];
          floatdatatemp.buf[2]=data[index+2];
          floatdatatemp.buf[3]=data[index+3];
          factordata=floatdatatemp.data;
        }
   }
   else if(instrumentsearchmap[factorid].formula=="四字节float小端模式倒连")
   {
      if(index<datacount-3)
      {
         floatdatatemp.buf[1]=data[index];
         floatdatatemp.buf[0]=data[index+1];
         floatdatatemp.buf[3]=data[index+2];
         floatdatatemp.buf[2]=data[index+3];
         factordata=floatdatatemp.data;
      }
   }
   else if(instrumentsearchmap[factorid].formula=="四字节float大端模式倒连")
   {
        if(index<datacount-3)
        {
          floatdatatemp.buf[2]=data[index];
          floatdatatemp.buf[3]=data[index+1];
          floatdatatemp.buf[0]=data[index+2];
          floatdatatemp.buf[1]=data[index+3];
          factordata=floatdatatemp.data;
        }
   }
   else if(instrumentsearchmap[factorid].formula=="int型不定字节补码")
   {
       for(int i=0;i<len&&i+index<datacount;i++)
       {
           factordata=helpclass.getDataN(256,len-i-1)*(data[index+i]&0xff)+factordata;

           tempdata=tempdata*256;
       }
       int m=(int)data[index]&0xff;
       if(0x80<=m)
       {
          //factordata=-(tempdata-factordata+1);
           factordata=-(tempdata-factordata);
       }
   }
   else if(instrumentsearchmap[factorid].formula=="int型不定字节顺排")
   {
       for(int i=0;i<len&&i+index<datacount;i++)
       {
           factordata=helpclass.getDataN(256,len-i-1)*(data[index+i]&0xff)+factordata;
       }
   }
   else if(instrumentsearchmap[factorid].formula=="212")
   {
       QString tempstr=data,temp;
       int pos=tempstr.indexOf(instrumentsearchmap[factorid].addr);
       if(pos>=0)
       {
          int end= tempstr.indexOf(",",pos+1);
           temp=tempstr.mid(pos+instrumentsearchmap[factorid].addr.length(),end-pos-instrumentsearchmap[factorid].addr.length());
           factordata=temp.toDouble();
       }
   }
   else if(instrumentsearchmap[factorid].formula=="BCD码")
   {
     int  Startindex=index;
     if(Startindex+len>datacount)
         return 0;
      for(int i=0;i<len;i++)
       {
           factordata=factordata+(data[Startindex]>>4)*helpclass.getDataN(10,(len-i)*2-1)+(data[Startindex++]&0x0f)*helpclass.getDataN(10,(len-i)*2-2);
       }
   }
   else if(instrumentsearchmap[factorid].formula=="多字节小数")
   {
      QString datastr;
      datastr.prepend(data);
      datastr=datastr.mid(index,len);
      factordata=datastr.toDouble();
   }
   else if(instrumentsearchmap[factorid].formula=="低半字节16进制数")
   {
       for(int i=0;i<len;i++)
        {
             factordata=factordata+(data[index+i]&0x0f)*helpclass.getDataN(16,(len-i-1));
        }
   }
   else if(instrumentsearchmap[factorid].formula=="高半字节16进制数")
   {
       for(int i=0;i<len;i++)
        {
             factordata=factordata+(data[index+i]&0xf0)*helpclass.getDataN(16,(len-i-1));
        }
   }
   else if(instrumentsearchmap[factorid].formula=="分隔符数量不定")//2018.1.31除去开头不满足条件的字符后再计算后面数字字符，记得分隔符一定要用十进制数
     {
             int k=0,j=0;
             char datam[15]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2d,0x2b,0x2e};
             for(k=0;k<datacount&&k<300;k++)
             {
                 for(j=0;j<15;j++)
                 {
                   if(data[k]==datam[j])
                       break;
                 }
                 if(j<15)
                     break;
             }
           QString  str=helpclass.GetDataFromBuf(data.data(),index+1,len,k);
            factordata=str.toDouble();
    }
   else if(instrumentsearchmap[factorid].formula=="科学计数法")//2019.11.8
   {
       int k=0,j=0;
       int sum=1;
       char datam[15]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x2d,0x2b,0x2e};
       for(k=0;k<datacount&&k<300;k++)
       {
           for(j=0;j<13;j++)
           {
             if(data[k]==datam[j])
                 break;
           }
           if(j<13)
               break;
       }
       QString  str=helpclass.GetDataFromBuf(data.data(),index+1,len,k);
       factordata=str.toDouble();
       for(;k<datacount&&k<300;k++)
       {
           if(data[k]==0x45)
               break;
       }
       if(data[k+1]==0x2b||data[k+1]==0x2d)//如果是+或-
       {
          for(j=k+2;j<datacount&&j<300;j++)
          {
              if(data[j]-0x30<=9&&data[j]>=0)
              {
                  ;
              }
              else
                  break;
          }
           QString datastr;
          datastr.prepend(data);
          datastr=datastr.mid(k+2,j-k-2);
          int num=datastr.toInt();
          sum=helpclass.getDataN(10,num);
          if(data[k+1]==0x2b)//如果是+
          {
             factordata=factordata*sum;
          }
          else
             factordata=factordata/sum;
       }

   }
   else if(instrumentsearchmap[factorid].formula=="位操作")
   {
      char c=data[index]  ;
      for(int i=1;i<len;i++)
      {
          c=c>>1;
      }
      if((int)c%2==1)
      {
          factordata=1;
      }
      else
      {
          factordata=0;
      }
   }
   else if(instrumentsearchmap[factorid].formula=="数字输入")//正常数据如：123456，主要用于密码输入
   {
      int size= data.size();
      for(int i=0;i<size;i++)
      {
         factordata=factordata+(data[i]-0)*helpclass.getDataN(10,(size-i-1));
      }
   }
    if(instrumentsearchmap[factorid].factorAd)//如果有数模转化
    {
         factordata=((factordata-instrumentsearchmap[factorid].revDataMin)*(instrumentsearchmap[factorid].factorMax-instrumentsearchmap[factorid].factorMin))/(instrumentsearchmap[factorid].revDataMax-instrumentsearchmap[factorid].revDataMin);
    }
    factordata=factordata*factorDatamap[factorid].factorinfodata.modulus;
   factorDatamap[factorid].adddata(factordata,instrumentinfodata.testmode);
   setconnectionstatus(true);
   return factordata;

}
/**
  保存数据
 * @brief ctrlInstrument::SaveData
 * @param type 1：保存分钟数据，2：保存5分钟数据 3：保存小时数据
 */

void ctrlInstrument::SaveData(int type)
{
    QMapIterator<int,factorData> i(factorDatamap);
    int id;
    QStringList minName,fiveminName,hourName;
     minName<<"name" << "dataTime" << "data" <<"coudata"<<"mindata"<<"maxdata"<<"dataTitle";//QStringList赋值
     fiveminName<<"name" << "dataTime" << "data" <<"coudata"<<"mindata"<<"maxdata"<<"dataTitle";
     hourName<<"name" << "dataTime" << "data" <<"coudata"<<"mindata"<<"maxdata"<<"dataTitle";

     QStringList valuelist,columnNamelist;
      columnNamelist<<"dataTime" << "type" << "systemLog";
      valuelist.append(helpclass.currenttimetostrinterface());
      valuelist.append("数据保存");
    while(i.hasNext())
    {
        QStringList datalist;
        i.next();
        id=i.value().factorinfodata.id;
        switch(type)
        {
           case 1:
               datalist=factorDatamap[id].savemindata();
               if(datalist.size()==minName.size())
                  if(!insertdata(datalist,minName,"minutefactor"))
                  {
                      db.close();
                     if(openDb())
                     {
                        valuelist.append("数据库重新打开");
                        insertdata(valuelist,columnNamelist,"log");
                     }
                  }

            break;
           case 2:
               datalist=factorDatamap[id].savefivemindata();
               if(datalist.size()==fiveminName.size())
                  insertdata(datalist,fiveminName,"5minutefactor");
               else
               {
                   valuelist.append(i.value().factorinfodata.name+"：5分钟数据未接收到数据");
                   insertdata(valuelist,columnNamelist,"log");
               }
            break;
           case 3:
               datalist=factorDatamap[id].savehourdata();
               if(datalist.size()==hourName.size())
                 insertdata(datalist,hourName,"hourfactor");
            break;
           case 4:
               datalist=factorDatamap[id].savedaydata();
               if(datalist.size()==hourName.size())
                 insertdata(datalist,hourName,"dayfactor");
            break;
        }
    }
}
/**保存临时数据
 * @brief ctrlInstrument::SavetempData
 */
void ctrlInstrument::SavetempData()
{
    QMapIterator<int,factorData> i(factorDatamap);
    int id;
    QStringList columndata;
    QString DbName="dbtempdata";
    columndata<< "unit" << "Instrument"<< "status"<<"data"<<"factorname";
    while(i.hasNext())
    {
        QStringList datalist;
        i.next();
        id=i.value().factorinfodata.id;
        datalist=factorDatamap[id].savetempdata(isconnectionstatus());
        QString sqlstr="select * from dbtempdata where factorname=";
        sqlstr=sqlstr+"'"+factorDatamap[id].factorinfodata.name+"'";
         QSqlQuery query(db);
         query.prepare(sqlstr);
         query.exec();
         if(query.next())
         {
             datalist.append(datalist.at(0));
             datalist.removeAt(0);
             updata(columndata,datalist,4,DbName);
         }
         else
         {
             columndata.clear();
             columndata<<"factorname"<< "unit" << "Instrument"<< "status"<<"data";
             insertdata(datalist,columndata,DbName);
         }
    }
}
/**设置串口状态
 * @brief ctrlInstrument::setconnectionstatus
 */
void ctrlInstrument:: setconnectionstatus(bool data)
{
    connectionstatus=data;
}

bool ctrlInstrument:: isconnectionstatus()
{
    return connectionstatus;
}
/**
* @brief dbbase::insertdata 插入数据到数据库
* @param valuedata 需要插入数据库的值
* @return
*/
bool ctrlInstrument::insertdata(QStringList valuedata,QStringList columnName,QString tablename)
{
     QSqlQuery query(db);
    QString sqlstr,columnstr,valuestr;

    sqlstr="INSERT INTO "+tablename;
    columnstr=" (";
    for(int i=0;i<columnName.size();i++)
    {
        if(i!=0)
           columnstr=columnstr+","+columnName.at(i);
        else
           columnstr=columnstr+columnName.at(i);
    }
    columnstr=columnstr+") ";

    valuestr="VALUES (";
    for(int j=0;j<valuedata.size();j++)
    {
        if(j!=0)
          valuestr=valuestr+","+"?";
        else
          valuestr=valuestr+"?";
    }
    valuestr=valuestr+")";
    sqlstr=sqlstr+columnstr+valuestr;
    query.prepare(sqlstr);
    for(int j=0;j<valuedata.size();j++)
    {
         query.bindValue(j, valuedata.at(j));
    }
   return query.exec();

}
/**
* @brief dbbase::updata更新列表数据
* @param columndata 被更新数据表的列名
* @param valuedata  更新数据的值
* @param  valuedatanum 被更新的数据个数，注意被更新数据个数后为条件判断
* @return
*/
bool ctrlInstrument::updata(QStringList columndata,QStringList valuedata,int valuedatanum,QString tablename)
{
  QSqlQuery query(db);
   QString sqlstr,columnstr;
   sqlstr="update "+tablename +" set ";
   if(columndata.size()!=valuedata.size())
       return false;
   for(int i=0;i<columndata.size();i++)
   {
       if(i<valuedatanum)
       {
           if(i!=valuedatanum-1)
               columnstr=columnstr+ columndata.at(i)+"=? ,";
           else
               columnstr=columnstr+ columndata.at(i)+"=? ";
       }
       else //加入条件判断
       {
           if(i==valuedatanum)
           {
                columnstr=columnstr+ "where "+columndata.at(i)+"=? ";
           }
           else
           {
                columnstr=columnstr+ "and "+columndata.at(i)+"=? ";
           }
       }
   }
   sqlstr=sqlstr+columnstr;
   query.prepare(sqlstr);
   for(int i=0;i<columndata.size();i++)
   {
        query.bindValue(i,valuedata.at(i));
   }
   return query.exec();
}
/**
 * @brief ctrlInstrument::getfactorDataMap
 * @return
 */
factorDatatype  ctrlInstrument:: getfactorDataMap()
{
     return  factorDatamap;
}
/**仪器中显示因子的数量
 * @brief ctrlInstrument::getshowfactornum
 * @return
 */
int ctrlInstrument::getshowfactornum()
{
    QMapIterator<int,factorData> item(factorDatamap);
    int i=0;
    while(item.hasNext())
    {
           item.next();
          if(item.value().factorinfodata.type=="显示")
           {
                i++;
           }
    }
   return i;
}

/**初始化SOCK
 * @brief Tcpclient::initclient
 */
void ctrlInstrument::initclient()
{
    tcpClient = new QTcpSocket();   //实例化tcpClient
  //  connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
           this, SLOT(ReadError(QAbstractSocket::SocketError)));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT (slotDisconnected ()));
    tcpClient->abort();
}
/**接收网络数据信号操函数
 * @brief Tcpclient::ReadData
 */
void ctrlInstrument::ReadData()
{
    QByteArray buffer = tcpClient->readAll();
    QString str;
    if(!buffer.isEmpty())
    {
       str=buffer;
     //  QMessageBox msgBox;
     //  msgBox.setText(str);
     //  msgBox.exec();
    }
}
/**接收到网络错误信号槽函数
 * @brief Tcpclient::ReadError
 */
void ctrlInstrument::ReadError(QAbstractSocket::SocketError)
{
    QString logstr;
    QStringList list;
    list.append("网络日志");
    logstr=tr("网络异常原因 %1").arg(tcpClient->errorString());
    list.append(logstr);
    //pDbControl->loginsertData(list);
    tcpClient->disconnectFromHost();
    tcpClient->waitForDisconnected();
    netconnect=false;


}
void  ctrlInstrument::slotDisconnected()
{
       QString logstr;
       QStringList list;
       list.append("网络日志");
       logstr=tr("服务器断开原因 %1").arg(tcpClient->errorString());
       list.append(logstr);
       //pDbControl->loginsertData(list);
       tcpClient->disconnectFromHost();
       tcpClient->waitForDisconnected();
      // netconnect=false;

}
/**数据发送函数
 * @brief ctrlInstrument::senddata
 * @param responseData
 * @param requestData
 */
bool  ctrlInstrument::senddata(QByteArray requestData,QByteArray &responseData,int time)
{
    if(instrumentinfodata.communicationType=="串口")
    {
        m_serial->write(requestData);
    if(instrumentinfodata.waittime>0&&instrumentinfodata.waittime<100000)
         time=instrumentinfodata.waittime;
    if (m_serial->waitForBytesWritten(time)) {
        if (m_serial->waitForReadyRead(1000)) {
             responseData = m_serial->readAll();
            if(m_serial->waitForReadyRead())
                responseData += m_serial->readAll();
        } else {
             return false;
        }
    } else {
       return false;

    }
    return true;
    }
    else//网络口
    {
        tcpClient->write(requestData);
        tcpClient->waitForBytesWritten(1000);//
        if(tcpClient->waitForReadyRead(time))
        {
            responseData =  tcpClient->readAll();
             return true;
        }
        else
        {
            return false;
        }
    }

}

/**连接服务器
 * @brief Tcpclient::connectServer
 * @param ip
 * @param port
 * @return
 */
bool ctrlInstrument::connectServer(QString ip,int port)
{
    QString logstr,portstr;
    QStringList valuelist,columnNamelist;

   tcpClient->connectToHost(ip, port);
   columnNamelist<<"dataTime" << "type" << "systemLog";
   if (tcpClient->waitForConnected(1000))  // 连接成功则进入if{}
   {

       valuelist.append(helpclass.currenttimetostrinterface());
       valuelist.append("网络日志");
       portstr=QString("%1").arg(port);
       logstr="网络连接成功"+ip+" "+portstr;
       valuelist.append(logstr);
     insertdata(valuelist,columnNamelist,"log");
       return true;
   }
   else
   {
       valuelist.append(helpclass.currenttimetostrinterface());
       valuelist.append("网络日志");
       portstr=QString("%1").arg(port);
       logstr="网络连接失败"+ip+" "+portstr;
       valuelist.append(logstr);
      insertdata(valuelist,columnNamelist,"log");
       return false;
   }
}
