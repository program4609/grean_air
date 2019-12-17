#include "dbbase.h"

 dbbase::dbbase()
{
     querymodel=new QSqlQueryModel;
     model=new QSqlTableModel;
   //  query=new QSqlQuery();
    initdata();
}

 /**
 * @brief dbbase::insertdata 插入数据到数据库
 * @param valuedata 需要插入数据库的值
 * @return
 */
bool dbbase::insertdata(QStringList valuedata)
{
     QString sqlstr,columnstr,valuestr;
    QSqlQuery query;
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
         QString str=valuedata.at(j);
         if(!str.isEmpty())
           query.bindValue(j, valuedata.at(j));
         else
           query.bindValue(j, "0");
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
bool dbbase::updata(QStringList columndata,QStringList valuedata,int valuedatanum)
{
    QSqlQuery query;
    QString sqlstr,columnstr;
    sqlstr="update "+tablename +" set ";
    if(columndata.size()!=valuedata.size())
        return false;
    else
      valuedatanum= valuedata.size()-1;
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
 * @brief dbbase::deletedata  删除数据
 * @param columndata  列名
 * @param valuedata   满足条件列的值
 * @return
 */
bool dbbase::deletedata(QStringList columndata,QStringList valuedata)
{
     QSqlQuery query;
    QString sqlstr,columnstr;
    sqlstr="delete from "+tablename +" where ";
    if(columndata.size()!=valuedata.size())
        return false;
     for(int i=0;i<columndata.size();i++)
     {
         if(i==0)
         {
               columnstr=columnstr+columndata.at(i)+"=?";
         }
         else
             columnstr=columnstr+" and "+columndata.at(i)+"=?";
         query.bindValue(i,valuedata.at(i));
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
  查询列表
  * @brief dbbase::searchdata
  * @param sqlstr
  * @return
  */
 QSqlQuery dbbase::searchdata(QString sqlstr)
 {
     QSqlQuery  query;
     query.exec("SET NAMES UTF8");
     query.exec(sqlstr);
     return query;
 }

 bool dbbase::Finddata(QString sqlstr)
 {
     QSqlQuery  query;
     query.exec("SET NAMES UTF8");
     query.exec(sqlstr);

     if(query.next())
     {
       return true;
     }
        return false;
 }
 /**返回查询选中仪器所有因子
  * @brief help::getSelectFactorSqlstr
  * @return
  */
 QStringList dbbase::getSelectFactorList()
 {
      QSqlQuery query;
      QStringList factorList;
     QString sqlstr="SELECT a.name,d.label FROM factor a,instrumentsearch b ,instrument c ,combo_box d WHERE a.id=b.factorId and c.checked='是' and b.instrumentId=c.id and a.unit=d.value and d.type='unit' and a.type='显示'";
     query=searchdata(sqlstr);
     while(query.next())
     {
           QString data=query.value("name").toString();
           QString unitstr=query.value("label").toString();
           factorList.append(data+"("+unitstr+")");
     }
     return factorList;
 }
 /**返回查询选中仪器所有因子
  * @brief help::getSelectFactorSqlstr
  * @return
  */
 QStringList dbbase::getSelectFactoridList()
 {
      QSqlQuery query;
      QStringList factorList;
     QString sqlstr="SELECT a.id FROM factor a,instrumentsearch b ,instrument c WHERE a.id=b.factorId and c.checked='是' and b.instrumentId=c.id and a.type='显示'";
     query=searchdata(sqlstr);
     while(query.next())
     {
           QString data=query.value("id").toString();
           factorList.append(data);
     }
     return factorList;
 }
 /**生成历史数据查询语句
  * @brief dbbase::getHistorySqlstr
  * @param factorList 选中所有因子名称
  * @param tableName 需要查询表名称
  * @return
  */
 QString dbbase::getHistorySqlstr(QStringList factorList,QString tableName)
 {
  // QString sqlstr=  SELECT dataTime ,MAX(CASE name WHEN '温度' THEN  data  END)'温度',MAX(CASE name WHEN 'pM2.5' THEN  data  END)'pM2.5' from minutefactor GROUP BY dataTime
      QString sqlstr=  "SELECT dataTime ",tempstr;

      for(int i=0;i<factorList.size();i++)
      {
          tempstr=tempstr+",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN data END)"+"'"+factorList.at(i)+"'";
      }
      sqlstr=sqlstr+tempstr+" from "+tableName+" GROUP BY dataTime";
      return sqlstr;
 }

 /**生成历史数据查询语句
  * @brief dbbase::getHistorySqlstr
  * @param factorList 选中所有因子名称
  * @param tableName 需要查询表名称
  * @return
  */
 QString dbbase::getHistorySqlstrFromTime(QStringList factorList,QString tableName,QString starttime,QString endtime)
 {

      QString sqlstr=  "SELECT dataTime ",tempstr;

      for(int i=0;i<factorList.size();i++)
      {
          tempstr=tempstr+",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN data END)"+"'"+factorList.at(i)+"'";
      }
      // sqlstr=sqlstr+tempstr+" from "+tableName+" GROUP BY dataTime";
      sqlstr=sqlstr+tempstr+" from "+tableName+" where dataTime BETWEEN "+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+ " GROUP BY dataTime";
      return sqlstr;
 }

 /**生成历史数据查询语句(查询包括AVG,COU,MIN,MAX)
  * @brief dbbase::getHistorySqlstr
  * @param factorList 选中所有因子名称
  * @param tableName 需要查询表名称
  * @return
  */
 QString dbbase::getHistoryAllSqlstrFromTime(QStringList factorList,QString tableName,QString starttime,QString endtime)
 {

      QString sqlstr=  "SELECT dataTime ",tempstr;

      for(int i=0;i<factorList.size();i++)
      {
          tempstr=tempstr+",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN data END)"+"'"+factorList.at(i)+"Avg'" +",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN coudata END)"+"'"+factorList.at(i)+"Cou'"+",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN mindata END)"+"'"+factorList.at(i)+"Min'"+",MAX(CASE name WHEN "+"'"+factorList.at(i)+"'" +"THEN maxdata END)"+"'"+factorList.at(i)+"Max'";
      }
      // sqlstr=sqlstr+tempstr+" from "+tableName+" GROUP BY dataTime";
      sqlstr=sqlstr+tempstr+" from "+tableName+" where dataTime BETWEEN "+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+ " GROUP BY dataTime";
      return sqlstr;
 }
