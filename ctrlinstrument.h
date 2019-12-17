#ifndef CTRLINSTRUMENT_H
#define CTRLINSTRUMENT_H
#include <QThread>
#include <QObject>
#include <QSerialPort>
#include<QMap>
#include<QMutex>
#include "factordata.h"
#include <QTcpSocket>
#include "db\dbinstrumentsearch.h"
union floatdata
  {
      float data;
      char buf[4];
  };
struct factorAd
{
    int factorId;
    float revDataMin;
    float revDataMax;
    float factorMin;
    float factorMax;
};
struct instrumentsearch
{
  QString cmd;
 QString  addr;
 int num;
 QString formula;
 int factorId;
 int instrumentId;
 int formulaId;
 bool factorAd;
 float revDataMin;
 float revDataMax;
 float factorMin;
 float factorMax;
};
struct instrumentcmd
{
  QString cmd;
  QString name;
};
struct instrumentinfo
{
    int id;
    QString name;
    QString type;
    int baudrate;
    QString parity;
    int port;
    QString ip;
    int stopBit;
    int checked;
    QString communicationType;
    QString autoReadType;
    int testmode;
    int comID;
    int waittime;
};
typedef QMap <int,factorData> factorDatatype;
typedef QMap <int,factorinfo> factorInfotype;
//class mythread;
class ctrlInstrument :public QThread
{
   Q_OBJECT
public:
    explicit ctrlInstrument();//QObject *parent = nullptr
    void initdata(instrumentinfo instrument);
    void init(instrumentinfo instrument);
    // void readData();

   ctrlInstrument getClass();


//signals:
signals:
    void instrumentcomSend(QString ,QString);
//public slots:
public:
   // mythread *pmythread;
     mythread();
     void run();
      void ComRev();
      bool setcomport();
      void ComSend();
       bool openDb();
       float GetFactorData(QByteArray data,int factorid);
      void SaveData(int type);
      void SavetempData();
      void setsearchcmd();
      void setfactor();
     void  setconnectionstatus(bool data);
     bool isconnectionstatus();
     bool updata(QStringList columndata,QStringList valuedata,int valuedatanum,QString tablename);
    bool insertdata(QStringList valuedata,QStringList columnName,QString tablename);
    instrumentinfo getinstrumentinfo();
    factorDatatype getfactorDataMap();
    QByteArray hexstrTobyte(QString str);
    void settestmode(int mode);
    void setCtrlcmd();
    bool sendinstrumentCmd();
    bool setinstrumentCmd(QString cmdname);
      void  checkPassword(QByteArray responseData);
      int getshowfactornum();
      void initclient();
      bool  senddata(QByteArray requestData,QByteArray &responseData,int time);
      bool connectServer(QString ip,int port);
     instrumentinfo instrumentinfodata;
 private:
//    ctrlInstrument pctrlInstrument;
    bool autoReadType;
    bool netconnect;
     QSerialPort *m_serial ;//= nullptr;
      QTcpSocket *tcpClient;
     dbinstrumentsearch *dbinstrumentsearchclass;
     bool menjingtype;
     factorDatatype factorDatamap;
    // factorinfo factorinfodata;
    QString m_cmdname;
    typedef QMap<int,instrumentsearch>instrumentsearchtype;
    typedef QMap<QString,instrumentcmd>instrumentcmdtype;
     instrumentcmdtype instrumentcmdtypelist;
     instrumentsearchtype instrumentsearchmap;

     int connectionstatus;//连接状态
     help helpclass;
     QSqlDatabase db;
     // QSqlQuery *query;
private slots:
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
     void slotDisconnected();
};


#endif // CTRLINSTRUMENT_H
