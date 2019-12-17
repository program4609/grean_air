#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "instrumentmanage.h"
#include<QTableView>
#include<QComboBox>
#include<QTime>
#include "qcustomplot.h"
#include "db\dbcontrol.h"
#include "tcpclient.h"
#include "navbutton.h"
#include "frmdevice.h"
#include"panelwidget.h"
#include "unit.h"
#include "info.h"
#include "othordlg.h"
#include "qixiangdlg.h"
#include "setinfodlg.h"
#define maintabnum 6
#define systemtabnum 3
extern instrumentManage *pinstrumentManage;
extern   help helpclass;
namespace Ui {
class MainWindow;
}
#define MAX_PLOT 8
#define MAX_DRAW 10
#define MAX_NETWORK_NUM 20
struct ComboBoxdata
{
    QString name;
    int index;
};
struct Ring
{
   bool airConditionerOpen;
};
Q_DECLARE_METATYPE(ComboBoxdata)
class NavButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void infoRecv(datainfomap,QString,QString id);
     void comRecv(QString,QString);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  void init();
  static QString loginName,loginPassword,loginType;
  //static instrumentManage *pinstrumentManage;
private slots:



    void on_tableView_3_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_tableView_7_clicked(const QModelIndex &index);

    void on_tableView_6_clicked(const QModelIndex &index);

    void on_pushButton_21_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void mainClick();
   // void dataClick();
    void systemClick();

    void on_tableView_15_clicked(const QModelIndex &index);

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_2_clicked();

    void on_navButton6_clicked();

    void on_pushButton_45_clicked();

    void on_tableView_8_clicked(const QModelIndex &index);



    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_40_clicked();

  //  void on_pushButton_9_clicked();

  //  void on_pushButton_11_clicked();



    void on_pushButton_47_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_49_clicked();


    //void on_pushButton_7_clicked();

   // void on_pushButton_8_clicked();

    void on_listView_pressed(const QModelIndex &index);




    void on_listView_2_pressed(const QModelIndex &index);

    void on_navButton1_clicked();

    void on_tableView_9_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_37_clicked();

   // void myMoveEvent(QMouseEvent *event);
    void on_comboBox_14_currentTextChanged(const QString &arg1);

 //   void on_btnMain_clicked();

protected:
     void paintEvent(QPaintEvent *event);
      void resizeEvent(QResizeEvent *event);
private:
      QRect rectMove;
      int Othorfactorindex;
       QWidget *othorfactorwidget;
       QFrame * othorfactorframe;
    QString logtypestr,histroydatatypestr;
    Ui::MainWindow *ui;
     QList<QToolButton *> mainbtns;
     QList<NavButton *>databtns;
     QList<NavButton *>systembtns;
     QList<QLabel *>factordatalist;
      QScrollArea *scrollArea;
     QList<frmdevice *> frms;
     QList<unit *> unitdlg;
     QList<unit *> zhanfangdlg;
     QList<unit *> gongdiandlg;
     QList<unit *> biaoqidlg;
     QList<unit *> caiyangdlg;
     QList<unit *> qitadlg;
     QList<Info *> infodlg;
     QList<Othordlg *>othordlg;
     QList<qixiangdlg *>qixiangdlglist;

     QList<setinfoDlg *>factorsetdlglist;
     QList<setinfoDlg *>instrumentsetdlglist;
     QList<setinfoDlg *>qualitysetdlglist;
     QList<setinfoDlg *>ctrlcmdsetdlglist;
     QList<setinfoDlg *>searchcmdsetdlglist;
     QList<setinfoDlg *>instrumentconnectsetdlglist;
     QList<setinfoDlg *>networksetdlglist;
     QList<setinfoDlg *>networkfactorIdsetdlglist;
     QList<setinfoDlg *>othersetdlglist;
     QList<setinfoDlg *>usersetdlglist;
     QString factorId,instrumentId,networkId,networkfactorId,queryId,ctrlCmdId,instrumentconnectId,searchcmdId,usersetId;
     bool insertsearchCmd;
//    QTimer dataTimer;
  //  int timeID;
    int timedrawId,sqlTimeIdrefresh,instrumentTimeId;
    QString namestr;
    QString Idstr;
    QString userId;
    QString MultipleParameters;

    Ring ring;

    QCustomPlot *pCustomPlot[MAX_PLOT];
    QCPTextElement *qCPTextElement;
      bool showtype[MAX_PLOT];

     dbinstrument dbinstrumentclass;
     DbControl *pDbControl;
     Tcpclient *pTcpclient[MAX_NETWORK_NUM];
     int tepclientindex;
 QSqlQueryModel  *realtimequerymodel ,*instrumentquerymodel,*factorquerymodel,*CtrlCmdquerymodel,*searchCmdquerymodel,*communicationquerymodel,*instrumentmodemodel,*networkquerymodel,*factornetIdquerymodel,*userquerymodel,*logquerymodel;
 QSqlQueryModel *maintainquerymodel,*alarmquerymodel;
 ctrlInstrument *qdonghuaninstrument;
 // QLabel *label[2];
  void initdraw();
    QSqlQueryModel *historyquerymodel;
   QCPGraph *graph1;
    /*系统设置部分 */
    void setTableView(QTableView *TableView,int row_count);
    void initInstrumentQueryModel();
    void initInstrumentComboBox();
    void initFactorQueryModel();
    void initFactorComboBox();
    void initCtrlCmdQueryModel();
    void initCtrlCmdComboBox();
    void initSearchCmdQueryModel();
    void initSearchCmdComboBox();
    void initCommunicationQueryModel();
    void initCommunicationComboBox();
    void initNetWorkQueryModel();
    void initNetWorkComboBox();
    void initHistoryComboBox();
    void settableColumnWidth(int columncount,QTableView *tableView);
    void initFactornetIDQueryModel();
    void initFactornetIDComboBox();
    void initnetwork();
    void initStyle();
    void initbutton();
    void showinfo();
    void initUserQueryModel();
    void initmaintainQueryModel();
    void initUserCombox();
    void initlogCombox();
    void initPanelWidget();
    void initsystemsetPanelWidget();
    void showRealData();
    void initlogModel();
    void initalarmquerymodel();
    void initvideo(bool show);
    void setiniData(QString filename,QString titlestr,QString data);
    QString getiniData(QString filename,QString titlestr);
    void historyinitdraw();
    void settableparame(QSqlQueryModel *querymodel,QTableView *tableView);
    void exportMsg(QStringList headtitleList,QSqlQueryModel *querymodel,QTableView *tableView);
    void  logsearch(QString typestr);
    void  historysearch(QString typestr);
     QStringList getTableViewRowData(QTableView *TableView,int row,int columnCount);
    void setzhangfangDlg();
    void startinstrumentCmd(QString instrumentname,QString cmd);
    void initinstrumentmodeQueryModel();
    void setfactorId(QString id);
    QString getfactorId();
    void setinstrumentId(QString id);
    QString getinstrumentId();
    void setnetworkId(QString id);
    QString getnetworkId();
    void setnetworkfactorId(QString id);
    QString getnetworkfactorId();
    void setqueryId(QString id);
    QString getqueryId();
    void setctrlCmdId(QString id);
    QString getctrlCmdId();
    QString  getsearchCmdId();
    void setsearchCmdId(QString id);
    QString getinstrumentconnectId();
    void  setinstrumentconnectId(QString id);
    QString getusersetId();
    void  setusersetId(QString id);
    void initdlg(QString sqlstr, PanelWidget *widgetPanel,QString type);
    void setdlginfo(QList<setinfoDlg *> dlglist,QStringList namelist,QStringList datalist,QString id);
    QString fromintoName(QString sqlstr);
   void initfactorDlg();
   void  initinstrumentDlg();
    void initqualitysetDlg();
    void initctrlcmdDlg();
    void initsearchcmdDlg();
    void initinstrumentconnectDlg();
    void initnetworkDlg();
    void initnetworkfactorIdDlg(QString xieyi);
    void inituserDlg();
    void setdlginfoselect(QList<setinfoDlg *> dlglist,QString id);

    void initOtherfactor();
    void showOtherfactor();
     void initmulUI();
    /*  结束 */
    /*控件操作*/
    QStringList getTableViewRowData(QTableView *TableView,int columnCount);
    void initcomboBox(QComboBox *comboBox,QString sqlstr);//初始化下拉控件
    void initcomboBox(QComboBox *comboBox,QString sqlstr,int num);
      void realtimeDataSlot();
    /* */
    /*数据及报表查询*/
   void initHistoryModel();
   void  initListview();
    /* */
    void SetTabEnable();
   // void SetSystemTabEnable(bool type);
    void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
