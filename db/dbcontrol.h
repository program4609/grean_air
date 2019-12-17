#ifndef DBCONTROL_H
#define DBCONTROL_H
#include "dbbase.h"
#include "dbfactor.h"
#include "dbinstrument.h"
#include "dbinstrumentcmd.h"
#include "dbinstrumentsearch.h"
#include "dbnetpolid.h"
#include "dbnetworkset.h"
#include "dbcfg_user.h"
#include "help.h"
#include "dblog.h"
#include"maintain.h"

class DbControl
{
public:
    DbControl();
    bool factorinsertData(QStringList valuedata);
    bool factorupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool factordelete(QStringList columndata,QStringList valuedata);

    bool instrumentinsertData(QStringList valuedata);
    bool instrumentupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool instrumentdelete(QStringList columndata,QStringList valuedata);

    bool CtrlCmdinsertData(QStringList valuedata);
    bool CtrlCmdupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool CtrlCmddelete(QStringList columndata,QStringList valuedata);

    bool searchCmdinsertData(QStringList valuedata);
    bool searchCmdupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool searchCmddelete(QStringList columndata,QStringList valuedata);

    bool netpolidinsertData(QStringList valuedata);
    bool netpolidupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool netpoliddelete(QStringList columndata,QStringList valuedata);


    bool networksetinsertData(QStringList valuedata);
    bool networksetupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool networksetdelete(QStringList columndata,QStringList valuedata);

    bool userinsertData(QStringList valuedata);
    bool userupdateData(QStringList columndata,QStringList valuedata,int valuedatanum);
    bool userdelete(QStringList columndata,QStringList valuedata);

    bool loginsertData(QStringList valuedata);

    bool maintaininsertData(QStringList valuedata);

private:
    dbfactor *pdbfactor;
    dbinstrument *pdbinstrument;
    dbinstrumentcmd *pdbinstrumentcmd;
    dbinstrumentsearch *pdbinstrumentsearch;
    dbnetpolid *pdbnetpolid;
    dbnetworkset *pdbnetworkset;
    dbcfg_user *pdbcfg_user;
    dblog *pdblog;
    help helpclass;
    maintain *qmaintain;

};

#endif // DBCONTROL_H
