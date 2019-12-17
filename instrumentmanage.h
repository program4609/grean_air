#ifndef INSTRUMENTMANAGE_H
#define INSTRUMENTMANAGE_H
#include "db\dbinstrument.h"
#include "ctrlinstrument.h"
#include <QThread>
#include<QMap>
#include<QPointer>
#define MAX_INSTRUMENT  30



//class managethread ;
class instrumentManage:public QObject
{
    Q_OBJECT

public:
    instrumentManage();
    dbinstrument *dbinstrumentclass;

     void init();
     //void ComSend();
    factorDatatype getAlldata();
 //   factorDatatype getdata();
    factorInfotype getFactorinfo();
    QStringList  getInstrumetNameinfo();
    factorDatatype getfactordata(QString Name);
    void settestmode(QString instrumentName,int mode);
    int getinstrumentIndex();
    factorinfo getFactorinfo(QString factorName);
   // void sendcomdata (QString instrumentname,QString  cmd){ emit comSend(instrumentname, cmd);}
    //void savetempdata(factorinfo factorinfodata);
       //  managethread *qmanagethread;
     ctrlInstrument *m_ctrlInstrument[MAX_INSTRUMENT];
signals:
    void comSend(QString ,QString);
private slots:
    void comRecv(QString,QString);
private:
 //   QMap<QString ,*ctrlInstrument>ctrlInstrumentmap;

  int instrumentIndex;
  QStringList instrumentNameList;
     //    QList<QPointer<ctrlInstrument>>ctrlInstrumentmap;

};




#endif // INSTRUMENTMANAGE_H
