#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include<QThread>
#include <QSqlDatabase>
#include "help.h"
#include "db\dbnetworkset.h"
#include "db\dbcontrol.h"
struct networkinfo
{
    QString id;
   QString ip;
   int port;
   QString protocalId;
   QString mn;
   QString password;
   QString st;
   QString hourdatetime;
   QString minutedatetime;
   int sendFlag;
   int requestFlag;
   int crctype;
};
struct Dbdata
{
   QString factorname;
   int factorId;
   QString time;
   QString dataTitle;
   QString polId;
   float Avg;
   float Cou;
   float Min;
   float Max;
};
struct net212set
{
    QString cn;
    QString contain;
    QString dataname;
};
class Tcpclient : public QThread //QObject
{
    Q_OBJECT
private:
      typedef QMap<int,Dbdata>DbdataMap;
public:
     Tcpclient();
    bool  connectServer(QString ip,int port);
    void writedata(QString data);
      void run();
      void initdata(networkinfo networkinfos);
      bool initDb();
      QString readSendTime();
      QString getheaddata(QString cn,int flag);
     void get2061Pkg(QString strQN, QString starttime,QString endtime);

     void get2011Pkg(QString strQN);
     void get2051Pkg(QString strQN, QString starttime,QString endtime);
     QMap<int,Dbdata> getDbData(QString starttime,QString endtime);
     void getnet212set();
     unsigned int CRC16_Checkout ( char *puchMsg, unsigned int usDataLen ) ;
     QString getSendBytes(QString sendStr);
       void sendheadpackage();
       void initclient();
       bool insertdata(QStringList valuedata,QStringList columnName,QString tablename);
      QMap<int,Dbdata> getDbMinuteData(QString starttime,QString endtime);
       QMap<int,Dbdata> getDblastMinuteData();
      QString read2051SendTime();
      void send2051Data(QString sendstr,QString olddatatime);
      unsigned  int  CRC_16(char *modbusdata, int length);
private:
     QTcpSocket *tcpClient;
    DbControl *pDbControl;
    int crctype;
     QString m_ip;
     networkinfo m_networkinfo;
     bool netconnect;
    int m_port;
  QSqlDatabase db;

 // DbdataMap DbdataList;
  typedef QMap<int,net212set> net212setmap;
  net212setmap net212setlist;
  help helpclass;
  bool  openDb();
  bool updata(QStringList columndata,QStringList valuedata,int valuedatanum,QString tablename);
  void sendData(QString sendstr,QString olddatatime);

//signals:
private slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
     void slotDisconnected();
//public slots:
};

#endif // TCPCLIENT_H
