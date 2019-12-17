#include "tcpclient.h"
#include <QMessageBox>
#include<QTime>
#include<QSqlQuery>

Tcpclient::Tcpclient()
{

}
bool Tcpclient::initDb()
{
    db=QSqlDatabase::addDatabase("QMYSQL",m_ip);
    db.setHostName("127.0.0.1");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("grean_air");      //连接数据库名，与设置一致
    db.setUserName("root");          //数据库用户名，与设置一致
    db.setPassword("188122133");    //数据库密码，与设置一致
    netconnect=false;
    pDbControl=new  DbControl();
     return openDb();

}
/**
  线程打开数据库
* @brief mythread::openDb
* @return
*/
bool  Tcpclient ::openDb()
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
/**接收网络数据信号操函数
 * @brief Tcpclient::ReadData
 */
void Tcpclient::ReadData()
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
void Tcpclient::ReadError(QAbstractSocket::SocketError)
{
    QString logstr;
    QStringList list;
    list.append("网络日志");
    logstr=tr("网络异常原因 %1").arg(tcpClient->errorString());
    list.append(logstr);
    pDbControl->loginsertData(list);
    tcpClient->disconnectFromHost();
    tcpClient->waitForDisconnected();
    netconnect=false;


}
void  Tcpclient::slotDisconnected()
{
       QString logstr;
       QStringList list;
       list.append("网络日志");
       logstr=tr("服务器断开原因 %1").arg(tcpClient->errorString());
       list.append(logstr);
       pDbControl->loginsertData(list);
       tcpClient->disconnectFromHost();
       tcpClient->waitForDisconnected();
       netconnect=false;

}
/**初始化数据连接
 * @brief Tcpclient::initdata
 * @param ip
 * @param port
 */
void Tcpclient::initdata(networkinfo networkinfos)
{
    m_ip=networkinfos.ip;
    m_port=networkinfos.port;
    m_networkinfo=networkinfos;
    crctype=networkinfos.crctype;
    initDb();
    getnet212set();
    start();
}
/**初始化SOCK
 * @brief Tcpclient::initclient
 */
void Tcpclient::initclient()
{
    tcpClient = new QTcpSocket();   //实例化tcpClient
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), \
           this, SLOT(ReadError(QAbstractSocket::SocketError)));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT (slotDisconnected ()));
    tcpClient->abort();
}

/**连接服务器
 * @brief Tcpclient::connectServer
 * @param ip
 * @param port
 * @return
 */
bool  Tcpclient::connectServer(QString ip,int port)
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
/**发送数据
 * @brief Tcpclient::writedata
 * @param data
 */
void Tcpclient::writedata(QString data)
{
  tcpClient->write(data.toLatin1());
  tcpClient->waitForBytesWritten(1000);//
}
/**线程执行
 * @brief Tcpclient::run
 */
void  Tcpclient ::run()
{
      initclient();
      netconnect=connectServer(m_ip,m_port);
      while(true)
      {
             QTime current_time =QTime::currentTime();
             if(netconnect==true)
             {
                 if(current_time.second()%4==0)
                 {
                     QString strQN,endtime,starttime;
                     strQN=helpclass.currenttimetostrid();
                     endtime=helpclass.currenttimetostrinterface();
                     if(current_time.second()>52)
                     {
                        starttime=readSendTime();
                        strQN="QN="+strQN;
                        get2061Pkg(strQN,  starttime, endtime);
                        sleep(19);
                     }
                     sleep(1);
                 }
                 else if(current_time.second()%30==0)
                 {
                     QString strQN,endtime,starttime;
                     strQN=helpclass.currenttimetostrid();
                     endtime=helpclass.currenttimetostrinterface();
                     starttime=read2051SendTime();
                     strQN="QN="+strQN;
                     get2051Pkg(strQN,  starttime, endtime);
                     sleep(3);
                     get2011Pkg(strQN);
                 }
                 else
                 {
                     sleep(1);
                 }
                 if(current_time.second()<40&&current_time.second()>35)
                 {
                    sendheadpackage();
                    sleep(6);
                 }
             }
             else if(current_time.minute()%10==0&&current_time.second()<5)
             {
                  netconnect=connectServer(m_ip,m_port);
                  sleep(5);
             }
             else
             {
                 sleep(2);
             }
    }
}
/**
 * @brief Tcpclient::readDbData
 */
QString Tcpclient::readSendTime()
{
   QSqlQuery query(db);
   QString resultstr="";
   QString sqlstr="select hourdatetime from networkset where id=";
   sqlstr=sqlstr+QString("%1").arg(m_networkinfo.id);
  // query.exec("SET NAMES UTF8");
   if(query.exec(sqlstr))
   {
       while(query.next())
       {
           resultstr= query.value(0).toString();
           break;
       }
   }
    int pos= resultstr.indexOf("T");
    if(pos>=0)
    {
        resultstr=resultstr.left(pos)+" "+resultstr.right(resultstr.length()-pos-1);
    }
   return resultstr;
}
/**
 * @brief Tcpclient::readDbData
 */
QString Tcpclient::read2051SendTime()
{
   QSqlQuery query(db);
   QString resultstr="";
   QString sqlstr="select minutedatetime from networkset where id=";
   sqlstr=sqlstr+QString("%1").arg(m_networkinfo.id);
  // query.exec("SET NAMES UTF8");
   if(query.exec(sqlstr))
   {
       while(query.next())
       {
           resultstr= query.value(0).toString();
           break;
       }
   }
    int pos= resultstr.indexOf("T");
    if(pos>=0)
    {
        resultstr=resultstr.left(pos)+" "+resultstr.right(resultstr.length()-pos-1);
    }
   return resultstr;
}
/**得到协议头数据
 * @brief Tcpclient::getheaddata
 * @param cn
 * @param flag
 * @return
 */
QString Tcpclient::getheaddata(QString cn,int flag)
{
    QString resultstr;
    if(flag!=-1)//如果设置为-1表示无flag
       resultstr=";ST="+m_networkinfo.st+";CN="+ cn+";PW="+m_networkinfo.password+";MN="+m_networkinfo.mn+";Flag="
            +QString("%1").arg(flag)+";CP=&&";
    else
        resultstr=";ST="+m_networkinfo.st+";CN="+ cn+";PW="+m_networkinfo.password+";MN="+m_networkinfo.mn+";CP=&&";
    return resultstr;
}
/**获取2061
 * @brief Tcpclient::get2061Pkg
 * @param strQN
 * @param recDataTime
 * @param buf
 */
void Tcpclient::get2061Pkg(QString strQN, QString starttime,QString endtime)
{
    QString headstr= getheaddata("2061",m_networkinfo.sendFlag);
    QString sendstr="",factorPloId,tempstr,datastr,dataname,olddatatime;
    float data;
  DbdataMap DbdataList;

    DbdataList=getDbData(starttime, endtime);
    bool first=false;
    QMapIterator<int,Dbdata> i(DbdataList);
    while (i.hasNext())
    {
        QMapIterator<int,net212set>net (net212setlist);
         i.next();
         if(olddatatime!=i.value().time)
         {
             if(first==true)
             {
                 sendstr=sendstr+tempstr;
                 sendData(sendstr,olddatatime);
                  tempstr="";
                  sendstr="";
                  sleep(1);
             }
             olddatatime=i.value().time;
             sendstr=strQN+headstr+"DataTime="+helpclass.getTimeToNumb(olddatatime)+";";
             first=true;
         }
         factorPloId=i.value().polId;
        while(net.hasNext())
        {
            net.next();
           QString  PloIdstr= factorPloId+"-"+net.value().contain+"=";
           dataname=net.value().dataname;
           if(net.value().cn=="2061")
           {
               if(net.value().dataname=="data")
               {
                   data=i.value().Avg;
                   datastr=QString::number(data,'f',6);
                   tempstr= tempstr+ PloIdstr+datastr+",";
               }
               else if(dataname=="coudata")
              {
                  data=i.value().Cou;
                  datastr=QString::number(data,'f',6);
                  tempstr= tempstr+ PloIdstr+datastr+",";
              }
              else if(dataname=="mindata")
             {
                 data=i.value().Min;
                 datastr=QString::number(data,'f',6);
                 tempstr= tempstr+ PloIdstr+datastr+",";
             }
             else if(dataname=="maxdata")
             {
                  data=i.value().Max;
                  datastr=QString::number(data,'f',6);
                  tempstr= tempstr+ PloIdstr+datastr+",";
                  //tempstr= tempstr+ PloIdstr+datastr+","+factorPloId+"-Flag="+i.value().dataTitle+";";
             }
           }

        }
          tempstr= tempstr+factorPloId+"-Flag="+i.value().dataTitle+";";
    }
    if(sendstr.length()>0){
        sendstr=sendstr+tempstr;
        sendData(sendstr,olddatatime);
                         tempstr="";
                         sendstr="";
    }
}
/**
 * @brief Tcpclient::getDbData
 * @param starttime
 * @param endtime
 */
 QMap<int,Dbdata> Tcpclient::getDbData(QString starttime,QString endtime)
{
    float data=0;
     QString sqlstr;
     DbdataMap DbdataList;
     QSqlQuery query(db);
     sqlstr="select dataTime,data,coudata,mindata,maxdata,dataTitle,polId from hourfactor a,netpolid b where a.name=b.factorId and b.protocalId="+m_networkinfo.protocalId+" and  dataTime > ";
     sqlstr=sqlstr+"'" +starttime+"'"+" AND dataTime<"+"'" +endtime+"'";  //+ " GROUP BY dataTime"加上则同时间只显示一个
     query.exec("SET NAMES UTF8");
     query.exec(sqlstr);
     int index=0;

     while(query.next()){
          Dbdata Dbdatatemp;
         QString datastr=query.value(0).toString();
         int pos=datastr.indexOf(".");
         if(pos>=0)
           datastr=datastr.left(pos);
         Dbdatatemp.time=datastr;
         data=query.value(1).toFloat();
         Dbdatatemp.Avg=data;
         data=query.value(2).toFloat();
         Dbdatatemp.Cou=data;
         data=query.value(3).toFloat();
         Dbdatatemp.Min=data;
         data=query.value(4).toFloat();
         Dbdatatemp.Max=data;
         datastr=query.value(5).toString();
         Dbdatatemp.dataTitle=datastr;
         datastr=query.value(6).toString();
         Dbdatatemp.polId=datastr;
         DbdataList.insert(index++,Dbdatatemp);
     }
     return DbdataList;
}
 /**
  * @brief Tcpclient::getDbMinuteData
  * @param starttime
  * @param endtime
  */
  QMap<int,Dbdata> Tcpclient::getDbMinuteData(QString starttime,QString endtime)
 {
     float data=0;
      QString sqlstr;
      DbdataMap DbdataList;
      QSqlQuery query(db);
      sqlstr="select dataTime,data ,polId ,mindata,maxdata, coudata from minutefactor a,netpolid b where a.name=b.factorId and b.protocalId="+m_networkinfo.protocalId+" and dataTime > ";
      sqlstr=sqlstr+"'" +starttime+"'"+" AND dataTime<"+"'" +endtime+"'";  //+ " GROUP BY dataTime"加上则同时间只显示一个
      query.exec("SET NAMES UTF8");
      query.exec(sqlstr);
      int index=0;
      while(query.next()){
           Dbdata Dbdatatemp;
          QString datastr=query.value(0).toString();
          int pos=datastr.indexOf(".");
          if(pos>=0)
            datastr=datastr.left(pos);
          Dbdatatemp.time=datastr;
          data=query.value(1).toFloat();
          Dbdatatemp.Avg=data;
          datastr=query.value(2).toString();
           Dbdatatemp.polId=datastr;

           data=query.value(3).toFloat();
           Dbdatatemp.Min=data;
           data=query.value(4).toFloat();
           Dbdatatemp.Max=data;
           data=query.value(5).toFloat();
           Dbdatatemp.Cou=data;
          DbdataList.insert(index++,Dbdatatemp);
      }
      return DbdataList;
 }

  /**
   * @brief Tcpclient::getDbMinuteData
   * @param starttime
   * @param endtime
   */
   QMap<int,Dbdata> Tcpclient::getDblastMinuteData()
  {
      float data=0;
       QString sqlstr,timestr;
       timestr="";
       DbdataMap DbdataList;
       QSqlQuery query(db);
       sqlstr="select dataTime,data ,polId ,mindata,maxdata, coudata from minutefactor a,netpolid b where a.name=b.factorId and b.protocalId="+m_networkinfo.protocalId+" ";
       sqlstr=sqlstr+" order by dataTime desc";  //+ " GROUP BY dataTime"加上则同时间只显示一个
       query.exec("SET NAMES UTF8");
       query.exec(sqlstr);
       int index=0;
       while(query.next()){
            Dbdata Dbdatatemp;
           QString datastr=query.value(0).toString();
           int pos=datastr.indexOf(".");
           if(pos>=0)
             datastr=datastr.left(pos);
           Dbdatatemp.time=datastr;
           if(timestr.isEmpty())
               timestr=Dbdatatemp.time;
           if(timestr!=Dbdatatemp.time)
               break;
           data=query.value(1).toFloat();
           Dbdatatemp.Avg=data;
           datastr=query.value(2).toString();
            Dbdatatemp.polId=datastr;

            data=query.value(3).toFloat();
            Dbdatatemp.Min=data;
            data=query.value(4).toFloat();
            Dbdatatemp.Max=data;
            data=query.value(5).toFloat();
            Dbdatatemp.Cou=data;
            DbdataList.insert(index++,Dbdatatemp);
       }
       return DbdataList;
  }
/**
 * @brief Tcpclient::getnet212set
 */
void Tcpclient::getnet212set()
{
    QString sqlstr,datastr;
    QSqlQuery query(db);
    int index=0;
    sqlstr="select * from net212set where sendorno=1 and protocalId=";
    sqlstr=sqlstr+m_networkinfo.protocalId;
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    while(query.next()){
        net212set net212settemp;
        datastr=query.value("cn").toString();
        net212settemp.cn=datastr;
        datastr=query.value("contain").toString();
        net212settemp.contain=datastr;
          datastr=query.value("dataname").toString();
         net212settemp.dataname=datastr;
        net212setlist.insert(index++,net212settemp);
    }
}

unsigned int Tcpclient::CRC16_Checkout (  char *puchMsg, unsigned int usDataLen )
{
unsigned int i,j,crc_reg,check;
crc_reg = 0xFFFF;
for(i=0;i<usDataLen;i++)
{
crc_reg = (crc_reg>>8) ^ puchMsg[i];
 for(j=0;j<8;j++)
{
 check = crc_reg & 0x0001;
 crc_reg >>= 1;
 if(check==0x0001)
{
 crc_reg ^= 0xA001;
 }
 }
}
return crc_reg;
}
/*  2016.5.13修改原因以前的算法不能计算256以上个字符数据 */
unsigned  int  Tcpclient::CRC_16(char *modbusdata, int length)
{
    unsigned short int i, j;
    unsigned short int crc16 = 0xFFFF;
    for (i = 0; i < length; i++)
    {
        crc16 ^= modbusdata[i];//CRC = BYTE xor CRC
        for (j = 0; j < 8; j++)
        {

            if ((crc16 & 0x01) == 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            else
            {
                crc16 = crc16 >> 1;
            }
        }
    }
    return crc16;
  }
QString Tcpclient::getSendBytes(QString sendStr)
{
          if(sendStr.at(sendStr.length()-1)==";")
              sendStr= sendStr.left(sendStr.length()-1)+"&&";
          else
               sendStr= sendStr.left(sendStr.length())+"&&";
            char*  buf;
          // sendStr ="QN=20190918094936031;ST=31;CN=2011;PW=123456;MN=3310047002331004;CP=&&DataTime=20190918094800;116-Rtd=0.003,116-Flag=N;141-Rtd=0.017,141-Flag=N;102-Rtd=0.022,102-Flag=N;101-Rtd=0.010,101-Flag=N;106-Rtd=0.686,106-Flag=N;108-Rtd=0.127,108-Flag=N;107-Rtd=0.045,107-Flag=N;121-Rtd=0.025,121-Flag=N;126-Rtd=26.178,126-Flag=N;127-Rtd=1000.369,127-Flag=N;128-Rtd=67.230,128-Flag=N;129-Rtd=4.444,129-Flag=N;130-Rtd=21.350,130-Flag=N&&";
          QByteArray ba = sendStr.toLatin1(); // must
          buf=ba.data();
          int crc16 =0;
          QString crc16str;
          if(crctype==1)
          {
              crc16 = CRC16_Checkout (buf, sendStr.length());
              crc16str=QString("%1").arg(crc16,4,16,QLatin1Char('0'));
          }
          else if(crctype==2)
          {
              crc16 =CRC_16(buf, sendStr.length());
             crc16str=QString("%1").arg(crc16,4,16,QLatin1Char('0'));
             crc16str=crc16str.mid(2,2)+crc16str.mid(0,2);
          }
          else
          {
              crc16 =CRC_16(buf, sendStr.length());
             crc16str=QString("%1").arg(crc16,4,16,QLatin1Char('0'));
             crc16str=crc16str.mid(2,2)+crc16str.mid(0,2);
          }
          QString strTmp = "##"+QString("%1").arg(sendStr.length(),4,10,QLatin1Char('0')) +sendStr+ crc16str+"\r\n";
          return strTmp;
 }
/**
* @brief dbbase::insertdata 插入数据到数据库
* @param valuedata 需要插入数据库的值
* @return
*/
bool Tcpclient::insertdata(QStringList valuedata,QStringList columnName,QString tablename)
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
bool Tcpclient::updata(QStringList columndata,QStringList valuedata,int valuedatanum,QString tablename)
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
 * @brief Tcpclient::sendData
 * @param sendstr
 */
void Tcpclient::sendData(QString sendstr,QString olddatatime)
{
                    QString alldata;
                    alldata=getSendBytes(sendstr);
                    writedata(alldata);
                    QStringList columnnamelist,columndatalist;
                    columnnamelist<< "hourdatetime"<<"id" ;//QStringList
                    columndatalist.append(olddatatime);
                    columndatalist.append(m_networkinfo.id);
                    updata(columnnamelist,columndatalist,1,"networkset");
}
/**
 * @brief Tcpclient::sendData
 * @param sendstr
 */
void Tcpclient::send2051Data(QString sendstr,QString olddatatime)
{
                    QString alldata;
                    alldata=getSendBytes(sendstr);
                    writedata(alldata);
                    QStringList columnnamelist,columndatalist;
                    columnnamelist<< "minutedatetime"<<"id" ;//QStringList
                    columndatalist.append(olddatatime);
                    columndatalist.append(m_networkinfo.id);
                    updata(columnnamelist,columndatalist,1,"networkset");
}
/**发送心跳包
 * @brief Tcpclient::sendheadpackage
 */
void Tcpclient::sendheadpackage()
{
    QString headstr= getheaddata("9015",m_networkinfo.sendFlag);
    QString strQN;
    strQN=helpclass.currenttimetostrid();
    strQN="QN="+strQN;
    QString alldata;
    alldata=getSendBytes(strQN+headstr);
    writedata(alldata);
}

/**获取2011
 * @brief Tcpclient::get2061Pkg
 * @param strQN
 * @param recDataTime
 * @param buf
 */
void Tcpclient::get2011Pkg(QString strQN)
{
    QString headstr= getheaddata("2011",m_networkinfo.sendFlag);
    QString sendstr="",factorPloId,tempstr,datastr,dataname,olddatatime;
    float data;
  DbdataMap DbdataList;

    DbdataList=getDblastMinuteData();
    bool first=false;
    QMapIterator<int,Dbdata> i(DbdataList);
    while (i.hasNext())
    {
        QMapIterator<int,net212set>net (net212setlist);
         i.next();
         if(olddatatime!=i.value().time)
         {
             if(first==true)
             {
                 sendstr=sendstr+tempstr;
                 QString alldata;
                 alldata=getSendBytes(sendstr);
                 writedata(alldata);
                  tempstr="";
                  sendstr="";
                  sleep(1);
             }
             olddatatime=i.value().time;
             sendstr=strQN+headstr+"DataTime="+helpclass.getTimeToNumb(olddatatime)+";";
             first=true;
         }
         factorPloId=i.value().polId;
        while(net.hasNext())
        {
            net.next();
           QString  PloIdstr= factorPloId+"-"+net.value().contain+"=";
           dataname=net.value().dataname;
           if(net.value().cn=="2011")
           {
               if(net.value().dataname=="data")
               {
                   data=i.value().Avg;
                   datastr=QString::number(data,'f',6);
                   tempstr= tempstr+ PloIdstr+datastr+",";
               }

           }

        }
          tempstr= tempstr+factorPloId+"-Flag="+"N;";
    }
    if(sendstr.length()>0){
        sendstr=sendstr+tempstr;
        QString alldata;
        alldata=getSendBytes(sendstr);
        writedata(alldata);
                         tempstr="";
                         sendstr="";
    }
}

/**获取2051
 * @brief Tcpclient::get2061Pkg
 * @param strQN
 * @param recDataTime
 * @param buf
 */
void Tcpclient::get2051Pkg(QString strQN, QString starttime,QString endtime)
{
    QString headstr= getheaddata("2051",m_networkinfo.sendFlag);
    QString sendstr="",factorPloId,tempstr,datastr,dataname,olddatatime;
    float data;
  DbdataMap DbdataList;

    DbdataList=getDbMinuteData(starttime, endtime);
    bool first=false;
    QMapIterator<int,Dbdata> i(DbdataList);
    while (i.hasNext())
    {
        QMapIterator<int,net212set>net (net212setlist);
         i.next();
         if(olddatatime!=i.value().time)
         {
             if(first==true)
             {
                 sendstr=sendstr+tempstr;
                 send2051Data(sendstr,olddatatime);
                  tempstr="";
                  sendstr="";
                  sleep(1);
             }
             olddatatime=i.value().time;
             sendstr=strQN+headstr+"DataTime="+helpclass.getTimeToNumb(olddatatime)+";";
             first=true;
         }
         factorPloId=i.value().polId;
        while(net.hasNext())
        {
            net.next();
           QString  PloIdstr= factorPloId+"-"+net.value().contain+"=";
           dataname=net.value().dataname;
           if(net.value().cn=="2051")
           {
               if(net.value().dataname=="data")
               {
                   data=i.value().Avg;
                   datastr=QString::number(data,'f',6);
                   tempstr= tempstr+ PloIdstr+datastr+",";
               }
               else if(dataname=="coudata")
              {
                  data=i.value().Cou;
                  datastr=QString::number(data,'f',6);
                  tempstr= tempstr+ PloIdstr+datastr+",";
              }
              else if(dataname=="mindata")
             {
                 data=i.value().Min;
                 datastr=QString::number(data,'f',6);
                 tempstr= tempstr+ PloIdstr+datastr+",";
             }
             else if(dataname=="maxdata")
             {
                  data=i.value().Max;
                  datastr=QString::number(data,'f',6);
                  tempstr= tempstr+ PloIdstr+datastr+",";
                  //tempstr= tempstr+ PloIdstr+datastr+","+factorPloId+"-Flag="+i.value().dataTitle+";";
             }

           }

        }
          tempstr= tempstr+factorPloId+"-Flag="+"N;";
    }
    if(sendstr.length()>0){
        sendstr=sendstr+tempstr;
        send2051Data(sendstr,olddatatime);
                         tempstr="";
                         sendstr="";
    }
}
