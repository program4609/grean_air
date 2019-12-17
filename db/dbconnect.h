#ifndef DBCONNECT_H
#define DBCONNECT_H
#include <QSqlDatabase>
#include"dbbase.h"
class dbconnect
{
public:
    dbconnect();
    bool connectmysql();
};

#endif // DBCONNECT_H
