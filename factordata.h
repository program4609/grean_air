#ifndef FACTORDATA_H
#define FACTORDATA_H

#include <QObject>
#include "db\dbminutefactor.h"
#include "db\dbhourfactor.h"
#include "db\dbfiveminutefactor.h"
#include "db/dbtempdata.h"
#include "help.h"

struct factorinfo
{
     int id;
    QString name;
    float mindata;
    float maxdata;
    QString unit;
    int dataNum;
    QString type;
    float modulus;
    int need_upload;
    QString datastr;
    QString instrumentName;
    float data;
    float hourdata;
    int mode;

};
class factorData// : public QObject
{
  //  Q_OBJECT
public:
    explicit factorData();
    void init();
    void adddata(float data,int modetype);
    void initdata();
     QStringList  savemindata();
    QStringList savefivemindata();
   QStringList savehourdata();
   QStringList savedaydata();
    void initmindata();
    void initfivemindata();
    void inithourdata();
    void initdaydata();
     QStringList getfiveminutedbData(double data,double cou,double min,double max,QString title);
    QStringList savetempdata(bool connect);

    QStringList getdbData(double data,double cou,double min,double max,QString title);
    QStringList gethourdbData(double data,double cou,double min,double max,QString title);
    factorinfo getfactorinfo();
      void  setfactorinfo(factorinfo &factorinfotemp);
      void setDatabaseDb(QSqlDatabase db);
       factorinfo factorinfodata;
private:
   int id;

   int minindex;
   int hourindex;
   int fiveminindex;
   int dayindex;

   double minsumdata;
   double hoursumdata;
   double fivesumdata;
   double daysumdata;
   double oldminsumdata;

   double minmindata;
   double minmaxdata;
   double fiveminmindata;
   double fiveminmaxdata;
   double hourmindata;
   double hourmaxdata;
   double daymindata;
   double daymaxdata;

   dbfiveminutefactor *dbfiveminutefactordata;
   minutefactor *minutefactordata;
   dbhourfactor *dbhourfactordata;
    dbtempdata *dbtempdataclass;
   QSqlDatabase m_db;
   help helpclass;

//signals:

//public slots:
};

#endif // FACTORDATA_H
