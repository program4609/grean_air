#ifndef DBBASE_H
#define DBBASE_H
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QSqlQuery>
#include<QStringList>


class dbbase
{
public:
   dbbase();
   virtual void initdata(){};
//    QSqlQuery *query;
    QString tablename;//表名
    QStringList columnName;//表中列名称
    bool  insertdata(QStringList valuedata);
    bool updata(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool deletedata(QStringList columndata,QStringList valuedata);
    QSqlQuery searchdata(QString sqlstr);
     bool Finddata(QString sqlstr);
     QStringList getSelectFactorList();
     QStringList getSelectFactoridList();
     QString getHistorySqlstr(QStringList factorList,QString tableName);
    QString getHistorySqlstrFromTime(QStringList factorList,QString tableName,QString starttime,QString endtime);
     QString getHistoryAllSqlstrFromTime(QStringList factorList,QString tableName,QString starttime,QString endtime);

private:
    QSqlQueryModel *querymodel;
    QSqlTableModel *model;
     QSqlDatabase m_db;
     bool threaddb;
};

#endif // DBBASE_H
