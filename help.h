#ifndef HELP_H
#define HELP_H

#include <QObject>
#include<QDateTime>
#include <QSqlQueryModel>
#include<QTableView>
#include <QMainWindow>
struct datainfo
{
    QString name;
    QString data;
    double  doubledata;
    bool    booldata;
    int     datatype;
};
typedef QMap<QString,datainfo>datainfomap;
class help
{

public:
    explicit help();
QString currenttimetostr();
 QString currenttimetostrid();
  QString currenttimetostridnomm();
 QString getTimeToNumb(QString Timestr);
 double getDataN(float data,int N);
 QString currenttimetostr(QStringList factorList);
 QString hourtimetostr();
 QString minutetimetostr();
 QString currenttimetostrinterface();
 bool ShowMessageBox(QString titlestr);
QString GetDataFromBuf(char *Buf,int index,char c,int startindex);
void setiniData(QString filename,QString titlestr,QString data);
QString getiniData(QString filename,QString titlestr);
bool checknum(QString datastr);
bool ShowoneMessageBox(QString titlestr);
signals:

public slots:
};

#endif // HELP_H
