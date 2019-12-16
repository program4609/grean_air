#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db\dbconnect.h"
#include "frmdevice.h"
#include"panelwidget.h"
#include "logindlg.h"
#include "applive.h"

int plot[MAX_PLOT]={0,0};
QString MainWindow::loginName="",MainWindow::loginPassword="",MainWindow::loginType="";
instrumentManage *pinstrumentManage=NULL;
help helpclass;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    dbconnect db;
    if(db.connectmysql())
    {

    }
    qdonghuaninstrument=NULL;
    scrollArea=NULL;
 //    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);//去掉边框
    ui->setupUi(this);
    pinstrumentManage=new instrumentManage;
    connect(pinstrumentManage ,SIGNAL(comSend(QString,QString)) ,this ,SLOT(comRecv(QString,QString)));
    instrumentquerymodel= new QSqlQueryModel;
    factorquerymodel=new QSqlQueryModel;
    CtrlCmdquerymodel=new QSqlQueryModel;
    searchCmdquerymodel=new QSqlQueryModel;
    communicationquerymodel=new QSqlQueryModel;
    instrumentmodemodel=new QSqlQueryModel;
    networkquerymodel=new QSqlQueryModel;
    factornetIdquerymodel=new QSqlQueryModel;
    userquerymodel=new QSqlQueryModel;
    logquerymodel=new QSqlQueryModel;
    maintainquerymodel=new QSqlQueryModel;
    alarmquerymodel=new QSqlQueryModel;

    pinstrumentManage->init();
    ui->tabWidget->setCurrentIndex(6);
    SetTabEnable();
    init();
    initStyle();
    initbutton();
    initListview();

   // ui->frame_4->setStyleSheet("QFrame{border: 0px;}") ;//去掉边框
    ui->frame_2->setStyleSheet(".QFrame{border:0px;}") ;//去掉边框前面加上.不影响子类
    ui->frame->setStyleSheet("QFrame{border: 0px;background:transparent;}") ;//去掉边框
    ui->frame_5->setStyleSheet("QFrame{border: 0px;}") ;//去掉边框
    ui->tabWidget->setStyleSheet("QTabWidget{border: 0px;}") ;//去掉边框
    ui->tabWidget->setStyleSheet("QTabWidget::pane{border-width: 0px; border-style: solid; border-color: rgb(230, 230, 230); border-top: 0px solid #bbbbbb;}");
     setWindowFlags(Qt::FramelessWindowHint);
     ui->groupBox->setStyleSheet("QGroupBox{border:none;}");//设置QGroupBox边框不可见
     ui->groupBox_2->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_3->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_4->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_5->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_6->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_7->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_8->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_9->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_10->setStyleSheet("QGroupBox{border:none;}");
     ui->groupBox_11->setStyleSheet("QGroupBox{border:none;}");
   /*  ui->label_54->setStyleSheet(QString("background:transparent;font-family:\"Mircsoft Yahei\";"
                                            "font-size:15px; color:#ffffFF; font-weight:bold;"));
     ui->label_55->setStyleSheet(QString("background:transparent;font-family:\"Mircsoft Yahei\";"
                                            "font-size:15px; color:#ffffFF; font-weight:bold;"));
     ui->label_56->setStyleSheet(QString("background:transparent;font-family:\"Mircsoft Yahei\";"
                                            "font-size:15px; color:#ffffFF; font-weight:bold;"));
     ui->label_57->setStyleSheet(QString("background:transparent;font-family:\"Mircsoft Yahei\";"
                                            "font-size:15px; color:#ffffFF; font-weight:bold;"));
     ui->label_58->setStyleSheet(QString("background:transparent;font-family:\"Mircsoft Yahei\";"
                                            "font-size:15px; color:#ffffFF; font-weight:bold;"));
                                            */
     QProcess *p = new QProcess;
     p->start(QString("\"%1/%2.exe\"").arg(qApp->applicationDirPath()).arg("livetool"));
    // ui->frame_3->setVisible(false);

   setStyleSheet("MainWindow{border-image:url(:/image/back.png);}");

   ui->frame_3->setStyleSheet("#frame_3{background:url(:/image/realback.png);}");//#frame_3设置后子窗口不继承
   ui->frame_4->setStyleSheet("#frame_4{border-image:url(:/image/left.png);}");//#frame_4设置后子窗口不继承
   ui->frame_16->setStyleSheet("#frame_16{border-image:url(:/image/left.png);}");//#frame_4设置后子窗口不继承
    ui->frame_6->setStyleSheet("#frame_6{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_7->setStyleSheet("#frame_7{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_8->setStyleSheet("#frame_8{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_9->setStyleSheet("#frame_9{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_10->setStyleSheet("#frame_10{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_11->setStyleSheet("#frame_11{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_12->setStyleSheet("#frame_12{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_13->setStyleSheet("#frame_13{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_14->setStyleSheet("#frame_14{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
    ui->frame_15->setStyleSheet("#frame_15{border-image:url(:/image/right.png);}");//#frame_4设置后子窗口不继承
  /* ui->widgetPanel_3->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #96c0ee,stop:1 #6a9bdf)");//
  // ui->widgetPanel_3->setFixedHeight(108);//设置高度
   ui->widgetPanel_2->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #4e86dc,stop:1 #5790e1)");//设置背景渐变色
   ui->widgetPanel_8->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #457dd7,stop:1 #4c84db)");//设置背景渐变色
   ui->widgetPanel_9->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #5791e1,stop:1 #5f99e5)");//设置背景渐变色
   ui->widgetPanel_4->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #96c0ee,stop:1 #6a9bdf)");//
   ui->widgetPanel_5->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #96c0ee,stop:1 #6a9bdf)");//
   ui->widgetPanel_6->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #96c0ee,stop:1 #6a9bdf)");//
   ui->widgetPanel_7->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #96c0ee,stop:1 #6a9bdf)");//
   ui->widgetPanel->setStyleSheet("background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #487ed8,stop:1 #5f99e5)");//设置背景渐变色
   */
    ui->widgetPanel_2->setStyleSheet("background:transparent;");//
    ui->widgetPanel_8->setStyleSheet("background:transparent;");//
    ui->widgetPanel_9->setStyleSheet("background:transparent;");//
   ui->widgetPanel_13->setStyleSheet("background:transparent;");//
   ui->widgetPanel_4->setStyleSheet("background:transparent;");//
   ui->widgetPanel_5->setStyleSheet("background:transparent;");//
   ui->widgetPanel_6->setStyleSheet("background:transparent;");//
   ui->widgetPanel_7->setStyleSheet("background:transparent;");//
   ui->widgetPanel->setStyleSheet("background:transparent;");//设置背景透明

  // ui->widgetPanel_2->setStyleSheet("#widgetPanel_2{border-image:url(:/image/real.png);}");//设置背景渐变色
   //ui->listView_2->setr
   ui->horizontalLayout_10->setMargin(0);//设置自动布局控件间边距
  // ui->horizontalLayout_10->setSpacing(20);//设置布局控件的间距
   ui->verticalLayout_3->setSpacing(5);

  histroydatatypestr="小时数据";
  logtypestr="系统日志";
  initOtherfactor();
  ui->pushButton_5->hide();
  insertsearchCmd=false;
  //delete splash;
  ui->btnHelp->hide();

}
void MainWindow::initbutton()
{
//设置背景色为画刷
QFont font;
font.setPixelSize(15);
font.setBold(true);
/*
QLinearGradient normalBgBrush(0, 0, 0, ui->navButton1->height());
normalBgBrush.setColorAt(0.0, QColor("#3985BF"));
normalBgBrush.setColorAt(0.5, QColor("#2972A9"));
normalBgBrush.setColorAt(1.0, QColor("#1C6496"));

QLinearGradient hoverBgBrush(0, 0, 0, ui->navButton1->height());
hoverBgBrush.setColorAt(0.0, QColor("#4897D1"));
hoverBgBrush.setColorAt(0.5, QColor("#3283BC"));
hoverBgBrush.setColorAt(1.0, QColor("#3088C3"));
// QColor normalBgColor = QColor("#E6393D");
//QColor hoverBgColor = QColor("#EE0000");
//QColor checkBgColor = QColor("#A40001");
QColor normalTextColor = QColor("#FFFFFF");
QColor hoverTextColor = QColor("#FFFFFF");
QColor checkTextColor = QColor("#FFFFFF");
*/
/*mainbtns << ui->navButton1 << ui->navButton2 << ui->navButton3 << ui->navButton5 ;
for (int i = 0; i < mainbtns.count(); i++) {
    mainbtns.at(i)->setFont(font);
    mainbtns.at(i)->setPaddingLeft(0);
    mainbtns.at(i)->setLineSpace(0);
    mainbtns.at(i)->setShowTriangle(true);
    mainbtns.at(i)->setTextAlign(NavButton::TextAlign_Center);
    mainbtns.at(i)->setTrianglePosition(NavButton::TrianglePosition_Bottom);
    mainbtns.at(i)->setLinePosition(NavButton::LinePosition_Top);

    mainbtns.at(i)->setNormalTextColor(normalTextColor);
    mainbtns.at(i)->setHoverTextColor(hoverTextColor);
    mainbtns.at(i)->setCheckTextColor(checkTextColor);

    mainbtns.at(i)->setNormalBgBrush(normalBgBrush);
    mainbtns.at(i)->setHoverBgBrush(hoverBgBrush);
    mainbtns.at(i)->setCheckBgBrush(hoverBgBrush);
    connect(mainbtns.at(i), SIGNAL(clicked(bool)), this, SLOT(mainClick()));

}
*/

//设置顶部导航按钮
QSize icoSize(32, 32);
int icoWidth = 85;
//QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
mainbtns << ui->btnMain << ui->btnConfig << ui->btnData << ui->btnHelp<<ui->btnMain_2;
foreach (QToolButton *btn, mainbtns) {
    btn->setIconSize(icoSize);
    btn->setMinimumWidth(icoWidth);
    btn->setCheckable(true);
   // btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置图标在左边
     connect(btn, SIGNAL(clicked(bool)), this, SLOT(mainClick()));
}
ui->btnMain_2->setChecked(false);
/*
databtns << ui->navButtondata_1<< ui->navButtondata_2 << ui->navButtondata_3 << ui->navButtondata_4;
for (int i = 0; i < databtns.count(); i++) {
    databtns.at(i)->setPaddingLeft(35);
    databtns.at(i)->setLineSpace(0);
    databtns.at(i)->setLineWidth(8);
    databtns.at(i)->setLineColor(QColor(255, 107, 107));
    databtns.at(i)->setShowTriangle(true);

    databtns.at(i)->setShowIcon(true);
    databtns.at(i)->setIconSpace(10);
    databtns.at(i)->setIconSize(QSize(22, 22));

    databtns.at(i)->setNormalBgColor(normalBgColor);
    databtns.at(i)->setHoverBgColor(hoverBgColor);
    databtns.at(i)->setCheckBgColor(checkBgColor);
    databtns.at(i)->setNormalTextColor(normalTextColor);
    databtns.at(i)->setHoverTextColor(hoverTextColor);
    databtns.at(i)->setCheckTextColor(checkTextColor);

    connect(databtns.at(i), SIGNAL(clicked(bool)), this, SLOT(dataClick()));

}
*/
/*
systembtns << ui->navButtondata_5<< ui->navButtondata_7 << ui->navButtondata_6 ;
for (int i = 0; i < systembtns.count(); i++)
{
    systembtns.at(i)->setPaddingLeft(35);
    systembtns.at(i)->setLineSpace(0);
    systembtns.at(i)->setLineWidth(8);
    systembtns.at(i)->setLineColor(QColor(255, 107, 107));
    systembtns.at(i)->setShowTriangle(true);

    systembtns.at(i)->setShowIcon(true);
    systembtns.at(i)->setIconSpace(10);
    systembtns.at(i)->setIconSize(QSize(22, 22));

    systembtns.at(i)->setNormalBgColor(normalBgColor);
    systembtns.at(i)->setHoverBgColor(hoverBgColor);
    systembtns.at(i)->setCheckBgColor(checkBgColor);

    systembtns.at(i)->setNormalTextColor(normalTextColor);
    systembtns.at(i)->setHoverTextColor(hoverTextColor);
    systembtns.at(i)->setCheckTextColor(checkTextColor);

    connect(systembtns.at(i), SIGNAL(clicked(bool)), this, SLOT(systemClick()));
}
*/
ui->dateEdit->setCalendarPopup(true);
}
void MainWindow::mainClick()
{
    QToolButton *btn = (QToolButton *)sender();
    static bool first=true;
    for (int i = 0; i < mainbtns.count(); i++) {
        mainbtns.at(i)->setChecked(mainbtns.at(i) == btn);
        if(mainbtns.at(i) == btn)
        {
            if(i==4)
            {
                ui->tabWidget->setCurrentIndex(5);
                ui->tabWidget->setTabEnabled(5, true);
                if(first==true)
                {
                    first=false;
                   initmulUI();
                }
            }
            else if(i==5)
            {
                ui->tabWidget->setCurrentIndex(4);
                ui->tabWidget->setTabEnabled(4, true);
            }
            else if(i==3)
            {
                if(loginType=="管理员")
                {
                 ui->tabWidget->setCurrentIndex(i);
                 ui->tabWidget->setTabEnabled(i, true);
                }
                else if(loginType.isEmpty())
                {
                     if(helpclass.ShowMessageBox("你未登录系统，请问是否登录系统?"))
                     {
                         loginDlg *dlg=new loginDlg();
                         dlg->exec();
                         if(!loginName.isEmpty())
                         {
                                 ui->pushButton->setStyleSheet(tr("background-image: url(:/image/注销.png);"));
                         }
                     }
                     break;
                }
                else
                {
                    helpclass.ShowoneMessageBox("你的用户权限不够，请用管理员账号登录");
                }
            }
            else
            {
                ui->tabWidget->setCurrentIndex(i);
                ui->tabWidget->setTabEnabled(i, true);
            }
           if(i==5)
                 initvideo(true);
           else
                 initvideo(false);
           mainbtns.at(i)->setChecked(true);
        }
        else
        {
            mainbtns.at(i)->setChecked(false);
        }
        }

}
/*
void MainWindow::dataClick()
{
    NavButton *btn = (NavButton *)sender();
    for (int i = 0; i < databtns.count(); i++) {
        databtns.at(i)->setChecked(databtns.at(i) == btn);
        if(databtns.at(i) == btn)
        {
           ui->tabWidget_2->setCurrentIndex(i);
           ui->tabWidget_2->setTabEnabled(i, true);

        }
        }

}
*/
void MainWindow::systemClick()
{
    NavButton *btn = (NavButton *)sender();
    for (int i = 0; i < systembtns.count(); i++) {
        systembtns.at(i)->setChecked(systembtns.at(i) == btn);
        if(systembtns.at(i) == btn)
        {
           ui->tabWidget_System->setCurrentIndex(i);
           ui->tabWidget_System->setTabEnabled(i, true);

        }
        }

}
void MainWindow::initStyle()
{
    //加载样式表
  QFile file(":/qss/lightblue.css"); //flatwhite

     if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
/**数据控件初始化
 * @brief MainWindow::init
 */
void MainWindow::init()
{
    //  this->showMaximized();
  //  initInstrumentQueryModel();
  //  initFactorQueryModel();
  //  initCtrlCmdQueryModel();
  //  initSearchCmdQueryModel();
 //   initCommunicationQueryModel();
 //    initinstrumentmodeQueryModel();
  //  initNetWorkQueryModel();
 //   initFactornetIDQueryModel();
  //  initUserQueryModel();
    initlogModel();
    initmaintainQueryModel();
    initalarmquerymodel();

     //settableparame(instrumentquerymodel,ui->tableView);
    // settableparame(factorquerymodel,ui->tableView_3);
     //settableparame(CtrlCmdquerymodel,ui->tableView_2);
    // settableparame(searchCmdquerymodel,ui->tableView_4);

     //settableparame(communicationquerymodel,ui->tableView_5);
    //  settableparame(instrumentmodemodel,ui->tableView_9);
    // settableparame(networkquerymodel,ui->tableView_7);
   //  settableparame(factornetIdquerymodel,ui->tableView_6);
   //  settableparame(userquerymodel,ui->tableView_15);
     settableparame(logquerymodel,ui->tableView_17);
     settableparame(maintainquerymodel,ui->tableView_18);
      settableparame(alarmquerymodel,ui->tableView_10);//设置列表属性

    initInstrumentComboBox();
    initFactorComboBox();
    initCtrlCmdComboBox();
    initSearchCmdComboBox();
    initCommunicationComboBox();
 //   initNetWorkComboBox();
    initFactornetIDComboBox();
    initNetWorkComboBox();
    initHistoryComboBox();

    initUserCombox();
    initlogCombox();
    initPanelWidget();
    initsystemsetPanelWidget();

    historyinitdraw();

    /* 历史数据 */
     historyquerymodel = new QSqlQueryModel;
     initHistoryModel();
     settableparame(historyquerymodel,ui->tableView_8);
     realtimequerymodel=new  QSqlQueryModel ;
     pDbControl=new  DbControl;
    // timeID=startTimer(1000);// 定时器
     timedrawId=startTimer(1000);// 定时器
     //inittableViewTimeId=startTimer(1000);// 定时器
     instrumentTimeId=startTimer(250);// 定时器
     sqlTimeIdrefresh=startTimer(3600000);
     initdraw();
    // ui->tableView_9->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    // ui->tableView_9->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    // ui->tableView->horizontalHeader()->setStretchLastSection(true);
    // ui->tableView_7->horizontalHeader()->setStretchLastSection(true);
 //    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    // ui->tableView_3->horizontalHeader()->setStretchLastSection(true);
   //  ui->tableView_4->horizontalHeader()->setStretchLastSection(true);
   //  ui->tableView_5->horizontalHeader()->setStretchLastSection(true);
    // ui->tableView_6->horizontalHeader()->setStretchLastSection(true);
     ui->tableView_8->horizontalHeader()->setStretchLastSection(true);
    // ui->tableView_9->horizontalHeader()->setStretchLastSection(true);

     //以下是视觉方面的效果，不加也没影响
     //隔行变色
    // ui->tableView_9->setAlternatingRowColors(true);
    initnetwork();

    QSqlQuery query;
    QString sqlstr;
    query.exec("SET NAMES UTF8");
    sqlstr="select * from stationinfo";
    query.exec(sqlstr);
    if(query.next())
    {
        namestr=query.value("station_name").toString();
        Idstr=query.value("station_code").toString();
    }
    tepclientindex=0;
//    ui->tableView_9->setVisible(false);//隐藏控件
    // ui->pushButton->setVisible(false);//隐藏控件
  //  ui->pushButton_10->setVisible(false);
   // ui->pushButton_12->setVisible(false);
     ui->histroyPlot->setVisible(false);
     ui->label_69->setPixmap(QPixmap(":/image/logo.png"));
     ui->label_69->setVisible(false);
     ui->pushButton->setStyleSheet(tr("background-image: url(:/image/Landing.png);"));
     ui->pushButton_3->setStyleSheet(tr("background-image: url(:/image/Exit.png);"));
    // ui->tabWidget->setDocumentMode(false);
    // ui->tabWidget_2->setDocumentMode(false);
     //启动守护程序服务类
     AppLive::Instance()->start(6666);
     ring.airConditionerOpen=false;
}
/**初始化网络发送
 * @brief MainWindow::initnetwork
 */
void MainWindow::initnetwork()
{
    QSqlQuery query;
    QString sqlstr;
    query.exec("SET NAMES UTF8");
    sqlstr="select * from networkset where used='是'";
    query.exec(sqlstr);
    tepclientindex=0;
    while(query.next())
    {
        Tcpclient *tcpclient=new Tcpclient;
        networkinfo m_networkinfo;
        m_networkinfo.id=query.value("id").toString();
        m_networkinfo.ip=query.value("ip").toString();
        m_networkinfo.minutedatetime=query.value("minutedatetime").toString();
        m_networkinfo.mn=query.value("mn").toString();
        m_networkinfo.password=query.value("password").toString();
        m_networkinfo.port=query.value("port").toInt();
        m_networkinfo.protocalId=query.value("protocol").toString();
        m_networkinfo.requestFlag=query.value("requestFlag").toInt();
        m_networkinfo.sendFlag=query.value("sendFlag").toInt();
        m_networkinfo.st=query.value("st").toString();
        m_networkinfo.crctype=query.value("crc").toInt();
        tcpclient->initdata(m_networkinfo);
        if(tepclientindex<MAX_NETWORK_NUM)
           pTcpclient[tepclientindex++]=tcpclient;
    }

}
/**
  定时器
 * @brief MainWindow::timerEvent
 * @param t
 */
void MainWindow::timerEvent(QTimerEvent *t)
{
//if(t->timerId()==timeID)
//{

    showinfo();
     showOtherfactor();
//}
     static bool first=true;
 if(t->timerId()==timedrawId)
{
   // realtimeDataSlot();
    showRealData();

    if(first==true)
    {
         first=false;
         this->showMaximized();
    }
    if(ring.airConditionerOpen==false)//空调是否开启
    {
        if(pinstrumentManage->getFactorinfo("环境温度").data>25)//判断环境温度
            {
                startinstrumentCmd("空调","制令");
                ring.airConditionerOpen=true;
           }
        else
        {
            if(pinstrumentManage->getFactorinfo("温度").data<10&&pinstrumentManage->getFactorinfo("温度").name=="温度")
            {
                startinstrumentCmd("空调","关闭");
                ring.airConditionerOpen=false;
            }
        }
    }
}
else if(t->timerId()==sqlTimeIdrefresh)//一个小时刷新一次数据库
{
    communicationquerymodel->setQuery("select a.id, name ,communicationType,label ,autoReadType from instrument a,combo_box b where a.checked='是' and b.type='com_id' and b.`value`=a.comID");
}
else if(t->timerId()==instrumentTimeId)//定时控制仪器，这里主要是PLC开启门禁
{
    QString instrumentname,cmd;
    QString status=helpclass.getiniData("setting.ini","instrumentctrl/type");//得到被控仪器的操作状态
    if(status=="open")
    {
        helpclass.setiniData("setting.ini","instrumentctrl/type","close");
        instrumentname=helpclass.getiniData("setting.ini","instrumentctrl/instrumentName");
        cmd=helpclass.getiniData("setting.ini","instrumentctrl/instrumentcmd");
        startinstrumentCmd(instrumentname,cmd);

    }

}


}
/**显示站点信息
 * @brief MainWindow::showinfo
 */
void MainWindow::showinfo()
{
    QString timestr;
    timestr="时间：        "+helpclass.currenttimetostrinterface();
  /*  ui->label_55->setText(timestr);
    ui->label_54->setText("站点名称：        "+namestr);
    ui->label_56->setText("站点编码：        "+Idstr);
    ui->label_57->setText("用户名 ：        "+MainWindow::loginName);
    ui->label_58->setText("用户类型：        "+MainWindow::loginType);
*/
    QListIterator<Info *> i(infodlg);//
    QStringList titlelist;
    titlelist.append("站点名称： "+namestr);
    titlelist.append("站点编码： "+Idstr);
   while(i.hasNext())
   {
      Info *from= i.next();
      from->settitle(titlelist);
   }

   QListIterator<Othordlg *> item(othordlg);//
   QStringList title;
   title.append("用户名： "+MainWindow::loginName);
   title.append("用户类型： "+MainWindow::loginType);
  while(item.hasNext())
  {
     Othordlg *from= item.next();
     from->settitle(title);
  }


}

/*仪器列表初始化*/
void MainWindow::initInstrumentQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
     // QSqlQueryModel *querymodel;
      namestr<<"仪器名" << "类型" << "本站点仪器"<< "波特率" << "校验"<<"停止位" << "端口号" << "IP" << "仪器自动发送数据";

     instrumentquerymodel->setQuery("select name,type,checked,baudrate,parity,stopBit,port,ip,autoReadType from instrument");//这里直接设置SQL语句，忽略最后一个参数
     for(int i=0;i<namestr.size();i++)
     {
        instrumentquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
     }
    // ui->tableView->setModel(instrumentquerymodel);

    /* int row_count = querymodel->rowCount();
     setTableView(ui->tableView, row_count);
     ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
     int columncount=querymodel->columnCount();
      settableColumnWidth(columncount,ui->tableView);*/
   //  static bool first=true;
   //  if(first==true)
      //  settableparame(instrumentquerymodel,ui->tableView);
    // else
      //   first=false;
}
/**设置列表的属性
 * @brief MainWindow::settableparame
 * @param querymodel 数据库查询模板
 * @param tableView  列表控件
 */
void  MainWindow::settableparame(QSqlQueryModel *querymodel,QTableView *tableView)
{
    int row_count = querymodel->rowCount();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式

    tableView->setModel(querymodel);
    setTableView(tableView, row_count);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    int columncount=querymodel->columnCount();
    // ui->tableView_3->horizontalHeader()->
    // setSectionResizeMode(QHeaderView::ResizeToContents);自动适应大小，设置后不能拉伸
    if(columncount>0)
       settableColumnWidth(columncount,tableView);
}
/*用户列表初始化*/
void MainWindow::initUserQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
     // QSqlQueryModel *querymodel;
      namestr<<"id"<<"用户名" << "用户类型" << "描述" << "创建时间"<<"修改时间" << "最近登录时间";
   //  userquerymodel = new QSqlQueryModel;
     userquerymodel->setQuery("select id, user,type,description,add_time,update_time,login_time from cfg_user");//这里直接设置SQL语句，忽略最后一个参数
     for(int i=0;i<namestr.size();i++)
     {
         userquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
     }
    // ui->tableView_15->setModel(userquerymodel);

}
/**维修日志初始化
  */
void MainWindow::initmaintainQueryModel()
{
QStringList namestr;
QString sqlstr;

sqlstr="select dataTime,personnel,systemLog from maintain ";
maintainquerymodel->setQuery(sqlstr);
 namestr<<"时间"<<"操作人员"<<"维修事项";
for(int i=0;i<namestr.size();i++)
{
  maintainquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
}

ui->tableView_18->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
ui->tableView_18->setModel( maintainquerymodel);
}

/**报警日志初始化
  */
void MainWindow::initalarmquerymodel()
{
QStringList namestr;
QString sqlstr;
sqlstr="select * from alarm  order by data_Date desc  LIMIT 10";
alarmquerymodel->setQuery(sqlstr);
 namestr<<"时间"<<"描述"<<"数值"<<"单位"<<"下限"<<"上限"<<"类型";
for(int i=0;i<namestr.size();i++)
{
     alarmquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
}

ui->tableView_10->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
ui->tableView_10->setModel(alarmquerymodel);
}
void MainWindow::initInstrumentComboBox()
{/* 下来框初始化 */
    QStringList DataStr;
    DataStr<<"pM2.5"<<"CO"<<"NO"<<"NO2"<<"SO2"<<"臭氧"<<"五参数"<<"动环信息"<<"站房信息"<<"采样信息"<<"仪器供电"<<"标气压力"<<"其他供电"<<"多参数";
    ui->comboBox->addItems(DataStr);
    DataStr.clear();
    DataStr<<"600"<<"1200"<<"2400"<<"4800"<<"9600"<<"14400"<<"19200"<<"38400"<<"56000"<<"57600"<<"115200";
    ui->comboBox_2->addItems(DataStr);
    DataStr.clear();
    DataStr<<"无校验"<<"奇校验"<<"偶校验"<<"标记校验";
    ui->comboBox_3->addItems(DataStr);
    DataStr.clear();
    DataStr<<"1"<<"1.5"<<"2";
    ui->comboBox_4->addItems(DataStr);
    DataStr.clear();
    DataStr<<"是"<<"否";
    ui->comboBox_21->addItems(DataStr);
    DataStr.clear();
    DataStr<<"正常"<<"零校"<<"满校";
    ui->comboBox_20->addItems(DataStr);
}


/*因子列表初始化*/
void MainWindow::initFactorQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
     // QSqlQueryModel *querymodel;
      namestr<<"因子名" << "因子值下限" << "因子值上限" << "单位"<<"小数位数" << "是否显示" << "单位转化系数" << "是否上传";
   //  querymodel = new QSqlQueryModel;
     //querymodel->setQuery("select name,min,max,unit,dataNum,type,modulus,need_upload from factor");//这里直接设置SQL语句，忽略最后一个参数
     factorquerymodel->setQuery("select name,min,max,label,dataNum,a.type,modulus,need_upload from factor a, combo_box b where a.unit=b.value and b.type='unit'");
     for(int i=0;i<namestr.size();i++)
     {
         factorquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
     }
  //   ui->tableView_3->setModel(factorquerymodel);


}
/**设置列表框的列宽度一致
 * @brief MainWindow::settableColumnWidth
 * @param columncount
 * @param tableView
 */
void MainWindow::settableColumnWidth(int columncount,QTableView *tableView)
{
   /* int widths=tableView->width()/columncount;
   for(int i=0;i<columncount;i++)
    {
         tableView->setColumnWidth(i,widths);
     }*///设置每列的宽度
  tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽度平均并充满整个控件
}
/** 因子下来框初始化
 * @brief MainWindow::initFactorComboBox
 */
void MainWindow::initFactorComboBox()
{/* 下来框初始化 */
    QString sqlstr="select label,value from  combo_box where type='unit' ";
    initcomboBox(ui->comboBox_5,sqlstr,2);

    QStringList DataNum;
    DataNum<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
    ui->comboBox_6->addItems(DataNum);
}


void MainWindow::initcomboBox(QComboBox *comboBox,QString sqlstr)
{
   QSqlQueryModel *querymodelComboBox;
   querymodelComboBox=new  QSqlQueryModel;
   querymodelComboBox->setQuery(sqlstr);
   comboBox->setModel(querymodelComboBox);
}
void MainWindow:: initUserCombox()
{
    QStringList DataNum;
    DataNum<<"管理员"<<"运维人员"<<"参观用户";
    ui->comboBox_19->addItems(DataNum);

}
void MainWindow::initlogCombox()
{
   /* QStringList comboxlist;
    comboxlist<<"网络日志"<<"系统日志"<<"操作日志";
    ui->comboBox_23->addItems(comboxlist);*/
}
void MainWindow::initcomboBox(QComboBox *comboBox,QString sqlstr,int num)
{
    QSqlQuery query;
    ComboBoxdata  comboBoxdata;
    comboBox->clear();
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    while (query.next()) {
          comboBoxdata.name=query.value(0).toString();
          comboBoxdata.index=query.value(1).toInt();
          QVariant var;
          var=QVariant::fromValue(comboBoxdata);
          comboBox->addItem(comboBoxdata.name, var);
    }

}

/*控制命令列表初始化*/
void MainWindow::initCtrlCmdQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
   //   QSqlQueryModel *querymodel;
      namestr<<"命令id"<<"仪器名" << "命令名称" << "命令";
    //  querymodel = new QSqlQueryModel;
      CtrlCmdquerymodel->setQuery("select a.id, name,cmdName,cmd from instrumentcmd a ,instrument b where b.id=a.instrumentId");//这里直接设置SQL语句，忽略最后一个参数
      for(int i=0;i<namestr.size();i++)
      {
         CtrlCmdquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
      //ui->tableView_2->setModel(CtrlCmdquerymodel);


}
/**
 * @brief MainWindow::initCtrlCmdComboBox
 */
void MainWindow::initCtrlCmdComboBox()
{/* 控制命令仪器名下拉框 */
    QString sqlstr="select  name,id from instrument";
  //  initcomboBox(ui->comboBox_7,sqlstr);
    initcomboBox(ui->comboBox_7,sqlstr,2);
    QStringList DataStr;
    DataStr<<"校零"<<"启动"<<"停止";
    ui->comboBox_8->addItems(DataStr);
}

/*查询命令列表初始化*/
void MainWindow::initSearchCmdQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
     // QSqlQueryModel *querymodel;
      namestr<<"命令ID"<<"仪器名" << "因子" <<"数据起始位" << "数据位数" << "查询命令"<< "计算公式";
    //  querymodel = new QSqlQueryModel;
      searchCmdquerymodel->setQuery("select a.id, b.`name` ,c.name,addr,num, cmd ,label from instrumentsearch a ,instrument b ,factor c ,combo_box d where a.instrumentId=b.id and c.id=a.factorId and d.type='formula_type' and d.`value`=a.formulaId");//这里直接设置SQL语句，忽略最后一个参数
      for(int i=0;i<namestr.size();i++)
      {
         searchCmdquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
     // ui->tableView_4->setModel(searchCmdquerymodel);

}
/**初始化查询命令下来框
 * @brief MainWindow::initSearchCmdComboBox
 */
void MainWindow::initSearchCmdComboBox()
{
/* 查询命令 下来菜单初始化 */
       QString sqlstr="select name ,id from instrument";
       initcomboBox(ui->comboBox_9,sqlstr,2);
       sqlstr="select name,id from factor";
       initcomboBox(ui->comboBox_10,sqlstr,2);
       sqlstr="select label ,value from combo_box where type='formula_type'";
       initcomboBox(ui->comboBox_11,sqlstr,2);
}
/*串口设置列表初始化*/
void MainWindow::initCommunicationQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
    //  QSqlQueryModel *querymodel;
      namestr<<"仪器id"<<"仪器名" << "通讯接口" << "串口号"<<"仪器自动发送数据";
     // querymodel = new QSqlQueryModel;
      communicationquerymodel->setQuery("select a.id, name ,communicationType,label ,autoReadType from instrument a,combo_box b where a.checked='是' and b.type='com_id' and b.`value`=a.comID");
      for(int i=0;i<namestr.size();i++)
      {
         communicationquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
      //ui->tableView_5->setModel(communicationquerymodel);


}

/*仪器模式列表初始化*/
void MainWindow::initinstrumentmodeQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
    //  QSqlQueryModel *querymodel;
      namestr<<"仪器id"<<"仪器名" <<"仪器模式";
     // querymodel = new QSqlQueryModel;
      instrumentmodemodel->setQuery("select id, name ,mode from instrument  where checked='是'");
      for(int i=0;i<namestr.size();i++)
      {
        instrumentmodemodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
    //  ui->tableView_9->setModel(instrumentmodemodel);


}
/**串口设置列表下拉框
 * @brief MainWindow::initCommunicationComboBox
 */
void MainWindow::initCommunicationComboBox()
{
    /* 串口设置列表 */
               QString sqlstr="select label ,value from combo_box where type='port_type'";
               initcomboBox(ui->comboBox_12,sqlstr,2);
               sqlstr="select label,value from combo_box where type='com_id'";
               initcomboBox(ui->comboBox_13,sqlstr,2);
}
/*网络因子编码列表初始化*/
void MainWindow::initFactornetIDQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
      QStringList namestr;
      //QSqlQueryModel *querymodel;
      namestr<<"id"<<"协议名" << "因子名" << "因子编码";
      //factornetIdquerymodel = new QSqlQueryModel;
      factornetIdquerymodel->setQuery("select a.id, label ,b.name,polId from netpolid a, factor b,combo_box c where a.factorId=b.id and c.type='protocol' and c.`value`=a.protocalId");
      for(int i=0;i<namestr.size();i++)
      {
         factornetIdquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
      //ui->tableView_6->setModel(factornetIdquerymodel);


}
void MainWindow::initFactornetIDComboBox()
{
    /* 网络因子编码下拉框初始化*/
               QString sqlstr="select name,id from factor";
               initcomboBox(ui->comboBox_15,sqlstr,2);
             //  sqlstr="select label,value from networkset a,combo_box b where a.protocol=b.value and b.type='protocol' ";
             //  initcomboBox(ui->comboBox_14,sqlstr,2);
               sqlstr="select label,value from combo_box where type='protocol' ";
                initcomboBox(ui->comboBox_14,sqlstr,2);
}

/*网络通讯协议列表初始化*/
void MainWindow::initNetWorkQueryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
    /*  QStringList namestr;
     // QSqlQueryModel *querymodel;
      namestr<<"id" <<"协议名称" << "IP"<<"端口号" << "MN码"<<"密码"<<"ST" << "发送标记" << "回复标记"<<"是否启用";
    //  querymodel = new QSqlQueryModel;
      networkquerymodel->setQuery("select a.id,label,ip,port,mn,password,st, sendFlag,requestFlag,used from networkset a ,combo_box b where b.type='protocol' and a.protocol=b.value");//这里直接设置SQL语句，忽略最后一个参数
      for(int i=0;i<namestr.size();i++)
      {
         networkquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
      }
       ui->tableView_7->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式

      ui->tableView_7->setModel(networkquerymodel);
*/

}
/**网络协议下拉列表
 * @brief MainWindow::initNetWorkComboBox
 */
void MainWindow::initNetWorkComboBox()
{
              QString sqlstr="select label,value from combo_box where type='protocol' ";
               initcomboBox(ui->comboBox_17,sqlstr,2);
}

/*历史数据列表初始化*/
void MainWindow::initHistoryModel()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */

      QStringList factorList;
      QString sqlstr;

      factorList=dbinstrumentclass.getSelectFactorList();
      sqlstr=dbinstrumentclass.getHistorySqlstr( factorList,"minutefactor");


      historyquerymodel->setQuery(sqlstr);//这里直接设置SQL语句，忽略最后一个参数
      historyquerymodel->setHeaderData(0, Qt::Horizontal, "时间");


}
/**
 * @brief MainWindow::initlogModel
 */
void MainWindow::initlogModel()
{
      //QSqlQueryModel *querymodel;
       //querymodel = new QSqlQueryModel;
       QStringList namestr;
       namestr<<"时间"<<"类型"<<"事件";
       logquerymodel->setQuery("select dataTime,type,systemLog  from log");
   for(int i=0;i<namestr.size();i++)
   {
      logquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
   }
    ui->tableView_17->setModel(logquerymodel);

}
void  MainWindow::initHistoryComboBox()
{
    QString sqlstr;
    sqlstr="select label ,value from combo_box where type='history_type'";
    //initcomboBox(ui->comboBox_16,sqlstr,2);
}



/**
  得到选中一行的数据
 * @brief MainWindow::getTableViewRowData
 * @param TableView  列表控件
 * columnCount 控件列数
 * @return
 */
QStringList MainWindow::getTableViewRowData(QTableView *TableView,int columnCount)
{
    QString tempstr;
    QStringList datalist;
    int row=TableView->currentIndex().row();
        QAbstractItemModel *model =  TableView->model ();
    for(int i=0;i<columnCount;i++)
    {

        QModelIndex index = model->index(row,i);
       QVariant  data = model->data(index);
       tempstr=data.toString();
       datalist.insert(i,tempstr);
    }
  return datalist;
}

void MainWindow::setTableView(QTableView *TableView,int row_count)
{
TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
//以下是视觉方面的效果，不加也没影响
//隔行变色
TableView->setAlternatingRowColors(true);

//设置行高
for(int i =0; i < row_count; i++)
{
    TableView->setRowHeight(i, 28);
}
}
/**去掉属性显示
 * @brief MainWindow::SetTabEnable
 */
void MainWindow::SetTabEnable()
{

   //影响子属性框
     ui->tabWidget->tabBar()->hide();//不影响子属性框
     ui->tabWidget_System->tabBar()->hide();//不影响子属性框
     ui->tabWidget_2->tabBar()->hide();//不影响子属性框
     ui->tabWidget_4->tabBar()->hide();//不显示属性页，不影响子属性框
     ui->tabWidget_5->tabBar()->hide();//不显示属性页，不影响子属性框
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pinstrumentManage;
}


/**因子列表单击事件
 * @brief MainWindow::on_tableView_3_clicked
 * @param index
 */
void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
 /* QStringList listdata= getTableViewRowData(ui->tableView_3,8) ;
  ui->lineEdit_4->setText(listdata.at(0));
  ui->lineEdit_5->setText(listdata.at(1));
  ui->lineEdit_6->setText(listdata.at(2));
  ui->lineEdit_7->setText(listdata.at(6));

  int comboBoxindex=ui->comboBox_5->findText(listdata.at(3));
  ui->comboBox_5->setCurrentIndex(comboBoxindex);
  comboBoxindex=ui->comboBox_6->findText(listdata.at(4));
  ui->comboBox_6->setCurrentIndex(comboBoxindex);
    if(listdata.at(5)=="显示")
    {
       ui->checkBox->setChecked(true);
    }
    else
        ui->checkBox->setChecked(false);
    if(listdata.at(7)=="上传")
        ui->checkBox_2->setChecked(true);
    else
        ui->checkBox_2->setChecked(false);
     ui->pushButton_21->setText("修改");
     */
}
/**仪器列表点击事件
 * @brief MainWindow::on_tableView_clicked
 * @param index
 */
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
//"仪器名" << "类型" <<"本站仪器"<< "波特率" << "校验"<<"停止位" << "端口号" << "IP" << "仪器自动发送数据"
   /* QStringList listdata= getTableViewRowData(ui->tableView,9) ;
    ui->lineEdit->setText(listdata.at(0));
    ui->lineEdit_2->setText(listdata.at(6));
    ui->lineEdit_3->setText(listdata.at(5));
    int comboBoxindex=ui->comboBox->findText(listdata.at(1));
    ui->comboBox->setCurrentIndex(comboBoxindex);
     comboBoxindex=ui->comboBox_21->findText(listdata.at(2));
    ui->comboBox_21->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_2->findText(listdata.at(3));
    ui->comboBox_2->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_3->findText(listdata.at(4));
    ui->comboBox_3->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_4->findText(listdata.at(5));
    ui->comboBox_4->setCurrentIndex(comboBoxindex);
     ui->pushButton_18->setText("修改");*/
}
/**控制命令列表点击事件
 * @brief MainWindow::on_tableView_2_clicked
 * @param index
 */
void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    //仪器名" << "命令名称" << "命令
  /*  QStringList listdata= getTableViewRowData(ui->tableView_2,4) ;
      ui->lineEdit_8->setText(listdata.at(3));
       ui->lineEdit_29->setText(listdata.at(0));
    int comboBoxindex=ui->comboBox_7->findText(listdata.at(1));
    ui->comboBox_7->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_8->findText(listdata.at(2));
    ui->comboBox_8->setCurrentIndex(comboBoxindex);
      ui->pushButton_24->setText("修改");
      */
}
/** 查询命令列表点击事件
 * @brief MainWindow::on_tableView_4_clicked
 * @param index
 */
void MainWindow::on_tableView_4_clicked(const QModelIndex &index)
{
    //仪器名" << "因子" << "查询命令"<<"数据起始位" << "数据位数" << "计算公式
/*    QStringList listdata= getTableViewRowData(ui->tableView_4,7) ;
    ui->lineEdit_23->setText(listdata.at(0));
     ui->lineEdit_9->setText(listdata.at(3));
     ui->lineEdit_10->setText(listdata.at(4));
     ui->lineEdit_11->setText(listdata.at(5));
    int comboBoxindex=ui->comboBox_9->findText(listdata.at(1));
    ui->comboBox_9->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_10->findText(listdata.at(2));
    ui->comboBox_10->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_11->findText(listdata.at(6));
    ui->comboBox_11->setCurrentIndex(comboBoxindex);
    ui->pushButton_27->setText("修改");
    */
}
/**串口设置接口设置列表点击事件
 * @brief MainWindow::on_tableView_5_clicked
 * @param index
 */
void MainWindow::on_tableView_5_clicked(const QModelIndex &index)
{
    //仪器名" << "通讯接口" << "串口号"
  /*  QStringList listdata= getTableViewRowData(ui->tableView_5,5) ;

    int comboBoxindex=ui->comboBox_12->findText(listdata.at(2));
    ui->comboBox_12->setCurrentIndex(comboBoxindex);
    comboBoxindex=ui->comboBox_13->findText(listdata.at(3));
    ui->comboBox_13->setCurrentIndex(comboBoxindex);
    ui->lineEdit_20->setText(listdata.at(0));
    if(listdata.at(4)=="是")
    {
        ui->checkBox_3->setChecked(true);
    }
    else
        ui->checkBox_3->setChecked(false);
     ui->pushButton_28->setText("修改");
     */
}
/**网络协议列表点击事件
 * @brief MainWindow::on_tableView_7_clicked
 * @param index
 */
void MainWindow::on_tableView_7_clicked(const QModelIndex &index)
{
    //"协议名称" << "IP"<<"端口号" << "MN码"<<"密码"<<"ST" << "发送标记" << "回复标记"<<"是否启用";
   /*  QStringList listdata= getTableViewRowData(ui->tableView_7,10) ;
     ui->lineEdit_22->setText(listdata.at(0));
     int comboBoxindex=ui->comboBox_17->findText(listdata.at(1));
     ui->comboBox_17->setCurrentIndex(comboBoxindex);
     ui->lineEdit_13->setText(listdata.at(2));
     ui->lineEdit_14->setText(listdata.at(3));
     ui->lineEdit_15->setText(listdata.at(4));
     ui->lineEdit_16->setText(listdata.at(5));
     ui->lineEdit_17->setText(listdata.at(6));
     ui->lineEdit_18->setText(listdata.at(7));
     ui->lineEdit_19->setText(listdata.at(8));
       ui->pushButton_34->setText("修改");*/
}
/**网络因子编码列表点击事件
 * @brief MainWindow::on_tableView_6_clicked
 * @param index
 */
void MainWindow::on_tableView_6_clicked(const QModelIndex &index)
{
    //"协议名" << "因子名" << "因子编码";
  /*  QStringList listdata= getTableViewRowData(ui->tableView_6,4) ;
    int comboBoxindex=ui->comboBox_15->findText(listdata.at(2));
    ui->comboBox_15->setCurrentIndex(comboBoxindex);
    ui->lineEdit_12->setText(listdata.at(3));
    ui->lineEdit_21->setText(listdata.at(0));
    ui->pushButton_29->setText("修改");
    */
}

void MainWindow::initdraw()
{
/*
QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

QColor Color[MAX_DRAW]={QColor(40, 110, 255),QColor(40, 110, 0),QColor(40, 110, 100),QColor(110, 110, 255),QColor(110, 110, 0),QColor(40, 110, 110),QColor(110, 0, 255),QColor(110, 0, 100),QColor(20, 110, 255),QColor(200, 110, 255)};
timeTicker->setTimeFormat("%h:%m:%s");

// make left and bottom axes transfer their ranges to right and top axes:
connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));

for(int m=0;m<MAX_PLOT;m++)
    showtype[m]=false;
pCustomPlot[0]=ui->plot;
pCustomPlot[1]=ui->plot_2;
pCustomPlot[2]=ui->plot_3;
pCustomPlot[3]=ui->plot_4;
pCustomPlot[4]=ui->plot_5;
pCustomPlot[5]=ui->plot_6;
pCustomPlot[6]=ui->plot_7;
pCustomPlot[7]=ui->plot_8;
//int sun=1;
factorInfotype factorinfoMap;
 factorinfoMap=pinstrumentManage->getFactorinfo();
  QMapIterator<int,factorinfo> item(factorinfoMap);

  while(item.hasNext())
  {
      item.next();

    int  maxdata=item.value().maxdata;
     if(maxdata<=10&& plot[0]<MAX_DRAW-1)
     {
           pCustomPlot[0]->addGraph(); // blue line
           pCustomPlot[0]->graph(plot[0])->setPen(QPen(Color[plot[0]]));
           pCustomPlot[0]->yAxis->setRange(0, 10);
           pCustomPlot[0]->xAxis->setTicker(timeTicker);
           pCustomPlot[0]->legend->setVisible(true);//显示曲线名
           pCustomPlot[0]->graph(plot[0]++)->setName(item.value().name);
           showtype[0]=true;
       }
      else if(maxdata<=100&& plot[1]<MAX_DRAW-1)
     {
           pCustomPlot[1]->addGraph(); // blue line
           pCustomPlot[1]->graph(plot[1])->setPen(QPen(Color[plot[1]]));
           pCustomPlot[1]->yAxis->setRange(0, 100);
           pCustomPlot[1]->xAxis->setTicker(timeTicker);
           pCustomPlot[1]->legend->setVisible(true);//显示曲线名
           pCustomPlot[1]->graph(plot[1]++)->setName(item.value().name);
           showtype[1]=true;
       }
       else if(maxdata<=1000&& plot[2]<MAX_DRAW-1)
     {
           pCustomPlot[2]->addGraph(); // blue line
           pCustomPlot[2]->graph(plot[2])->setPen(QPen(Color[plot[2]]));
           pCustomPlot[2]->yAxis->setRange(0, 1000);
           pCustomPlot[2]->xAxis->setTicker(timeTicker);
           pCustomPlot[2]->legend->setVisible(true);//显示曲线名
           pCustomPlot[2]->graph(plot[2]++)->setName(item.value().name);
           showtype[2]=true;
        }
       else if(maxdata<=10000&& plot[3]<MAX_DRAW-1)
     {
          pCustomPlot[3]->addGraph(); // blue line
          pCustomPlot[3]->graph(plot[3])->setPen(QPen(Color[plot[3]]));
           pCustomPlot[3]->yAxis->setRange(0, 10000);
           pCustomPlot[3]->xAxis->setTicker(timeTicker);
           pCustomPlot[3]->legend->setVisible(true);//显示曲线名
           pCustomPlot[3]->graph(plot[3]++)->setName(item.value().name);
           showtype[3]=true;
       }
       else if(maxdata<=100000&& plot[4]<MAX_DRAW-1)
     {
          pCustomPlot[4]->addGraph(); // blue line
          pCustomPlot[4]->graph(plot[4])->setPen(QPen(Color[plot[4]]));
           pCustomPlot[4]->yAxis->setRange(0, 100000);
           pCustomPlot[4]->xAxis->setTicker(timeTicker);
           pCustomPlot[4]->legend->setVisible(true);//显示曲线名
           pCustomPlot[4]->graph(plot[4]++)->setName(item.value().name);
           showtype[4]=true;
       }
      else if(maxdata<=1000000&& plot[5]<MAX_DRAW-1)
     {
          pCustomPlot[5]->addGraph(); // blue line
          pCustomPlot[5]->graph(plot[5])->setPen(QPen(Color[plot[5]]));
           pCustomPlot[5]->yAxis->setRange(0, 1000000);
           pCustomPlot[5]->xAxis->setTicker(timeTicker);
           pCustomPlot[5]->legend->setVisible(true);//显示曲线名
           pCustomPlot[5]->graph(plot[5]++)->setName(item.value().name);
           showtype[5]=true;
       }
       else if(maxdata<=10000000&& plot[6]<MAX_DRAW-1)
     {
          pCustomPlot[6]->addGraph(); // blue line
          pCustomPlot[6]->graph(plot[6])->setPen(QPen(Color[plot[6]]));
           pCustomPlot[6]->yAxis->setRange(0, 10000000);
           pCustomPlot[6]->xAxis->setTicker(timeTicker);
           pCustomPlot[6]->legend->setVisible(true);//显示曲线名
           pCustomPlot[6]->graph(plot[6]++)->setName(item.value().name);
           showtype[6]=true;
     }
       else if(maxdata<=100000000&& plot[7]<MAX_DRAW-1)
     {
           pCustomPlot[7]->addGraph(); // blue line
           pCustomPlot[7]->graph(plot[7])->setPen(QPen(Color[plot[7]]));
           pCustomPlot[7]->yAxis->setRange(0, 100000000);
           pCustomPlot[7]->xAxis->setTicker(timeTicker);
           pCustomPlot[7]->legend->setVisible(true);//显示曲线名
           pCustomPlot[7]->graph(plot[7]++)->setName(item.value().name);
           showtype[7]=true;
      }
  }

  // 设置画布渐变色 /
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(242, 249, 255));
  plotGradient.setColorAt(1, QColor(218, 239, 255));


int k=0;
  for(int m=0;m<8;m++)
      if(showtype[m]==true)
      {
           pCustomPlot[m]->show();
          //pCustomPlot[m]->legend->setBrush(QColor(250, 25, 255, 200));
           pCustomPlot[m]->setBackground(plotGradient);
           switch(k)
           {
            case 0:
            case 4:
                pCustomPlot[m]->setGeometry(11, 11, 541, 279);
               break;
              case 1:
              case 5:
               pCustomPlot[m]->setGeometry(580, 11, 541, 279);
               break;
           case 2:
           case 6:
               pCustomPlot[m]->setGeometry(11, 301, 541, 279);
               break;
           case 3:
           case 7:
               pCustomPlot[m]->setGeometry(580, 301, 541, 279);
               break;
           }
           k++;
      }
      else
          pCustomPlot[m]->hide();
  */
// setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
//connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
//dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}
/**仪器命令控制
 * @brief MainWindow::startinstrumentCmd
 * @param instrumentname
 * @param cmd
 */
void MainWindow::startinstrumentCmd(QString instrumentname,QString cmd)
{
    int instrumentindex= pinstrumentManage->getinstrumentIndex();
      for (int i = 0; i < instrumentindex; i++)
      {
          if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().name==instrumentname)
          {
             pinstrumentManage->m_ctrlInstrument[i]->setinstrumentCmd(cmd);
          }
        }
}
/**初始化因子显示面板
 * @brief MainWindow::initPanelWidget
 */
void MainWindow::initPanelWidget()
{
    //加载设备面板
    qDeleteAll(frms);
    frms.clear();
    qDeleteAll(unitdlg);
    unitdlg.clear();
    qDeleteAll(zhanfangdlg);
    zhanfangdlg.clear();
    qDeleteAll(gongdiandlg);
    gongdiandlg.clear();
    qDeleteAll(biaoqidlg);
    biaoqidlg.clear();
    qDeleteAll(caiyangdlg);
    caiyangdlg.clear();
    qDeleteAll(qitadlg);
    qitadlg.clear();
    qDeleteAll(infodlg);
    infodlg.clear();
    unit *zhanfang=new unit;
      unit *biaoqi=new unit;
      unit *caiyang=new unit;
  int instrumentindex= pinstrumentManage->getinstrumentIndex();
    for (int i = 0; i < instrumentindex; i++) {
        if(pinstrumentManage->m_ctrlInstrument[i]->getshowfactornum()<=0)
        {
            continue;
        }
        if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="动环信息")
        {
            //qdonghuaninstrument=pinstrumentManage->m_ctrlInstrument[i];
            qixiangdlg *dlg=new qixiangdlg;
            dlg->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);
            dlg->setFixedHeight(266);
            dlg->setFixedWidth(500);
            qixiangdlglist.append(dlg);

        }
        else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="站房信息")
        {
            //qdonghuaninstrument=pinstrumentManage->m_ctrlInstrument[i];

            zhanfang->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);


        }

        else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="仪器供电")
        {
            unit *dlg=new unit;
            dlg->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);
            gongdiandlg.append(dlg);

        }
        else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="标气压力")
        {
            //unit *dlg=new unit;
            biaoqi->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);
           // biaoqidlg.append(dlg);
        }
         else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="采样信息")
        {
          //  unit *dlg=new unit;
            caiyang->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);
          //  caiyangdlg.append(dlg);
        }
         else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="其他供电")
        {
            unit *dlg=new unit;
            dlg->setInstrument(pinstrumentManage->m_ctrlInstrument[i]);
            qitadlg.append(dlg);
        }
        else if(pinstrumentManage->m_ctrlInstrument[i]->getinstrumentinfo().type=="多参数")
        {
          ;
        }
        else
        {
           int count=pinstrumentManage->m_ctrlInstrument[i]->getfactorDataMap().size();
           for(int j=0;j<count;j++)
           {
               frmdevice *frm = new frmdevice;
               frm->setFixedHeight(410);
               frm->setInstrument(pinstrumentManage->m_ctrlInstrument[i],j);
               frms.append(frm);
           }
        }
    }
    zhanfangdlg.append(zhanfang);
    biaoqidlg.append(biaoqi);
    caiyangdlg.append(caiyang);

    Info *dlg=new Info;
    dlg->setFixedHeight(285);
    dlg->setFixedWidth(500);
    // unit *dlg = new unit;
    infodlg.append(dlg);
    ui->widgetPanel_8->setAutoWidth(true);
    ui->widgetPanel_8->setWidget(infodlg, 1);
    ui->widgetPanel_8->setMargin(1);
    ui->widgetPanel_8->setSpace(2);
    ui->widgetPanel_8->setFixedHeight(290);



    Othordlg *odlg=new Othordlg;
    odlg->setFixedHeight(246);
    odlg->setFixedWidth(500);
            // unit *dlg = new unit;
   othordlg.append(odlg);
   ui->widgetPanel_9->setAutoWidth(true);
   ui->widgetPanel_9->setWidget(othordlg, 1);
   ui->widgetPanel_9->setMargin(1);
   ui->widgetPanel_9->setSpace(2);
   ui->widgetPanel_9->setFixedHeight(252);

   ui->widgetPanel->setAutoWidth(true);
    ui->widgetPanel->setWidget(frms, 3);
    ui->widgetPanel->setMargin(3);
    ui->widgetPanel->setSpace(3);

    ui->widgetPanel_2->setAutoWidth(true);
    ui->widgetPanel_2->setWidget(qixiangdlglist, 1);
    ui->widgetPanel_2->setMargin(1);
    ui->widgetPanel_2->setSpace(2);
    ui->widgetPanel_2->setFixedHeight(272);


    if(zhanfang->getfactornum()>0)
    {
      ui->widgetPanel_3->setAutoWidth(true);
      ui->widgetPanel_3->setWidget(zhanfangdlg, 1);
      ui->widgetPanel_3->setMargin(1);
      ui->widgetPanel_3->setSpace(20);
      int heigh=0;
      for(int i=0;i<zhanfangdlg.size();i++)
      {
          heigh=heigh+zhanfangdlg.at(i)->getfactornum();
      }
          ui->widgetPanel_3->setFixedHeight(heigh*32+40);
    }
    else
    {
        ui->widgetPanel_3->hide();
    }
    if( gongdiandlg.size()>0)
    {
      ui->widgetPanel_4->setAutoWidth(true);
      ui->widgetPanel_4->setWidget( gongdiandlg, 1);
      ui->widgetPanel_4->setMargin(1);
      ui->widgetPanel_4->setSpace(20);
      int heigh=0;
      for(int i=0;i<gongdiandlg.size();i++)
      {
          heigh=heigh+gongdiandlg.at(i)->getfactornum();
      }
          ui->widgetPanel_4->setFixedHeight(heigh*32+40);
    }
    else
    {
        ui->widgetPanel_4->hide();
    }
    if(biaoqi->getfactornum()>0)
    {
      ui->widgetPanel_5->setAutoWidth(true);
      ui->widgetPanel_5->setWidget(biaoqidlg, 1);
      ui->widgetPanel_5->setMargin(1);
      ui->widgetPanel_5->setSpace(20);
      int heigh=0;
      for(int i=0;i<biaoqidlg.size();i++)
      {
          heigh=heigh+biaoqidlg.at(i)->getfactornum();
      }
          ui->widgetPanel_5->setFixedHeight(heigh*32+40);
    }
    else
    {
        ui->widgetPanel_5->hide();
    }
    if(caiyang->getfactornum()>0)
    {
      ui->widgetPanel_6->setAutoWidth(true);
      ui->widgetPanel_6->setWidget(caiyangdlg, 1);
      ui->widgetPanel_6->setMargin(1);
      ui->widgetPanel_6->setSpace(20);
      int heigh=0;
      for(int i=0;i<caiyangdlg.size();i++)
      {
          heigh=heigh+caiyangdlg.at(i)->getfactornum();
      }
          ui->widgetPanel_6->setFixedHeight(heigh*32+40);
    }
    else
    {
        ui->widgetPanel_6->hide();
    }
    if(qitadlg.size()>0)
    {
      ui->widgetPanel_7->setAutoWidth(true);
      ui->widgetPanel_7->setWidget(qitadlg, 1);
      ui->widgetPanel_7->setMargin(1);
      ui->widgetPanel_7->setSpace(20);
      int heigh=0;
      for(int i=0;i<qitadlg.size();i++)
      {
          heigh=heigh+qitadlg.at(i)->getfactornum();
      }
          ui->widgetPanel_7->setFixedHeight(heigh*32+40);
    }
    else
    {
        ui->widgetPanel_7->hide();
    }


}

void MainWindow::initfactorDlg()
{
     QString sqlstr;
    qDeleteAll(factorsetdlglist);
    factorsetdlglist.clear();
    sqlstr="select name,label,max,min,dataNum,a.type,modulus,need_upload ,a.id from factor a, combo_box b where a.unit=b.value and b.type='unit'";
    initdlg(sqlstr,ui->widgetPanel_10,"因子");
    ui->widgetPanel_10->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initinstrumentDlg()
{
     QString sqlstr;
     qDeleteAll(instrumentsetdlglist);
     instrumentsetdlglist.clear();
     sqlstr="select name,type,checked,baudrate,parity,stopBit,port,ip,autoReadType ,id from instrument";

     initdlg(sqlstr,ui->widgetPanel_11,"仪器");
     ui->widgetPanel_11->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initqualitysetDlg()
{
     QString sqlstr;
     qDeleteAll(qualitysetdlglist);
     qualitysetdlglist.clear();
     sqlstr="select  name ,mode ,id from instrument  where checked='是'";
     initdlg(sqlstr,ui->widgetPanel_12,"质控");
     ui->widgetPanel_12->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initctrlcmdDlg()
{
     QString sqlstr;
     qDeleteAll(ctrlcmdsetdlglist);
     ctrlcmdsetdlglist.clear();
     sqlstr="select  name,cmdName,cmd ,a.id from instrumentcmd a ,instrument b where b.id=a.instrumentId";
     initdlg(sqlstr,ui->widgetPanel_13,"控制命令");
     ui->widgetPanel_13->setStyleSheet("background:transparent;");//设置背景透明

}
void MainWindow::initsearchcmdDlg()
{
     QString sqlstr;
     qDeleteAll(searchcmdsetdlglist);
     searchcmdsetdlglist.clear();
     sqlstr="select b.`name` ,c.name,addr,num , cmd,label,a.id from instrumentsearch a ,instrument b ,factor c ,combo_box d where a.instrumentId=b.id and c.id=a.factorId and d.type='formula_type' and d.`value`=a.formulaId";
     initdlg(sqlstr,ui->widgetPanel_14,"查询命令");
     ui->widgetPanel_14->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initinstrumentconnectDlg()
{
     QString sqlstr;
     qDeleteAll(instrumentconnectsetdlglist);
     instrumentconnectsetdlglist.clear();
     sqlstr="select  name ,communicationType,label ,autoReadType ,a.id from instrument a,combo_box b where a.checked='是' and b.type='com_id' and b.`value`=a.comID";
     initdlg(sqlstr,ui->widgetPanel_15,"串口设置");
     ui->widgetPanel_15->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initnetworkDlg()
{
     QString sqlstr;
     qDeleteAll(networksetdlglist);
    networksetdlglist.clear();
    sqlstr="select label,ip,port,mn,password,st, sendFlag,requestFlag,used ,a.id from networkset a ,combo_box b where b.type='protocol' and a.protocol=b.value";
    initdlg(sqlstr,ui->widgetPanel_16,"网络协议");
    ui->widgetPanel_16->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::initnetworkfactorIdDlg(QString xieyi)
{
     QString sqlstr;
     qDeleteAll(networkfactorIdsetdlglist);
     networkfactorIdsetdlglist.clear();
     //sqlstr="select  label ,b.name,polId ,a.id from netpolid a, factor b,combo_box c where a.factorId=b.id and c.type='protocol' and c.`value`=a.protocalId";
      sqlstr="select  label ,b.name,polId ,a.id from netpolid a, factor b,combo_box c where a.factorId=b.id and c.type='protocol' and c.`value`=a.protocalId and c.label='"+xieyi+"'";
     initdlg(sqlstr,ui->widgetPanel_17,"网络因子编码");
     ui->widgetPanel_17->setStyleSheet("background:transparent;");//设置背景透明
}
void MainWindow::inituserDlg()
{
     QString sqlstr;
     qDeleteAll(usersetdlglist);
     usersetdlglist.clear();
     sqlstr="select user,type,description,add_time,update_time,login_time ,id from cfg_user";
      initdlg(sqlstr,ui->widgetPanel_18,"用户管理");
      ui->widgetPanel_18->setStyleSheet("background:transparent;");//设置背景透明
}
/**初始化系统设置显示面板
 * @brief MainWindow::initPanelWidget
 */
void MainWindow::initsystemsetPanelWidget()
{
    //加载设备面板
    initfactorDlg();
    initinstrumentDlg();
    initqualitysetDlg();
    initctrlcmdDlg();
    initsearchcmdDlg();
    initinstrumentconnectDlg();
    initnetworkDlg();
    initnetworkfactorIdDlg(ui->comboBox_14->currentText());
    inituserDlg();
   // qDeleteAll(othersetdlglist);
   // othersetdlglist.clear();

}
/**  初始化系统设置对话框
 * @brief MainWindow::initdlg
 * @param widgetPanel
 * @param type
 */
void MainWindow::initdlg(QString sqlstr, PanelWidget *widgetPanel,QString type)
{

 QStringList namelist;
 /*因子*/
 QSqlQuery query;
query.exec("SET NAMES UTF8");
query.exec(sqlstr);
if(type=="因子")
    namelist<<"名称"<<"单位"<<"最大值"<<"最小值"<<"精度"<<"显示"<<"转换系数"<<"上传";
 else if(type=="仪器")
{
     namelist<<"仪器名" << "类型" << "本站点仪器"<< "波特率" << "校验"<<"停止位" << "端口号" << "IP" << "仪器自动发送数据";
}
else if(type=="质控")
{
    namelist << "仪器名" << "仪器模式";
}
else if(type=="查询命令")
 {
    namelist<<"仪器名" << "因子" <<"数据起始位" << "数据位数" << "查询命令"<< "计算公式";
  }
else if(type=="控制命令")
 {
   namelist<<"仪器名" << "命令名称" << "命令";
  }
else if(type=="串口设置")
 {
   namelist<<"仪器名" << "通讯接口" << "串口号"<<"自动读取";
  }
else if(type=="网络因子编码")
{
  namelist<<"协议名" << "因子名" << "因子编码";
}
else if(type=="网络协议")
{
    namelist<<"协议名称" << "IP"<<"端口号" << "MN码"<<"密码"<<"ST" << "发送标记" << "回复标记"<<"是否启用";
}
else if(type=="用户管理")
{
    namelist<<"用户名" << "用户类型" << "描述" << "创建时间"<<"修改时间" << "最近登录时间";
}
QString istr,idstr;
int count=query.size();
while(query.next())
{
    int i=0;
    datainfomap datainfomaplist;
    while(i<namelist.size())
    {
       datainfo tempdatainfo;
       tempdatainfo.name=namelist.at(i);
       istr= QString("%1").arg(i);
       tempdatainfo.data=query.value(i).toString();
       datainfomaplist.insert(istr+namelist.at(i++),tempdatainfo);
    }
    idstr=query.value(i).toString();
    setinfoDlg *dlg=new setinfoDlg;
    dlg->setFixedHeight(250);
    dlg->setdatainfo(datainfomaplist,type,idstr,count);
    connect(dlg ,SIGNAL(infoSend(datainfomap,QString,QString)) ,this ,SLOT(infoRecv(datainfomap,QString,QString)));
    if(type=="因子")
      factorsetdlglist.append(dlg);
    else if(type=="仪器")
    {
       instrumentsetdlglist.append(dlg);
    }
    else if(type=="质控")
    {
        qualitysetdlglist.append(dlg);
    }
    else if(type=="查询命令")
    {
        searchcmdsetdlglist.append(dlg);
    }
    else if(type=="控制命令")
    {
        ctrlcmdsetdlglist.append(dlg);
    }
    else if(type=="串口设置")
    {
        instrumentconnectsetdlglist.append(dlg);
    }
    else if(type=="网络协议")
     {
       networksetdlglist.append(dlg);
      }
    else if(type=="网络因子编码")
    {
      networkfactorIdsetdlglist.append(dlg);
    }
    else if(type=="用户管理")
    {
        usersetdlglist.append(dlg);
    }
}
   widgetPanel->setAutoWidth(true);
  if(type=="因子")
       widgetPanel->setWidget(factorsetdlglist, 4);
   else if(type=="仪器")
   {
       widgetPanel->setWidget(instrumentsetdlglist, 4);
   }
  else if(type=="质控")
  {
      widgetPanel->setWidget(qualitysetdlglist, 4);
  }
  else if(type=="查询命令")
   {
       widgetPanel->setWidget(searchcmdsetdlglist, 4);
  }
  else if(type=="控制命令")
   {
       widgetPanel->setWidget(ctrlcmdsetdlglist, 4);
  }
  else if(type=="串口设置")
   {
       widgetPanel->setWidget(instrumentconnectsetdlglist, 4);
  }
  else if(type=="网络协议")
   {
       widgetPanel->setWidget(networksetdlglist, 4);
  }
  else if(type=="网络因子编码")
   {
       widgetPanel->setWidget(networkfactorIdsetdlglist, 4);
  }
  else if(type=="用户管理")
  {
      widgetPanel->setWidget(usersetdlglist, 4);
  }

  widgetPanel->setMargin(5);
  widgetPanel->setSpace(12);
}
/**设置站房管理信息窗口
 * @brief MainWindow::SetzhangfangDlg
 */
/*void MainWindow::SetzhangfangDlg()
{
    unit *dlg=new unit;
    dlg->setGeometry()
}*/
/**显示实时数据
 * @brief MainWindow::showRealData
 */
void MainWindow::showRealData()
{
   // factorInfotype factorinfoMap;

    // factorinfoMap=pinstrumentManage->getFactorinfo();
      QListIterator<frmdevice *> i(frms);//
     while(i.hasNext())
     {
        frmdevice *from= i.next();
        from->setfactorData();
     }
      QListIterator<unit *> item(unitdlg);//
      while(item.hasNext())
      {
          unit *tempunit=item.next();
          tempunit->setfactorData();
      }
      QListIterator<unit *> zhanfangitem(zhanfangdlg);//
      while(zhanfangitem.hasNext())
      {
          unit *zhanfangitemunit=zhanfangitem.next();
          zhanfangitemunit->setfactorData();
      }
      QListIterator<unit *> gongdianitem(gongdiandlg);//
      while(gongdianitem.hasNext())
      {
          unit *gongdianitemitemunit=gongdianitem.next();
          gongdianitemitemunit->setfactorData();
      }
      QListIterator<unit *> biaoqiitem(biaoqidlg);//
      while(biaoqiitem.hasNext())
      {
          unit *biaoqiitemunit=biaoqiitem.next();
          biaoqiitemunit->setfactorData();
      }
      QListIterator<unit *>caiyangitem(caiyangdlg);//
      while(caiyangitem.hasNext())
      {
          unit *caiyangitemunit=caiyangitem.next();
          caiyangitemunit->setfactorData();
      }
      QListIterator<unit *>qitaitem(qitadlg);//
      while(qitaitem.hasNext())
      {
          unit *qitaitemunit=qitaitem.next();
           qitaitemunit->setfactorData();
      }
      QListIterator<qixiangdlg *>qixiangtem(qixiangdlglist);//
      while(qixiangtem.hasNext())
      {
          qixiangdlg *qixiangtemunit=qixiangtem.next();
           qixiangtemunit->Show();
      }
}
void MainWindow::realtimeDataSlot()
{
/*
//static QTime time(QTime::currentTime());
 double data1=0.5;
 //factorInfotype factorinfoMap;
 //factorinfoMap=pinstrumentManage->getFactorinfo();
 showRealData();
// calculate two new data points:
  QTime current_time =QTime::currentTime();

//double key = time.elapsed()/100000.0+current_time.hour()*3600+current_time.minute()*60+current_time.second(); // time elapsed since start of demo, in seconds
  double key = current_time.hour()*3600+current_time.minute()*60+current_time.second();
//double key = time.elapsed()/1000.0;
static double lastPointKey = 0;
int i=0;
int maxdata=0;
int Plotdata[MAX_PLOT]={0,0,0};
  QMapIterator<int,factorinfo> item(pinstrumentManage->getFactorinfo());
if (key-lastPointKey > 0.002) // at most add point every 2 ms
{
  // add data to lines:
    while(item.hasNext())
    {
        item.next();
        data1=item.value().data;
        maxdata=item.value().maxdata;
        if(data1<0)
           data1=0;
         if(maxdata<=10&&Plotdata[0]<plot[0])
         {
               data1= data1>10?10:data1;
               pCustomPlot[0]->graph(Plotdata[0]++)->addData(key,data1);
           }
          else if(maxdata<=100&&Plotdata[1]<plot[1])
          {
           data1= data1>100?100:data1;
               pCustomPlot[1]->graph(Plotdata[1]++)->addData(key,data1);
          }
          else if(maxdata<=1000&&Plotdata[2]<plot[2])
         {
            data1= data1>1000?1000:data1;
               pCustomPlot[2]->graph(Plotdata[2]++)->addData(key,data1);
         }
         else if(maxdata<=10000&&Plotdata[3]<plot[3])
         {
            data1= data1>10000?10000:data1;
               pCustomPlot[3]->graph(Plotdata[3]++)->addData(key,data1);
          }
         else if(maxdata<=100000&&Plotdata[4]<plot[4])
         {
            data1= data1>100000?100000:data1;
               pCustomPlot[4]->graph(Plotdata[4]++)->addData(key,data1);
          }
        else if(maxdata<=1000000&&Plotdata[5]<plot[5])
         {
              data1= data1>1000000?1000000:data1;
               pCustomPlot[5]->graph(Plotdata[5]++)->addData(key,data1);
        }
        else if(maxdata<=10000000&&Plotdata[6]<plot[6])
         {
            data1= data1>10000000?10000000:data1;
               pCustomPlot[6]->graph(Plotdata[6]++)->addData(key,data1);
         }
          else if(maxdata<=100000000&&Plotdata[7]<plot[7])
         {
            data1= data1>100000000?100000000:data1;
               pCustomPlot[7]->graph(Plotdata[7]++)->addData(key,data1);
         }
   }
  // rescale value (vertical) axis to fit the current data:

  lastPointKey = key;
}
// make key axis range scroll with the data (at a constant range size of 8):
//ui->plot->xAxis->setRange(key, 8, Qt::AlignRight);
//ui->plot->replot();
for(i=0;i<MAX_PLOT;i++)
{
    if(showtype[i]==true)
    {
        pCustomPlot[i]->xAxis->setRange(key, 1200, Qt::AlignRight);
        pCustomPlot[i]->replot();
    }
}
// calculate frames per second:
*/
}

/**因子列表操作，修改或插入
 * @brief MainWindow::on_pushButton_21_clicked
 */
void MainWindow::on_pushButton_21_clicked()
{
   QString str=ui->pushButton_21->text();
   QStringList  ColumndataList,ColumnNameList;
   ColumnNameList<< "min" << "max" << "unit"<<"dataNum"<<"type"<<"modulus"<<"need_upload"<<"name";//QStringList赋值
   ColumndataList.append(ui->lineEdit_4->text());//因子名
   ColumndataList.append(ui->lineEdit_5->text());//最小值
   ColumndataList.append(ui->lineEdit_6->text());//最大值
   int index=ui->comboBox_5->currentIndex();
  // ColumndataList.append(QString("%1").arg(index+1));//单位
   ComboBoxdata mydata = ui->comboBox_5->itemData(index).value<ComboBoxdata>();
   QString indexstr=QString("%1").arg(mydata.index);
    ColumndataList.append(indexstr);//单位
   ColumndataList.append(ui->comboBox_6->currentText());//小数位数
   if(ui->checkBox->isChecked())//是否显示
   {
       ColumndataList.append("显示");//
   }
   else
   {
       ColumndataList.append("不显示");//
   }
   ColumndataList.append(ui->lineEdit_7->text());//单位转化系数
   if(ui->checkBox_2->isChecked())//是否上传
   {
        ColumndataList.append("上传");//
   }
   else
   {
       ColumndataList.append("不上传");//
   }
   QString logstr;
   QStringList list;
   list.append("操作日志");
   if(str=="新增")
   {
       pDbControl->factorinsertData(ColumndataList);

       logstr=tr("新增因子 %1").arg(ui->lineEdit_4->text());
       list.append(logstr);
       pDbControl->loginsertData(list);
       initfactorDlg();
   }
   else if(str=="修改")
   {
       ColumndataList.removeAt(0);
       ColumndataList.append(ui->lineEdit_4->text());//因子名
       pDbControl->factorupdateData(ColumnNameList,ColumndataList,7);

       logstr=tr("修改因子 %1").arg(ui->lineEdit_4->text());
       list.append(logstr);
       pDbControl->loginsertData(list);
       /* 设置显示对话框 */
      QString id= getfactorId();
      QStringList namelist,datalist;
      namelist<<"名称"<<"单位"<<"最大值"<<"最小值"<<"精度"<<"显示"<<"转换系数"<<"上传";
      datalist.append( ui->lineEdit_4->text());
      datalist.append( ui->comboBox_5->currentText());
      datalist.append( ui->lineEdit_6->text());
      datalist.append( ui->lineEdit_5->text());
      datalist.append( ui->comboBox_6->currentText());
      if(ui->checkBox->isChecked())
      {
          datalist.append("显示");
      }
      else
      {
          datalist.append("不显示");
      }
      datalist.append( ui->lineEdit_7->text());
      if(ui->checkBox_2->isChecked())
      {
          datalist.append("上传");
      }
      else
      {
          datalist.append("不上传");
      }
      setdlginfo(factorsetdlglist,namelist,datalist,id);
   }
  // initFactorQueryModel();



}
void MainWindow::setdlginfo(QList<setinfoDlg *> dlglist,QStringList namelist,QStringList datalist,QString id)
{
    QString istr;
        int i=0;
        datainfomap datainfomaptemp;
        while(i<namelist.size())
        {
           datainfo tempdatainfo;
           tempdatainfo.name=namelist.at(i);
           istr= QString("%1").arg(i);
           tempdatainfo.data=datalist.at(i);
           datainfomaptemp.insert(istr+namelist.at(i++),tempdatainfo);
        }
   QListIterator<setinfoDlg *> item(dlglist);//
   int count=dlglist.size();
    while(item.hasNext())
     {
                setinfoDlg *itemunit=item.next();
                if(itemunit->gettype()=="因子"&&itemunit->getId()==factorId)
                {
                    itemunit->setdatainfo(datainfomaptemp,"因子",id,count);
                    break;
                }
                else if(itemunit->gettype()=="仪器"&&itemunit->getId()==getinstrumentId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"仪器",id,count);
                    break;
                }
                else if(itemunit->gettype()=="网络协议"&&itemunit->getId()==getnetworkId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"网络协议",id,count);
                    break;
                }
                else if(itemunit->gettype()=="网络因子编码"&&itemunit->getId()==getnetworkfactorId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"网络因子编码",id,count);
                    break;
                }
                else if(itemunit->gettype()=="质控"&&itemunit->getId()==getqueryId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"质控",id,count);
                    break;
                }
                else if(itemunit->gettype()=="控制命令"&&itemunit->getId()==getctrlCmdId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"控制命令",id,count);
                    break;
                }
                else if(itemunit->gettype()=="查询命令"&&itemunit->getId()==getsearchCmdId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"查询命令",id,count);
                    break;
                }
                else if(itemunit->gettype()=="串口设置"&&itemunit->getId()==getinstrumentconnectId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"串口设置",id,count);
                    break;
                }
                else if(itemunit->gettype()=="用户管理"&&itemunit->getId()==getusersetId())
                {
                    itemunit->setdatainfo(datainfomaptemp,"用户管理",id,count);
                    break;
                }
     }

}
/**设置被选中窗口
 * @brief MainWindow::setdlginfoselect
 * @param dlglist
 * @param id
 */
void MainWindow::setdlginfoselect(QList<setinfoDlg *> dlglist,QString id)
{
    QString istr;
        int i=0;

   QListIterator<setinfoDlg *> item(dlglist);//

    while(item.hasNext())
     {
                setinfoDlg *itemunit=item.next();
                if(itemunit->gettype()=="因子")
                {
                    if(itemunit->getId()==factorId)
                    {
                         itemunit->drawback(true);
                    }
                    else
                        itemunit->drawback(false);
                }
                else if(itemunit->gettype()=="仪器")
                {
                     if(itemunit->getId()==getinstrumentId())
                     {
                         itemunit->drawback(true);
                    }
                    else
                        itemunit->drawback(false);
                }
                else if(itemunit->gettype()=="网络协议")
                {
                   if(itemunit->getId()==getnetworkId())
                   {
                       itemunit->drawback(true);
                  }
                  else
                      itemunit->drawback(false);
                }
              else if(itemunit->gettype()=="网络因子编码")
              {
                  if(itemunit->getId()==getnetworkfactorId())
                   {
                      itemunit->drawback(true);
                   }
                 else
                     itemunit->drawback(false);
                }

                else if(itemunit->gettype()=="质控")
                {
                   if(itemunit->getId()==getqueryId())
                   {
                      itemunit->drawback(true);
                   }
                 else
                     itemunit->drawback(false);
                }
                else if(itemunit->gettype()=="控制命令")
                {
                   if(itemunit->getId()==getctrlCmdId())
                   {
                      itemunit->drawback(true);
                   }
                 else
                     itemunit->drawback(false);

                }
                else if(itemunit->gettype()=="查询命令")
                {
                   if(itemunit->getId()==getsearchCmdId())
                   {
                      itemunit->drawback(true);
                   }
                 else
                     itemunit->drawback(false);
                }
                else if(itemunit->gettype()=="串口设置")
                {
                    if(itemunit->getId()==getinstrumentconnectId())
                    {
                       itemunit->drawback(true);
                    }
                  else
                      itemunit->drawback(false);
                }
                else if(itemunit->gettype()=="用户管理")
                {
                    if(itemunit->getId()==getusersetId())
                    {
                       itemunit->drawback(true);
                    }
                  else
                      itemunit->drawback(false);
                }
     }

}
void MainWindow::on_pushButton_19_clicked()
{
      ui->pushButton_21->setText("新增");
}

/**删除因子
 * @brief MainWindow::on_pushButton_20_clicked
 */
void MainWindow::on_pushButton_20_clicked()
{
    QStringList columndata, valuedata;
     QSqlQuery query;
     QString name;
  //   QStringList listdata= getTableViewRowData(ui->tableView_3,8) ;

    QString sqlstr="select name from factor where id=";
    sqlstr=sqlstr+factorId;
     query.exec("SET NAMES UTF8");
     query.exec(sqlstr);
     while(query.next())
     {
         name=query.value("name").toString();
     }
    columndata<<"id";
    valuedata.append(factorId);

    QString str;
   str="你是否要删除"+name+"?";
   if(!getfactorId().isEmpty())
   {
    if (helpclass.ShowMessageBox(str)) {
          pDbControl->factordelete(columndata,valuedata);
         /* qDeleteAll(factorsetdlglist);
          factorsetdlglist.clear();
          sqlstr="select name,label,max,min,dataNum,a.type,modulus,need_upload ,a.id from factor a, combo_box b where a.unit=b.value and b.type='unit'";
          initdlg(sqlstr,ui->widgetPanel_10,"因子");*/
          initfactorDlg();
    }
   }
   else
   {
       helpclass.ShowoneMessageBox("请先选择一个因子");
   }

}
/**仪器列表，仪器查询与修改
 * @brief MainWindow::on_pushButton_18_clicked
 */
void MainWindow::on_pushButton_18_clicked()
{
    QString str=ui->pushButton_18->text();
    QStringList  ColumndataList,ColumnNameList;
    ColumnNameList << "type" << "baudrate" <<"parity"<<"port"<<"ip"<<"stopBit"<<"checked"<<"name";//QStringList赋值
    ColumndataList.append(ui->lineEdit->text());//仪器名
    ColumndataList.append(ui->comboBox->currentText());
    ColumndataList.append(ui->comboBox_2->currentText());
    ColumndataList.append(ui->comboBox_3->currentText());
    ColumndataList.append(ui->lineEdit_3->text());//端口号
    ColumndataList.append(ui->lineEdit_2->text());//IP
    ColumndataList.append(ui->comboBox_4->currentText());

    QString logstr;
    QStringList list;
    list.append("操作日志");

    if(str=="新增")
    {
        ColumndataList.append("是");//是否被选中
        ColumndataList.append("0");//通讯类型
        ColumndataList.append("0");//是否自动接收数据
        ColumndataList.append("1");//串口号
        ColumndataList.append("1000");
        ColumndataList.append("正常");
        pDbControl->instrumentinsertData(ColumndataList);
        logstr=tr("新增仪器 %1").arg(ui->lineEdit->text());
        list.append(logstr);
        pDbControl->loginsertData(list);
        initinstrumentDlg();
       if(helpclass.ShowMessageBox("是否需要添加查询命令?"))//2019.11.5
       {
           QString sqlstr;
           qDeleteAll(searchcmdsetdlglist);
           searchcmdsetdlglist.clear();
           sqlstr="select b.`name` ,c.name,addr,num , cmd,label,a.id from instrumentsearch a ,instrument b ,factor c ,combo_box d where a.instrumentId=b.id and c.id=a.factorId and d.type='formula_type' and d.`value`=a.formulaId and b.name='"+ui->lineEdit->text()+"'";
           initdlg(sqlstr,ui->widgetPanel_14,"查询命令");
           initSearchCmdComboBox();
           int comboBoxindex=ui->comboBox_9->findText(ui->lineEdit->text());
           ui->comboBox_9->setCurrentIndex(comboBoxindex);

           ui->tabWidget_System->setCurrentIndex(0);
           ui->tabWidget_System->setTabEnabled(0, true);
           ui->tabWidget_5->setCurrentIndex(4);
           ui->tabWidget_5->setTabEnabled(4, true);
           ui->listView_2->hide();
           ui->pushButton_5->show();
           insertsearchCmd=true;
       }
    }
    else if(str=="修改")
    {

        ColumndataList.removeAt(0);

        ColumndataList.append(ui->comboBox_21->currentText());
          ColumndataList.append(ui->lineEdit->text());//
        pDbControl->instrumentupdateData(ColumnNameList,ColumndataList,7);

        logstr=tr("修改仪器 %1").arg(ui->lineEdit->text());
        list.append(logstr);

        pDbControl->loginsertData(list);
        /* 设置显示对话框 */
       QString id= getinstrumentId();
       QStringList namelist,datalist;
       namelist<<"仪器名" << "类型" << "本站点仪器"<< "波特率" << "校验"<<"停止位" << "端口号" << "IP" ;
       datalist.append( ui->lineEdit->text());
       datalist.append( ui->comboBox->currentText());
       datalist.append( ui->comboBox_21->currentText());
       datalist.append( ui->comboBox_2->currentText());
       datalist.append( ui->comboBox_3->currentText());
       datalist.append( ui->comboBox_4->currentText());
       datalist.append( ui->lineEdit_3->text());
       datalist.append( ui->lineEdit_2->text());
       setdlginfo(instrumentsetdlglist,namelist,datalist,id);
    }
   // initInstrumentQueryModel();
    // initinstrumentmodeQueryModel();

}
/**根据编码查名称
 * @brief MainWindow::fromintoName
 * @param sqlstr
 * @return
 */
QString MainWindow::fromintoName(QString sqlstr)
{
    QString name;
     QSqlQuery query;
  //  QString sqlstr="select name from instrument where id=";
   // sqlstr=sqlstr+getinstrumentId();
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    while(query.next())
    {
       name= query.value("name").toString();
    }
    return name;
}

/**删除仪器
 * @brief MainWindow::on_pushButton_17_clicked
 */
void MainWindow::on_pushButton_17_clicked()
{
    QStringList columndata, valuedata;
    QString name;
     QSqlQuery query;
    // QStringList listdata= getTableViewRowData(ui->tableView,8) ;
    QString sqlstr="select name from instrument where id=";
    sqlstr=sqlstr+getinstrumentId();
    query.exec("SET NAMES UTF8");
    query.exec(sqlstr);
    while(query.next())
    {
       name= query.value("name").toString();
    }
    columndata<<"id";
    valuedata.append(getinstrumentId());
    QString str;
    str="你是否要删除"+name+"?";
    if(!getinstrumentId().isEmpty())
    {
    if (helpclass.ShowMessageBox(str)) {
          pDbControl->instrumentdelete(columndata,valuedata);
        // initInstrumentQueryModel();
         /* qDeleteAll(instrumentsetdlglist);
          instrumentsetdlglist.clear();
          sqlstr="select name,type,checked,baudrate,parity,stopBit,port,ip,autoReadType from instrument";
          initdlg(sqlstr,ui->widgetPanel_11,"仪器");*/
          initinstrumentDlg();

    }
    }
    else
    {
        helpclass.ShowoneMessageBox("请先选择一台仪器");
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->pushButton_18->setText("新增");
}
/**删除控制命令
 * @brief MainWindow::on_pushButton_23_clicked
 */
void MainWindow::on_pushButton_23_clicked()
{
      QStringList columndata, valuedata;

      columndata<<"id";
      valuedata.append(getctrlCmdId());
      QString str, sqlstr;
      str="你是否要删除"+getctrlCmdId()+"?";
      if(!getctrlCmdId().isEmpty())
      {
      if (helpclass.ShowMessageBox(str)) {
            pDbControl->CtrlCmddelete(columndata,valuedata);
           /* qDeleteAll(ctrlcmdsetdlglist);
            ctrlcmdsetdlglist.clear();
            sqlstr="select  name,cmdName,cmd ,a.id from instrumentcmd a ,instrument b where b.id=a.instrumentId";
            initdlg(sqlstr,ui->widgetPanel_13,"控制命令");*/
            initctrlcmdDlg();
      }
      }
      else
      {
          helpclass.ShowoneMessageBox("请先选择一个控制命令");
      }
}
/**控制命令操作
 * @brief MainWindow::on_pushButton_24_clicked
 */
void MainWindow::on_pushButton_24_clicked()
{
    QString str=ui->pushButton_24->text();
       QStringList  ColumndataList,ColumnNameList;
       ColumnNameList<<"instrumentId" << "cmdName"<< "cmd"<<"id" ;//QStringList
       int index=ui->comboBox_7->currentIndex();
       ComboBoxdata mydata = ui->comboBox_7->itemData(index).value<ComboBoxdata>();
       QString indexstr=QString("%1").arg(mydata.index);

       ColumndataList.append(indexstr);
       ColumndataList.append(ui->comboBox_8->currentText());
       ColumndataList.append(ui->lineEdit_8->text());//똥왯뵀
       QString logstr;
       QStringList list;
       list.append("操作日志");
       if(str=="新增")
       {
           pDbControl->CtrlCmdinsertData(ColumndataList);

           logstr=indexstr+": "+tr("新增查询命令 %1").arg(ui->comboBox_8->currentText());
           list.append(logstr);
           pDbControl->loginsertData(list);
           initctrlcmdDlg();
       }
       else if(str=="修改")
       {
           ColumndataList.append(ui->lineEdit_29->text());
           pDbControl->CtrlCmdupdateData(ColumnNameList,ColumndataList,3);
           logstr=indexstr+": "+tr("修改控制命令 %1").arg(ui->comboBox_8->currentText());
           list.append(logstr);
           pDbControl->loginsertData(list);
           /* 设置显示对话框 */
          QString id= getctrlCmdId();
          QStringList namelist,datalist;
          namelist<<"仪器名" << "命令名称" << "命令" ;
          datalist.append( ui->comboBox_7->currentText());
          datalist.append( ui->comboBox_8->currentText());
          datalist.append( ui->lineEdit_8->text());
          setdlginfo(ctrlcmdsetdlglist,namelist,datalist,id);
       }
   // initCtrlCmdQueryModel();

}

void MainWindow::on_pushButton_22_clicked()
{
     ui->pushButton_24->setText("新增");
}
/**查询命令操作
 * @brief MainWindow::on_pushButton_27_clicked
 */
void MainWindow::on_pushButton_27_clicked()
{
    //  "cmd" << "addr" << "num"<<"factorId"<<"instrumentId"<<"formulaId";//QStringList赋值
    QString str=ui->pushButton_27->text();
    QStringList  ColumndataList,ColumnNameList;
    ColumnNameList<< "cmd" << "addr" << "num"<<"formulaId"<<"factorId"<<"instrumentId";//QStringList赋值
    ColumndataList.append(ui->lineEdit_9->text());//cmd
    ColumndataList.append(ui->lineEdit_10->text());//adr
    ColumndataList.append(ui->lineEdit_11->text());//num
    int index=ui->comboBox_10->currentIndex();
    ComboBoxdata mydata = ui->comboBox_10->itemData(index).value<ComboBoxdata>();
    QString indexstr=QString("%1").arg(mydata.index);
    ColumndataList.append(indexstr);
    index=ui->comboBox_9->currentIndex();
    mydata = ui->comboBox_9->itemData(index).value<ComboBoxdata>();
    indexstr=QString("%1").arg(mydata.index);
     ColumndataList.append(indexstr);
     index=ui->comboBox_11->currentIndex();
    //  indexstr=QString("%1").arg(index+1);
     mydata = ui->comboBox_11->itemData(index).value<ComboBoxdata>();
     indexstr=QString("%1").arg(mydata.index);
      ColumndataList.append(indexstr);

      QString logstr;
      QStringList list;
      list.append("操作日志");
    if(str=="新增")
    {
        pDbControl->searchCmdinsertData(ColumndataList);
        logstr=indexstr+": "+tr("新增查询命令 %1").arg(ui->lineEdit_9->text());
        list.append(logstr);
        pDbControl->loginsertData(list);
        if(insertsearchCmd==false)
           initsearchcmdDlg();
        else
        {
            QString sqlstr;
            qDeleteAll(searchcmdsetdlglist);
            searchcmdsetdlglist.clear();
            sqlstr="select b.`name` ,c.name,addr,num , cmd,label,a.id from instrumentsearch a ,instrument b ,factor c ,combo_box d where a.instrumentId=b.id and c.id=a.factorId and d.type='formula_type' and d.`value`=a.formulaId and b.name='"+ui->lineEdit->text()+"'";
            initdlg(sqlstr,ui->widgetPanel_14,"查询命令");
            insertsearchCmd=true;
        }
    }
    else if(str=="修改")
    {
          ColumndataList.append(ColumndataList.at(3));//
          ColumndataList.append(ColumndataList.at(4));//
          ColumndataList.removeAt(4);
          ColumndataList.removeAt(3);
          ColumnNameList<< "id" ;
          ColumndataList.append(ui->lineEdit_23->text());
          pDbControl->searchCmdupdateData(ColumnNameList,ColumndataList,6);

          logstr=indexstr+": "+tr("修改查询命令 %1").arg(ui->lineEdit_9->text());
          list.append(logstr);
          pDbControl->loginsertData(list);
          /* 设置显示对话框 */
         QString id= getsearchCmdId();
         QStringList namelist,datalist;
         namelist<<"仪器名" << "因子" <<"数据起始位" << "数据位数"<< "查询命令" << "计算公式";
         datalist.append(ui->comboBox_9->currentText());
           datalist.append( ui->comboBox_10->currentText());


         datalist.append(  ui->lineEdit_10->text());
         datalist.append(  ui->lineEdit_11->text());
           datalist.append( ui->lineEdit_9->text());
         datalist.append( ui->comboBox_11->currentText());

         setdlginfo(searchcmdsetdlglist,namelist,datalist,id);
    }
  //initSearchCmdQueryModel();

   // <<"仪器名" << "因子" << "查询命令"<<"数据起始位" << "数据位数" << "计算公式";

}
/**删除查询命令
 * @brief MainWindow::on_pushButton_25_clicked
 */
void MainWindow::on_pushButton_25_clicked()
{
  //  QStringList listdata= getTableViewRowData(ui->tableView_4,6) ;
    QStringList columndata, valuedata;
    columndata<<"id";
    valuedata.append(getsearchCmdId());
    QString str;
    str="你是否要删除"+getsearchCmdId()+"?";
   if(!getsearchCmdId().isEmpty())
   {
    if (helpclass.ShowMessageBox(str)) {
          pDbControl->searchCmddelete(columndata,valuedata);
       // initSearchCmdQueryModel();
          initsearchcmdDlg();
    }
   }
    else
    {
        helpclass.ShowoneMessageBox("请先选择一个查询命令");
    }
}

void MainWindow::on_pushButton_26_clicked()
{
    ui->pushButton_27->setText("新增");
}
/**串口设置接口
 * @brief MainWindow::on_pushButton_28_clicked
 */
void MainWindow::on_pushButton_28_clicked()
{

     QString str=ui->lineEdit_20->text();
     QStringList  ColumndataList,ColumnNameList;
     ColumnNameList<< "communicationType" << "comID" << "autoReadType"<<"id";//QStringList赋值
      ColumndataList.append(ui->comboBox_12->currentText());//接口类型
     int index=ui->comboBox_13->currentIndex();
     ComboBoxdata mydata = ui->comboBox_13->itemData(index).value<ComboBoxdata>();
     QString indexstr=QString("%1").arg(mydata.index);
     ColumndataList.append(indexstr);//串口号
     QString logstr;
     QStringList list;
     list.append("操作日志");
     if(ui->checkBox_3->isChecked())
         {
             ColumndataList.append("是");//adr  checkBox_3
          }
     else
         {
             ColumndataList.append("否");//adr  checkBox_3
          }
   // QStringList listdata= getTableViewRowData(ui->tableView_5,5) ;
    // if(listdata.size()>0)
    // {
       logstr=indexstr+": "+tr("通讯接口设置 %1").arg(ui->comboBox_13->currentText());
       list.append(logstr);
    // }
     pDbControl->loginsertData(list);
     ColumndataList.append(ui->lineEdit_20->text());//串口号
       pDbControl->instrumentupdateData(ColumnNameList,ColumndataList,3);

   // initinstrumentconnectDlg();
       /* 设置显示对话框 */
      QString id= getinstrumentconnectId();
      QStringList namelist,datalist;
      namelist<<"仪器名" << "通讯接口" << "串口号"<<"自动读取";
      datalist.append(  ui->lineEdit_34->text());
      datalist.append( ui->comboBox_12->currentText());
      datalist.append( ui->comboBox_13->currentText());
      if(ui->checkBox_3->isChecked())
         datalist.append( "是");
      else
           datalist.append( "否");
      setdlginfo(instrumentconnectsetdlglist,namelist,datalist,id);
      //initCommunicationQueryModel();
}
/**删除网络因子编码
 * @brief MainWindow::on_pushButton_31_clicked
 */
void MainWindow::on_pushButton_31_clicked()
{
    // QStringList listdata= getTableViewRowData(ui->tableView_6,4) ;
     QStringList columnname, valuedata;
     columnname<<"id";
     valuedata.append(getnetworkfactorId());
     QString str;
     if(!getnetworkfactorId().isEmpty())
     {
     str="你是否要删除id为"+getnetworkfactorId()+"的因子编码?";
    // QMessageBox::StandardButton r = QMessageBox::question(this, "警告", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
     if (helpclass.ShowMessageBox(str)) {
           pDbControl->netpoliddelete(columnname,valuedata);
        //initFactornetIDQueryModel();
           initnetworkfactorIdDlg(ui->comboBox_14->currentText());
     }
     }
     else
     {
         helpclass.ShowoneMessageBox("请先选择一个因子编码");
     }

}

void MainWindow::on_pushButton_30_clicked()
{
    ui->pushButton_29->setText("新增");
}
/**网络因子编码
 * @brief MainWindow::on_pushButton_29_clicked
 */
void MainWindow::on_pushButton_29_clicked()
{
       QString str=ui->pushButton_29->text();
       QStringList  ColumndataList,ColumnNameList;
       ColumnNameList<< "protocalId"<<"factorId" << "polId"<<"id" ;//QStringList
       int index=ui->comboBox_14->currentIndex();
       ComboBoxdata mydata = ui->comboBox_14->itemData(index).value<ComboBoxdata>();
       QString indexstr=QString("%1").arg(mydata.index);
       ColumndataList.append(indexstr);
       index=ui->comboBox_15->currentIndex();
       mydata = ui->comboBox_15->itemData(index).value<ComboBoxdata>();
        indexstr=QString("%1").arg(mydata.index);
       ColumndataList.append(indexstr);

       ColumndataList.append(ui->lineEdit_12->text());//똥왯뵀
       QString logstr;
       QStringList list;
       list.append("操作日志");

       if(str=="新增")
       {
           ColumnNameList.removeLast();
           pDbControl->netpolidinsertData(ColumndataList);

           logstr=tr("新增因子编码： %1").arg(indexstr);
           list.append(logstr);
           pDbControl->loginsertData(list);
       }
       else if(str=="修改")
       {
           ColumndataList.append(ui->lineEdit_21->text());

           pDbControl->netpolidupdateData(ColumnNameList,ColumndataList,3);

           logstr=tr("修改因子编码： %1").arg(indexstr);
           list.append(logstr);
           pDbControl->loginsertData(list);
       }
  //  initFactornetIDQueryModel();
       QString id=  getnetworkfactorId();
       QStringList namelist,datalist;
       namelist<<"协议名"<<"因子名" << "因子编码" ;
       datalist.append( ui->comboBox_14->currentText());
       datalist.append( ui->comboBox_15->currentText());
       datalist.append( ui->lineEdit_12->text());

       setdlginfo(networkfactorIdsetdlglist,namelist,datalist,id);


       initnetworkfactorIdDlg(ui->comboBox_14->currentText());


}
/**删除网络协议
 * @brief MainWindow::on_pushButton_33_clicked
 */
void MainWindow::on_pushButton_33_clicked()
{
   //QStringList listdata= getTableViewRowData(ui->tableView_7,10) ;
    QStringList columndata, valuedata;
    columndata<<"id";
    valuedata.append(getnetworkId());
    QString str;
    if(!getnetworkId().isEmpty())
    {
    str="你是否要删除协议id为"+getnetworkId()+"的协议?";
    //QMessageBox::StandardButton r = QMessageBox::question(this, "警告", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (helpclass.ShowMessageBox(str)) {
          pDbControl->networksetdelete(columndata,valuedata);
        //initNetWorkQueryModel();
          initnetworkDlg();
    }
    }
    else
    {
        helpclass.ShowoneMessageBox("请先选择网络协议");
    }

}

void MainWindow::on_pushButton_32_clicked()
{
   ui->pushButton_34->setText("新增");
}
/**网络协议修改
 * @brief MainWindow::on_pushButton_34_clicked
 */
void MainWindow::on_pushButton_34_clicked()
{
    QString str=ui->pushButton_34->text();
    QStringList  ColumndataList,ColumnNameList;
    ColumnNameList<< "protocol"<<"ip" << "port"<< "mn"<<"password" << "st"<<"sendFlag"<<"requestFlag"<<"id" ;//QStringList
    int index=ui->comboBox_17->currentIndex();
    ComboBoxdata mydata = ui->comboBox_17->itemData(index).value<ComboBoxdata>();
    QString indexstr=QString("%1").arg(mydata.index);
    ColumndataList.append(indexstr);
    ColumndataList.append(ui->lineEdit_13->text());
    ColumndataList.append(ui->lineEdit_14->text());
    ColumndataList.append(ui->lineEdit_15->text());
    ColumndataList.append(ui->lineEdit_16->text());
    ColumndataList.append(ui->lineEdit_17->text());

    QString logstr;
    QStringList list;
    list.append("操作日志");


    if(str=="新增")
    {
        ColumndataList.append("1");
        ColumndataList.append("1");
        ColumndataList.append("2019-01-05 00:00:00");
        ColumndataList.append("2019-01-05 00:00:00");
        ColumndataList.append(ui->lineEdit_18->text());
        ColumndataList.append(ui->lineEdit_19->text());
        ColumndataList.append("1");
        ColumnNameList.removeLast();
        pDbControl->networksetinsertData(ColumndataList);

        logstr=tr("新增网络协议： %1").arg(indexstr);
        list.append(logstr);
        pDbControl->loginsertData(list);
        initnetworkDlg();
    }
    else if(str=="修改")
    {
        ColumndataList.append(ui->lineEdit_18->text());
        ColumndataList.append(ui->lineEdit_19->text());
        ColumndataList.append(ui->lineEdit_22->text());

        pDbControl->networksetupdateData(ColumnNameList,ColumndataList,8);

        logstr=tr("修改网络协议： %1").arg(indexstr);
        list.append(logstr);
        pDbControl->loginsertData(list);
    }
//  initNetWorkQueryModel();
    QString id=  getnetworkId();
    QStringList namelist,datalist;
    namelist<<"协议名称" << "IP"<<"端口号" << "MN码"<<"密码"<<"ST" << "发送标记" << "回复标记"; ;
    datalist.append( ui->comboBox_17->currentText());
    datalist.append( ui->lineEdit_13->text());
    datalist.append( ui->lineEdit_14->text());
    datalist.append( ui->lineEdit_15->text());
    datalist.append( ui->lineEdit_16->text());
    datalist.append( ui->lineEdit_17->text());
    datalist.append( ui->lineEdit_18->text());
    datalist.append( ui->lineEdit_19->text());
    setdlginfo(networksetdlglist,namelist,datalist,id);
}
void  MainWindow::setnetworkId(QString id)
{
    networkId=id;
}
QString MainWindow:: getnetworkId()
{
    return networkId;
}
/**查询历史数据
 * @brief MainWindow::on_pushButton_35_clicked
 */
void MainWindow::on_pushButton_35_clicked()
{
    /*  QSqlQueryModel的使用主要用于多表查询  */
     // QStringList namestr;
      QStringList factorList,factorListId;
      QString sqlstr,tablename;
      QSqlQueryModel *querymodel;
      factorList=dbinstrumentclass.getSelectFactorList();
      factorListId=dbinstrumentclass.getSelectFactoridList();
     // sqlstr=dbinstrumentclass.getHistorySqlstr( factorList,"minutefactor");
      if(histroydatatypestr=="分钟数据")
         tablename="minutefactor";
      else if(histroydatatypestr=="5分钟数据")
      {
         tablename="5minutefactor";
      }
      else if(histroydatatypestr=="小时数据")
      {
          tablename="hourfactor";
      }
       sqlstr=dbinstrumentclass.getHistorySqlstrFromTime(factorListId,tablename,ui->dateEdit->text(),ui->dateEdit_2->text()+" 23:59:59");
       querymodel = new QSqlQueryModel;
       querymodel->setQuery(sqlstr);//这里直接设置SQL语句，忽略最后一个参数
       querymodel->setHeaderData(0, Qt::Horizontal, "时间");
       for(int i=0;i<factorList.size();i++)
       {
            querymodel->setHeaderData(i+1, Qt::Horizontal, factorList.at(i));
       }
       ui->tableView_8->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
       ui->tableView_8->setModel(querymodel);
}
/**用户列表
 * @brief MainWindow::on_tableView_15_clicked
 * @param index
 */
void MainWindow::on_tableView_15_clicked(const QModelIndex &index)
{
  /*  QStringList listdata= getTableViewRowData(ui->tableView_15,7) ;
     ui->lineEdit_28->setText(listdata.at(0));
    ui->lineEdit_24->setText(listdata.at(1));
    int comboBoxindex=ui->comboBox_19->findText(listdata.at(2));
    ui->comboBox_19->setCurrentIndex(comboBoxindex);
    ui->lineEdit_27->setText(listdata.at(3));

      ui->pushButton_41->setText("修改");
      */
}
/**
  新增用户名
 * @brief MainWindow::on_pushButton_42_clicked
 */
void MainWindow::on_pushButton_42_clicked()
{
    ui->pushButton_41->setText("新增");
}
/**密码初始化
 * @brief MainWindow::on_pushButton_43_clicked
 */
void MainWindow::on_pushButton_43_clicked()
{
   QStringList  ColumndataList,ColumnNameList;
    ColumnNameList << "password"<<"id" ;//QStringList
    // QStringList listdata= getTableViewRowData(ui->tableView_15,7) ;
     if(MainWindow::loginType=="管理员")
     {
           ColumndataList.append("123456");
           ColumndataList.append(getusersetId());
           if(!getusersetId().isEmpty())
             pDbControl->userupdateData(ColumnNameList,ColumndataList,1);
           else
           {
               helpclass.ShowoneMessageBox("请选择一个用户");
           }
     }

}
/**用户管理
 * @brief MainWindow::on_pushButton_41_clicked
 */
void MainWindow::on_pushButton_41_clicked()
{
    QString str=ui->pushButton_41->text();
    QStringList  ColumndataList,ColumnNameList;
    ColumnNameList<< "user"<<"type" << "password"<<"description"<<"id" ;//QStringList

    ColumndataList.append(ui->lineEdit_24->text());
    ColumndataList.append(ui->comboBox_19->currentText());
    ColumndataList.append(ui->lineEdit_25->text());
    ColumndataList.append(ui->lineEdit_27->text());
    if(ui->lineEdit_25->text()==ui->lineEdit_26->text())
    {
    if(str=="新增"&&MainWindow::loginType=="管理员")
    {
        ColumndataList.append(helpclass.currenttimetostr());
        ColumndataList.append(helpclass.currenttimetostr());
        ColumndataList.append(helpclass.currenttimetostr());
        pDbControl->userinsertData(ColumndataList);

    }
    else if(str=="修改"&&MainWindow::loginType=="管理员")
    {
           ColumndataList.append(ui->lineEdit_28->text());
           if(MainWindow::loginName==ui->lineEdit_24->text())
              pDbControl->userupdateData(ColumnNameList,ColumndataList,4);
           else
           {
              /*  QMessageBox msgBox(QMessageBox::NoIcon,QString::fromUtf8("提示"),"请确认修改的用户是否属于本次登录用户");

                 msgBox.setStyleSheet("QLabel {font:15px;color:#4d85db;}");
                 msgBox.addButton(QString::fromUtf8("确定"), QMessageBox::AcceptRole);
                 //msgBox.setText("请确认修改的用户是否属于本次登录用户");
                 msgBox.exec();*/
                helpclass.ShowoneMessageBox("请确认修改的用户是否属于本次登录用户");
           }

    }
    else
    {
      //  QMessageBox msgBox;
       /* QMessageBox msgBox(QMessageBox::NoIcon,QString::fromUtf8("提示"),"您未登录或用户权限不够");
        msgBox.setStyleSheet("QLabel {font:15px;color:#4d85db;}");
        msgBox.addButton(QString::fromUtf8("确定"), QMessageBox::AcceptRole);
        msgBox.exec();*/
        helpclass.ShowoneMessageBox("您未登录或用户权限不够");
    }
  //  initUserQueryModel();
  //  namestr<<"用户名" << "用户类型" << "描述" << "创建时间"<<"修改时间" << "最近登录时间";
    QString id=  getusersetId();
    QStringList namelist,datalist;
    namelist<<"用户名" << "用户类型" << "描述" ;
    datalist.append( ui->lineEdit_24->text());
    datalist.append( ui->comboBox_19->currentText());
    datalist.append( ui->lineEdit_27->text());

    setdlginfo(usersetdlglist,namelist,datalist,id);
    }
    else
    {
           // QMessageBox msgBox;
        /*    QMessageBox msgBox(QMessageBox::NoIcon,QString::fromUtf8("提示"),"请确认两次输入的密码是否一致");
            msgBox.setStyleSheet("QLabel {font:15px;color:#4d85db;}");
            msgBox.addButton(QString::fromUtf8("确定"), QMessageBox::AcceptRole);
            // msgBox.setText("请确认两次输入的密码是否一致");
             msgBox.exec();*/
        helpclass.ShowoneMessageBox("请确认两次输入的密码是否一致");
    }

}
/**删除用户
 * @brief MainWindow::on_pushButton_44_clicked
 */
void MainWindow::on_pushButton_44_clicked()
{
    //QStringList listdata= getTableViewRowData(ui->tableView_15,7) ;
    QStringList columnname, valuedata;
    columnname<<"id";
    valuedata.append(getusersetId());
    QString str;
    if(!getusersetId().isEmpty())
    {
    str="你是否要删除用户名为"+getusersetId()+"的用户?";
    //QMessageBox::StandardButton r = QMessageBox::question(this, "警告", str, QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(helpclass.ShowMessageBox(str)) {
          pDbControl->userdelete(columnname,valuedata);
       //initUserQueryModel();
          inituserDlg();
    }
    }
    else
    {
        helpclass.ShowoneMessageBox("请选择需要删除的用户");
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
/*    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#069dd5"));
    rectMove = QRect(0, 0, width(), 58);//目前暂时不绘制，需要绘制时加大高度即可
    painter.drawRect(rectMove);
    painter.setPen(QColor("#C0DCF2"));
    //painter.drawLine(0, 70, this->width(), 70);
    */
    QWidget::paintEvent(event);
}

/**日志查询
 * @brief MainWindow::on_pushButton_38_clicked
 */
void MainWindow::on_pushButton_38_clicked()
{
   // QSqlQueryModel *querymodel;
    QStringList namestr;
    QString sqlstr,starttime,endtime,typestr;
    starttime=ui->dateEdit_15->text();
    endtime=ui->dateEdit_16->text();
    typestr=logtypestr;
    //querymodel=new QSqlQueryModel(this);
    sqlstr="select dataTime,type,systemLog from log where dataTime BETWEEN ";
     sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+ "AND type="+"'"+ typestr+"'" +" GROUP BY dataTime";
       logquerymodel->setQuery(sqlstr);
     namestr<<"时间"<<"类型"<<"事件";
 for(int i=0;i<namestr.size();i++)
 {
    logquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
 }

    ui->tableView_17->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tableView_17->setModel(logquerymodel);
}
/**视频初始化
 * @brief MainWindow::initvideo
 */
void MainWindow::initvideo(bool show)
{
ui->axWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
ui->axWidget->setProperty("DisplayAlerts",false);//不显示警告信息
ui->axWidget->setProperty("DisplayScrollBars",true);//不显示滚动条
QString webstr=helpclass.getiniData("setting.ini","videosetting/ip");//设置要打开的网页
ui->lineEdit_30->setText(webstr);
if(show==true)
    ui->axWidget->dynamicCall("Navigate(const QString&)",webstr);//显示网页
else
    ui->axWidget->dynamicCall("Navigate(const QString&)","");//显示网页

}

void MainWindow::on_pushButton_2_clicked()
{
   helpclass.setiniData("setting.ini","videosetting/ip",ui->lineEdit_30->text()) ;

   QString str=ui->lineEdit_31->text();
   QByteArray responseData;
   responseData=str.toLatin1();
   str="";
    int size=responseData.size();
   for(int m=0;m<size;m++)
    {
                  responseData[m]=(responseData[m])^0x7b;
                  str=str+responseData[m];
    }
   helpclass.setiniData("setting.ini","instrumentctrl/password",str) ;
}

void MainWindow::on_navButton6_clicked()
{

}
/**得到指定行所有数据
 * @brief MainWindow::getTableViewRowData
 * @param TableView
 * @param row
 * @param columnCount
 * @return
 */
QStringList MainWindow::getTableViewRowData(QTableView *TableView,int row,int columnCount)
{
    QString tempstr;
    QStringList datalist;
   // int row=TableView->currentIndex().row();
    for(int i=0;i<columnCount;i++)
    {
        QAbstractItemModel *model =  TableView->model ();
        QModelIndex index = model->index(row,i);
       QVariant  data = model->data(index);
       tempstr=data.toString();
       datalist.insert(i,tempstr);
    }
  return datalist;
}
/**导出CSV数据
 * @brief help::exportMsg
 * @param headtitleList  表头显示数据
 * @param querymodel    数据库查询模板
 * @param tableView    列表控件
 */
void MainWindow::exportMsg(QStringList headtitleList,QSqlQueryModel *querymodel,QTableView *tableView)
  {
     QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),

                                                 tr("Files (*.csv)"));
     if (fileName.isEmpty())
     return;
     //打开.csv文件
     QFile file(fileName);
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
         return;
   }
     QTextStream out(&file);
   /* 表头数据*/
    int column=headtitleList.size();
    for(int i=0;i<column;i++)
    {
        QString string = headtitleList.at(i);
        out << string << ",";// 写入文件
    }
 out << "\n";

     //获取表格内容
     int row=  querymodel->rowCount();//表格总行数
       column=querymodel->columnCount();
     for(int i = 0; i < row; i ++)
     {
       QStringList DataList=  getTableViewRowData(tableView,i,column);
       int count=DataList.size();
         for(int col = 0; col < count; col++)
        {
             QString string = DataList.at(col);
             out << string << ",";// 写入文件
         }
         out << "\n";
     }
     QString titlestr="导出数据成功,"+tr("信息已保存在%1！").arg(fileName);
     helpclass.ShowoneMessageBox(titlestr);
    // QMessageBox::information(this, tr("导出数据成功"), tr("信息已保存在%1！").arg(fileName), tr("确定"));
     file.close();
}


void MainWindow::on_pushButton_45_clicked()
{
    QStringList headtitleList;
    headtitleList=dbinstrumentclass.getSelectFactorList();
    headtitleList.insert(0,"时间");
    exportMsg(headtitleList,historyquerymodel,ui->tableView_8);
}

void MainWindow::on_tableView_8_clicked(const QModelIndex &index)
{
    int column =ui->tableView_8->currentIndex().column();
    int rowcount=0;
    QVector<double> valuedata,time;
    QStringList headlist;
    QDateTime tempdatetime;
    double tempdata,maxdata=0;
     if( column >0 )
     {
         QString tempstr;
             QAbstractItemModel *model = ui->tableView_8->model ();
             rowcount=model->rowCount();
        headlist=dbinstrumentclass.getSelectFactorList();
         for(int i=0;i<rowcount;i++)
         {
             QModelIndex index = model->index(i,column);
             QVariant  data = model->data(index);
             tempdata=data.toDouble();
             if(tempdata>maxdata)
                 maxdata=tempdata;
             valuedata.append(tempdata);
             index = model->index(i,0);
             tempstr = model->data(index).toString();
             tempstr=tempstr.left(tempstr.length()-4);
             tempstr.replace(10,1," ");
             tempdatetime=QDateTime::fromString(tempstr,"yyyy-MM-dd hh:mm:ss");
             time.append((double)tempdatetime.toTime_t());
         }
         ui->histroyPlot->xAxis->setRange(time.at(0), time.at(time.size()-1));
         ui->histroyPlot->yAxis->setRange(0, maxdata*1.1);
         // qCPTextElement->setData(time, valuedata);
         graph1->setData(time, valuedata);
        // ui->histroyPlot->graph()->setName(headlist.at(column-1));
         qCPTextElement->setText(headlist.at(column-1));
         ui->histroyPlot->replot();
     }

}
/**历史数据初始化
 * @brief MainWindow::historyinitdraw
 */
void MainWindow::historyinitdraw()
{
//ui->customPlot->axisRect()->setBackground(QPixmap("./solarpanels.jpg"));

     qCPTextElement=new QCPTextElement(ui->histroyPlot, "小时数据", QFont("sans", 12, QFont::Bold));
    QDateTime dt = QDateTime::currentDateTime();
    ui->histroyPlot->showTracer(true);
    int key=dt.toTime_t();

    // 设置画布渐变色 /
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(242, 249, 255));
    plotGradient.setColorAt(1, QColor(218, 239, 255));
    ui->histroyPlot->setBackground(plotGradient);
  //  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
   // timeTicker->setTimeFormat("%y-%M-%d %h");
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
 dateTicker->setDateTimeFormat("yy-MM-dd hh");//
  graph1=ui->histroyPlot->addGraph();
  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 5));
  ui->histroyPlot->graph()->setLineStyle(QCPGraph::lsLine);
//setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));

// set data:
// set title of plot:
ui->histroyPlot->plotLayout()->insertRow(0);
ui->histroyPlot->plotLayout()->addElement(0, 0,qCPTextElement );

// axis configurations:
ui->histroyPlot->xAxis->setLabel("时间");
ui->histroyPlot->yAxis->setLabel("数值");
//ui->histroyPlot->xAxis2->setVisible(true);
//ui->histroyPlot->yAxis2->setVisible(true);


ui->histroyPlot->xAxis->setRange(key, key+36000);
ui->histroyPlot->yAxis->setRange(0, 52);
// setup legend:

//ui->histroyPlot->legend->setFont(QFont(font().family(), 7));
//ui->histroyPlot->legend->setIconSize(50, 20);
//ui->histroyPlot->legend->setVisible(true);
ui->histroyPlot->xAxis->setTicker(dateTicker);
//connect(ui->histroyPlot,&QCustomPlot::mouseMove,this,&MainWindow::myMoveEvent);


}
/*
void MainWindow::myMoveEvent(QMouseEvent *event)
{

    double x = event->pos().x();
    double y = event->pos().y();
   double _x=0,_y=0;
    for(int i = 0;i<ui->histroyPlot->xAxis->graphs().count();i++)
        {

            _x = ui->histroyPlot->graph(0)->data().data()->at(i)->key;
            _y = ui->histroyPlot->graph(0)->data().data()->at(i)->value;
            if(x-_x<5&&x-_x>-5&&y-_y>-5&&y-_y<5)
                break;
        }

    double x_ = ui->histroyPlot->xAxis->pixelToCoord(_x);
    double y_ = ui->histroyPlot->yAxis->pixelToCoord(_y);



    QString str = QString("x:%1,y:%2\n"
                          "滚轮滚动放大缩小\n"
                          "鼠标拖拽移动位置").arg(QString::number(x_,10,3))
            .arg(QString::number(y_,10,3));

    QToolTip::showText(cursor().pos(),str,ui->histroyPlot);
}
*/

/**登录窗口
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    if(!loginName.isEmpty())
    {
       loginName="";
       loginType="";
        ui->pushButton->setStyleSheet(tr("background-image: url(:/image/Landing.png);"));
        ui->btnHelp->hide();
    }
     else
    {
        loginDlg *dlg=new loginDlg();
        dlg->exec();
        if(!loginName.isEmpty())
        {
                ui->pushButton->setStyleSheet(tr("background-image: url(:/image/注销.png);"));
                if(loginType=="管理员")
                {
                    ui->btnHelp->show();
                }
                else
                {
                    ui->btnHelp->hide();
                }
        }
    }


}

void MainWindow::on_pushButton_3_clicked()
{
    if(!loginName.isEmpty())
    {
        QString str="你是否需要退出软件？";
        if(helpclass.ShowMessageBox(str))
        {
            QString logstr;
            QStringList list;
            list.append("系统日志");
            logstr=tr("系统退出 %1").arg(loginName);
            list.append(logstr);
            pDbControl->loginsertData(list);
            this->close();
        }

    }
    else
    {
        helpclass.ShowoneMessageBox("只有登录用户才允许退出软件");
    }

}



void MainWindow::on_pushButton_5_clicked()
{
    /*QString logstr;
    QStringList list;
    list.append(ui->lineEdit_33->text());
    logstr=ui->textEdit_3->toPlainText();
    list.append(logstr);
    pDbControl->maintaininsertData(list);
    on_pushButton_40_clicked();
    */
    ui->tabWidget_System->setCurrentIndex(0);
    ui->tabWidget_System->setTabEnabled(0, true);
    ui->tabWidget_5->setCurrentIndex(1);
    ui->tabWidget_5->setTabEnabled(1, true);
    ui->listView_2->show();
    ui->pushButton_5->hide();
}

void MainWindow::on_pushButton_40_clicked()
{

    QString sqlstr,starttime,endtime;
    starttime=ui->dateEdit_17->text();
    endtime=ui->dateEdit_18->text();
    sqlstr="select dataTime,personnel,systemLog from maintain where dataTime BETWEEN ";
    sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+" GROUP BY dataTime";
    maintainquerymodel->setQuery(sqlstr);

}
/*
void MainWindow::on_pushButton_9_clicked()
{
    int i=2;
    ui->tabWidget_2->setCurrentIndex(i);
    ui->tabWidget_2->setTabEnabled(i, true);
}

void MainWindow::on_pushButton_11_clicked()
{
    int i=3;
    ui->tabWidget_2->setCurrentIndex(i);
    ui->tabWidget_2->setTabEnabled(i, true);
}*/
/**日志查询
 * @brief MainWindow::on_pushButton_47_clicked
 */
void MainWindow::on_pushButton_47_clicked()
{
   // QSqlQueryModel *querymodel;
    QStringList namestr;
    QString sqlstr,starttime,endtime,typestr;
    starttime=ui->dateEdit_15->text();
    endtime=ui->dateEdit_16->text();
    typestr=logtypestr;
    //querymodel=new QSqlQueryModel(this);
    sqlstr="select dataTime,type,systemLog from log where dataTime BETWEEN ";
     sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+ "AND type="+"'"+ typestr+"'" +" GROUP BY dataTime";
       logquerymodel->setQuery(sqlstr);
     namestr<<"时间"<<"类型"<<"事件";
 for(int i=0;i<namestr.size();i++)
 {
    logquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
 }

    ui->tableView_17->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui->tableView_17->setModel(logquerymodel);
}

void  MainWindow::logsearch(QString typestr)
{
 // QSqlQueryModel *querymodel;
  QStringList namestr;
  QString sqlstr,starttime,endtime;
  starttime=ui->dateEdit_15->text();
  endtime=ui->dateEdit_16->text();

  //querymodel=new QSqlQueryModel(this);
  sqlstr="select dataTime,type,systemLog from log where dataTime BETWEEN ";
  sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+ "AND type="+"'"+ typestr+"'" +" GROUP BY dataTime";
  logquerymodel->setQuery(sqlstr);
   namestr<<"时间"<<"类型"<<"事件";
  for(int i=0;i<namestr.size();i++)
  {
    logquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
  }

  ui->tableView_17->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
  ui->tableView_17->setModel(logquerymodel);
}
/**维护日志查询
 * @brief MainWindow::on_pushButton_50_clicked
 */
void MainWindow::on_pushButton_50_clicked()
{
    QString sqlstr,starttime,endtime;
    starttime=ui->dateEdit_17->text();
    endtime=ui->dateEdit_18->text();
    sqlstr="select dataTime,personnel,systemLog from maintain where dataTime BETWEEN ";
    sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'"+" GROUP BY dataTime";
    maintainquerymodel->setQuery(sqlstr);
}

void MainWindow::on_pushButton_49_clicked()
{
    QString logstr;
    QStringList list;
    list.append(ui->lineEdit_33->text());
    logstr=ui->textEdit_3->toPlainText();
    list.append(logstr);
    pDbControl->maintaininsertData(list);
    on_pushButton_50_clicked();
}
/*
void MainWindow::on_pushButton_7_clicked()
{
    int i=0;
    ui->tabWidget_2->setCurrentIndex(i);
    ui->tabWidget_2->setTabEnabled(i, true);
   ui->pushButton_7->setChecked(true);
}

void MainWindow::on_pushButton_8_clicked()
{
    int i=1;
    ui->tabWidget_2->setCurrentIndex(i);
    ui->tabWidget_2->setTabEnabled(i, true);
    ui->pushButton_8->setChecked(true);
}
*/

void  MainWindow::initListview()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    QStringList qss;
    qss.append("QLabel#labTitle{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2AA2DA, stop:1 #12B5C9);color:#F0F0F0;}");
    qss.append("QWidget#widgetTop{background:#FFFFFF;}");
    qss.append("QWidget#widgetMain{background:#F1F3F6;}");
  //  qss.append("QLabel#label{color:#202020;font:50pt;}");
    qss.append("QListView#listView{background:rgb(52,73,94);border-width:0px;}");
    this->setStyleSheet(qss.join(""));
QStringList listItem;



listItem.append("数据查询||0|");
listItem.append("分钟数据|数据查询||");
listItem.append("5分钟数据|数据查询||");
listItem.append("小时数据|数据查询||");


listItem.append("报警数据||0|");
listItem.append("超标报警|报警数据||");
listItem.append("网络报警|报警数据||");

listItem.append("日志查询||0|");
listItem.append("系统日志|日志查询||");
listItem.append("网络日志|日志查询||");
listItem.append("操作日志|日志查询||");


 listItem.append("维护日志||1|");
ui->listView->setData(listItem);
ui->listView->setColorLine(QColor(225, 225, 225));
ui->listView->setColorBgNormal(QColor(130, 175, 234));
ui->listView->setColorBgHover(QColor(24, 189, 155));
ui->listView->setColorBgSelected(QColor(248, 250, 251));
ui->listView->setColorTextNormal(QColor(250, 250, 250));
ui->listView->setColorTextHover(QColor(0, 0, 0));
ui->listView->setColorTextSelected(QColor(77, 133, 219));

//ui->listView->setStyleSheet("border: 0px;background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #4d85db,stop:1 #6099e5)");//设置背景渐变色
ui->listView->setStyleSheet("border: 0px;background-color: #82AEEA");//设置背景渐变色 border: 0px;


QStringList listItem_2;
//listItem_2.append("主界面||0|");

listItem_2.append("仪器设置||0|");
listItem_2.append("因子设置|仪器设置||");
listItem_2.append("仪器设置|仪器设置||");
listItem_2.append("质控设置|仪器设置||");
listItem_2.append("控制命令|仪器设置||");
listItem_2.append("查询命令|仪器设置||");
listItem_2.append("串口设置|仪器设置||");

listItem_2.append("网络设置||0|");
listItem_2.append("网络协议|网络设置||");
listItem_2.append("因子编码|网络设置||");
listItem_2.append("其他设置|网络设置||");


listItem_2.append("用户设置||1|");

ui->listView_2->setData(listItem_2);
ui->listView_2->setColorLine(QColor(225, 225, 225));
//ui->listView_2->setColorBgNormal(QColor(107, 153, 225));
ui->listView_2->setColorBgNormal(QColor(130, 175, 234));

ui->listView_2->setColorBgHover(QColor(24, 189, 155));
ui->listView_2->setColorBgSelected(QColor(248, 250, 251));
ui->listView_2->setColorTextNormal(QColor(250, 250, 250));
ui->listView_2->setColorTextHover(QColor(0, 0, 0));
ui->listView_2->setColorTextSelected(QColor(77, 133, 219));

//ui->listView_2->setStyleSheet("border: 0px;background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #6090DD,stop:1 #82AEEA)");//设置背景渐变色
ui->listView_2->setStyleSheet("border: 0px;background-color: #82AEEA");//设置背景渐变色 border: 0px;
}

void  MainWindow::historysearch(QString typestr)
{
QStringList factorList,factorListId;
QString sqlstr,tablename;
QSqlQueryModel *querymodel;
factorList=dbinstrumentclass.getSelectFactorList();
factorListId=dbinstrumentclass.getSelectFactoridList();
// sqlstr=dbinstrumentclass.getHistorySqlstr( factorList,"minutefactor");
if( typestr=="分钟数据")
   tablename="minutefactor";
else if( typestr=="5分钟数据")
{
   tablename="5minutefactor";
}
else if( typestr=="小时数据")
{
    tablename="hourfactor";
}
 sqlstr=dbinstrumentclass.getHistorySqlstrFromTime(factorListId,tablename,ui->dateEdit->text(),ui->dateEdit_2->text()+" 23:59:59");
 querymodel = new QSqlQueryModel;
 querymodel->setQuery(sqlstr);//这里直接设置SQL语句，忽略最后一个参数
 querymodel->setHeaderData(0, Qt::Horizontal, "时间");
 for(int i=0;i<factorList.size();i++)
 {
      querymodel->setHeaderData(i+1, Qt::Horizontal, factorList.at(i));
 }
 ui->tableView_8->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
 ui->tableView_8->setModel(querymodel);
 }
void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    QString str=index.data().toString();
    if(str=="系统日志")
    {
        logsearch(str);
        ui->tabWidget_2->setCurrentIndex(2);
        ui->tabWidget_2->setTabEnabled(2, true);
        logtypestr="系统日志";
    }
   else if(str=="网络日志")
    {
        ui->tabWidget_2->setCurrentIndex(2);
        ui->tabWidget_2->setTabEnabled(2, true);
        logsearch(str);
        logtypestr="网络日志";
    }
    else if(str=="操作日志")
    {
        ui->tabWidget_2->setCurrentIndex(2);
        ui->tabWidget_2->setTabEnabled(2, true);
        logsearch(str);
        logtypestr="操作日志";
    }

    else if(str=="分钟数据")
    {
        ui->tabWidget_2->setCurrentIndex(0);
        ui->tabWidget_2->setTabEnabled(0, true);

       historysearch(str);
        ui->histroyPlot->setVisible(false);
    }
    else if(str=="5分钟数据")
    {
        ui->tabWidget_2->setCurrentIndex(0);
        ui->tabWidget_2->setTabEnabled(0, true);
        historysearch(str);
         ui->histroyPlot->setVisible(false);
    }
    else if(str=="小时数据")
    {
        ui->tabWidget_2->setCurrentIndex(0);
        ui->tabWidget_2->setTabEnabled(0, true);
       historysearch(str);
         ui->histroyPlot->setVisible(true);
    }
    else if(str=="超标报警")
    {
        ui->tabWidget_2->setCurrentIndex(1);
        ui->tabWidget_2->setTabEnabled(1, true);
    }
    else if(str=="网络报警")
    {
        ui->tabWidget_2->setCurrentIndex(1);
        ui->tabWidget_2->setTabEnabled(1, true);
    }
    else if(str=="维护日志")
    {
        ui->tabWidget_2->setCurrentIndex(3);
        ui->tabWidget_2->setTabEnabled(3, true);
    }

}


void MainWindow::on_listView_2_pressed(const QModelIndex &index)
{

    QString str=index.data().toString();
    if(str=="因子设置")
    {
        logsearch(str);
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(0);
        ui->tabWidget_5->setTabEnabled(0, true);
    }
   else if(str=="仪器设置")
    {
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(1);
        ui->tabWidget_5->setTabEnabled(1, true);
        logsearch(str);

    }
    else if(str=="质控设置")
    {
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(2);
        ui->tabWidget_5->setTabEnabled(2, true);
        logsearch(str);
    }
    else if(str=="控制命令")
    {
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(3);
        ui->tabWidget_5->setTabEnabled(3, true);
        logsearch(str);
    }
    else if(str=="查询命令")
    {
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(4);
        ui->tabWidget_5->setTabEnabled(4, true);
      // historysearch(str);
        ui->pushButton_5->hide();
        if(insertsearchCmd==true)
        {
           initsearchcmdDlg();
           insertsearchCmd=false;
        }
    }
    else if(str=="串口设置")
    {
        ui->tabWidget_System->setCurrentIndex(0);
        ui->tabWidget_System->setTabEnabled(0, true);
        ui->tabWidget_5->setCurrentIndex(5);
        ui->tabWidget_5->setTabEnabled(5, true);
       // historysearch(str);
    }
    else if(str=="网络协议")
    {
        ui->tabWidget_System->setCurrentIndex(1);
        ui->tabWidget_System->setTabEnabled(1, true);
        ui->tabWidget_4->setCurrentIndex(0);
        ui->tabWidget_4->setTabEnabled(0, true);
      // historysearch(str);
    }
    else if(str=="因子编码")
    {
        ui->tabWidget_System->setCurrentIndex(1);
        ui->tabWidget_System->setTabEnabled(1, true);
        ui->tabWidget_4->setCurrentIndex(1);
        ui->tabWidget_4->setTabEnabled(1, true);
    }
    else if(str=="其他设置")
    {
        ui->tabWidget_System->setCurrentIndex(1);
        ui->tabWidget_System->setTabEnabled(1, true);
        ui->tabWidget_4->setCurrentIndex(2);
        ui->tabWidget_4->setTabEnabled(2, true);
    }
    else if(str=="用户设置")
    {
        ui->tabWidget_System->setCurrentIndex(2);
        ui->tabWidget_System->setTabEnabled(2, true);
    }

}

void MainWindow::on_navButton1_clicked()
{

}

void MainWindow::on_tableView_9_clicked(const QModelIndex &index)
{
  /*  QStringList listdata= getTableViewRowData(ui->tableView_9,3) ;
    ui->lineEdit_32->setText(listdata.at(0));
    ui->lineEdit_35->setText(listdata.at(1));

    int comboBoxindex=ui->comboBox_20->findText(listdata.at(2));
    ui->comboBox_20->setCurrentIndex(comboBoxindex);
    ui->pushButton_4->setText("修改");
    */
}

void MainWindow::on_pushButton_4_clicked()
{
    QStringList ColumnNameList,ColumndataList,list;
    QString logstr;
    ColumnNameList<<"mode"<<"id";
    ColumndataList.append(ui->comboBox_20->currentText());
    ColumndataList.append(ui->lineEdit_32->text());//
    pDbControl->instrumentupdateData(ColumnNameList,ColumndataList,1);
    logstr=tr("修改仪器 %1").arg(ui->lineEdit_35->text());
    list.append(logstr);
    pDbControl->loginsertData(list);
    initinstrumentmodeQueryModel();
    pinstrumentManage->settestmode(ui->lineEdit_35->text(),ui->comboBox_20->currentIndex());

   QStyledItemDelegate *delegate = new QStyledItemDelegate(this);
   ui->comboBox_20->setItemDelegate(delegate);

   //  ui->comboBox_20->setView(QListView());
   // ui->comboBox_20->setStyleSheet("QComboBox QAbstractItemView {border:1px solid #dddddd;outline:0px;height:50px;	} QComboBox QAbstractItemView::item {min-height: 30px;background-color: rgb(255, 255, 255);color:#333;padding-left:11px;outline:0px;} QComboBox QAbstractItemView::item:hover {color:#333;background-color: #e9f2ff;}");

  /* 设置显示对话框 */
 QString id= getqueryId();
 QStringList namelist,datalist;
 namelist<<"仪器名" << "仪器模式"  ;
 //datalist.append( ui->lineEdit_32->text());
 datalist.append( ui->lineEdit_35->text());
 datalist.append( ui->comboBox_20->currentText());
 setdlginfo(qualitysetdlglist,namelist,datalist,id);

}

void MainWindow::on_pushButton_46_clicked()
{
    QStringList headtitleList;
    headtitleList<<"时间"<<"描述"<<"数值"<<"单位"<<"下限"<<"上限"<<"类型";
    exportMsg(headtitleList,alarmquerymodel,ui->tableView_10);
}

void MainWindow::on_pushButton_51_clicked()
{
    QStringList headtitleList;
    headtitleList<<"时间"<<"类型"<<"事件";
    //headtitleList.insert(0,"时间");
    exportMsg(headtitleList,logquerymodel,ui->tableView_17);
}

void MainWindow::on_pushButton_52_clicked()
{
    QStringList headtitleList;
   headtitleList<<"时间"<<"操作人员"<<"维修事件";
    //headtitleList.insert(0,"时间");
    exportMsg(headtitleList,maintainquerymodel,ui->tableView_18);
}

void MainWindow::on_pushButton_37_clicked()
{
    QStringList namestr;
    QString sqlstr;
   QString starttime=ui->dateEdit_5->text();
   QString endtime=ui->dateEdit_6->text();
    sqlstr="select * from alarm where data_Date BETWEEN ";
    sqlstr=sqlstr+"'" +starttime+"'"+" AND "+"'" +endtime+"'" +" GROUP BY data_Date";
      alarmquerymodel->setQuery(sqlstr);
     namestr<<"时间"<<"描述"<<"数值"<<"单位"<<"下限"<<"上限"<<"类型";
    for(int i=0;i<namestr.size();i++)
    {
         alarmquerymodel->setHeaderData(i, Qt::Horizontal, namestr.at(i));
    }

    ui->tableView_10->setModel( alarmquerymodel);
}
  void MainWindow:: setfactorId(QString id)
  {
      factorId=id;
  }
   QString  MainWindow::getfactorId()
   {
       return factorId;
   }
   QString MainWindow:: getinstrumentId()
   {
        return instrumentId;
   }
   void MainWindow::setinstrumentId(QString id)
   {
       instrumentId=id;
   }
/**子窗口曹函数处理 窗体间通讯
  * @brief MainWindow::infoRecv
  * @param datainfomaptemp
  */
 void  MainWindow::infoRecv(datainfomap datainfomaptemp,QString type,QString id)
 {
   //<<"名称"<<"单位"<<"最大值"<<"最小值"<<"精度"<<"显示"<<"转换系数"<<"上传";
       int index=0;
       QString name;
       QMapIterator<QString ,datainfo> i(datainfomaptemp);
       while (i.hasNext())
       {
            i.next();
            if(index>=MAX_UNIT)
                break;
              name=i.value().name;
            if(type=="因子")
            {
                ui->pushButton_21->setText("修改");
                setfactorId(id);
                setdlginfoselect(factorsetdlglist, id);
               if(i.value().datatype!=3)
               {

                    if(name=="名称")
                    {
                        ui->lineEdit_4->setText(i.value().data);
                    }
                    else if(name=="单位")
                    {
                        int comboBoxindex=ui->comboBox_5->findText(i.value().data);
                        ui->comboBox_5->setCurrentIndex(comboBoxindex);
                    }
                    else if(name=="最大值")
                    {
                            ui->lineEdit_6->setText(i.value().data);
                    }
                    else if(name=="最小值")
                    {
                            ui->lineEdit_5->setText(i.value().data);
                    }
                    else if(name=="精度")
                    {
                        int comboBoxindex=ui->comboBox_6->findText(i.value().data);
                        ui->comboBox_6->setCurrentIndex(comboBoxindex);
                    }
                    else if(name=="显示")
                    {
                          if(i.value().data=="显示")
                          {
                              ui->checkBox->setChecked(true);
                          }
                          else
                              ui->checkBox->setChecked(false);
                    }
                    else if(name=="转换系数")
                    {
                        ui->lineEdit_7->setText(i.value().data);
                    }
                    else if(name=="上传")
                    {
                        if(i.value().data=="上传")
                        {
                            ui->checkBox_2->setChecked(true);
                        }
                        else
                            ui->checkBox_2->setChecked(false);
                    }
                }

            }
            else if(type=="仪器")
            {
                ui->pushButton_18->setText("修改");
                setinstrumentId(id);
                setdlginfoselect(instrumentsetdlglist, id);
                if(name=="仪器名")
                {
                    ui->lineEdit->setText(i.value().data);
                }
                else if(name=="类型")
                {
                    int comboBoxindex=ui->comboBox->findText(i.value().data);
                    ui->comboBox->setCurrentIndex(comboBoxindex);
                }
                else if(name=="本站点仪器")
                {
                    int comboBoxindex=ui->comboBox_21->findText(i.value().data);
                    ui->comboBox_21->setCurrentIndex(comboBoxindex);
                }
                else if(name=="波特率")
                {
                    int comboBoxindex=ui->comboBox_2->findText(i.value().data);
                    ui->comboBox_2->setCurrentIndex(comboBoxindex);
                }
                else if(name=="校验")
                {
                    int comboBoxindex=ui->comboBox_3->findText(i.value().data);
                    ui->comboBox_3->setCurrentIndex(comboBoxindex);
                }
                else if(name=="停止位")
                {
                    int comboBoxindex=ui->comboBox_4->findText(i.value().data);
                    ui->comboBox_4->setCurrentIndex(comboBoxindex);
                }
                if(name=="端口号")
                {
                    ui->lineEdit_3->setText(i.value().data);
                }
                if(name=="IP")
                {
                    ui->lineEdit_2->setText(i.value().data);
                }

            }
            else if(type=="质控")
            {
                ui->pushButton_4->setText("修改");
                setqueryId(id);
                 setdlginfoselect(qualitysetdlglist, id);

                    ui->lineEdit_32->setText(id);
                 if(name=="仪器名")
                {
                    ui->lineEdit_35->setText(i.value().data);
                }
                if(name=="仪器模式")
                {
                    int comboBoxindex=ui->comboBox_20->findText(i.value().data);
                    ui->comboBox_20->setCurrentIndex(comboBoxindex);
                }

            }//namelist<<"仪器id"<<"仪器名" << "通讯接口" << "串口号";
            else if(type=="串口设置")
            {
                 ui->pushButton_28->setText("修改");
                 setinstrumentconnectId(id);
                 ui->lineEdit_20->setText(id);
                 setdlginfoselect(instrumentconnectsetdlglist, id);
                if(name=="仪器名")
                 {
                     ui->lineEdit_34->setText(i.value().data);
                 }
                 else if(name=="通讯接口")
                 {
                     int comboBoxindex=ui->comboBox_12->findText(i.value().data);
                     ui->comboBox_12->setCurrentIndex(comboBoxindex);
                 }
                 else if(name=="串口号")
                 {
                     int comboBoxindex=ui->comboBox_13->findText(i.value().data);
                     ui->comboBox_13->setCurrentIndex(comboBoxindex);
                 }
                else if(name=="自动读取")
                {
                    if(i.value().data=="是")
                      ui->checkBox_3->setChecked(true);
                    else
                        ui->checkBox_3->setChecked(false);
                }
            }// namelist<<"命令ID"<<"仪器名" << "因子" << "查询命令"<<"数据起始位" << "数据位数" << "计算公式";
            else if(type=="查询命令")
            {
                 ui->pushButton_27->setText("修改");
                    setsearchCmdId(id);
                     ui->lineEdit_23->setText(id);
                   setdlginfoselect(searchcmdsetdlglist, id);
                 if(name=="仪器名")
                 {
                     int comboBoxindex=ui->comboBox_9->findText(i.value().data);
                     ui->comboBox_9->setCurrentIndex(comboBoxindex);
                 }
                 if(name=="因子")
                 {
                     int comboBoxindex=ui->comboBox_10->findText(i.value().data);
                     ui->comboBox_10->setCurrentIndex(comboBoxindex);
                 }
                 if(name=="查询命令")
                 {
                     ui->lineEdit_9->setText(i.value().data);
                 }
                 else if(name=="数据起始位")
                 {
                  ui->lineEdit_10->setText(i.value().data);
                 }
                 if(name=="数据位数")
                 {
                     ui->lineEdit_11->setText(i.value().data);
                 }
                 if(name=="计算公式")
                 {
                     int comboBoxindex=ui->comboBox_11->findText(i.value().data);
                     ui->comboBox_11->setCurrentIndex(comboBoxindex);
                 }
            }
            else if(type=="控制命令")//namelist<<"命令id"<<"仪器名" << "命令名称" << "命令";
            {
                setctrlCmdId(id);
                ui->pushButton_24->setText("修改");
                ui->lineEdit_29->setText(id);
                setdlginfoselect(ctrlcmdsetdlglist, id);
               if(name=="仪器名")
                {
                    int comboBoxindex=ui->comboBox_7->findText(i.value().data);
                    ui->comboBox_7->setCurrentIndex(comboBoxindex);
                }
                if(name=="命令名称")
                {
                    int comboBoxindex=ui->comboBox_8->findText(i.value().data);
                    ui->comboBox_8->setCurrentIndex(comboBoxindex);
                }
                if(name=="命令")
                {
                    ui->lineEdit_8->setText(i.value().data);
                }
            }
            else if(type=="网络协议")// 协议id<<"协议名称" << "IP"<<"端口号" << "MN码"<<"密码"<<"ST" << "发送标记" << "回复标记"<<"是否启用";
            {
                ui->pushButton_34->setText("修改");
                 setnetworkId(id);
                    ui->lineEdit_22->setText(id);
                 setdlginfoselect(networksetdlglist, id);
               if(name=="协议名称")
                {
                    int comboBoxindex=ui->comboBox_17->findText(i.value().data);
                    ui->comboBox_17->setCurrentIndex(comboBoxindex);
                }
                if(name=="IP")
                {
                    ui->lineEdit_13->setText(i.value().data);
                }
                if(name=="端口号")
                {
                    ui->lineEdit_14->setText(i.value().data);
                }
                else if(name=="MN码")
                {
                 ui->lineEdit_15->setText(i.value().data);
                }
                if(name=="密码")
                {
                    ui->lineEdit_16->setText(i.value().data);
                }
                if(name=="ST")
                {
                    ui->lineEdit_17->setText(i.value().data);
                }
                if(name=="发送标记")
                {
                    ui->lineEdit_18->setText(i.value().data);
                }
                if(name=="回复标记")
                {
                    ui->lineEdit_19->setText(i.value().data);
                }
                if(name=="是否启用")
                {

                }
            }
            else if(type=="网络因子编码")//  namestr<<"id"<<"协议名" << "因子名" << "因子编码";
            {
                setnetworkfactorId(id);
                 ui->pushButton_29->setText("修改");
                 ui->lineEdit_21->setText(id);
                  setdlginfoselect(networkfactorIdsetdlglist, id);
                 if(name=="因子名")
                {
                    int comboBoxindex=ui->comboBox_15->findText(i.value().data);
                    ui->comboBox_15->setCurrentIndex(comboBoxindex);
                }
                else if(name=="因子编码")
                {
                   ui->lineEdit_12->setText(i.value().data);
                }

            }
           else if(type=="用户管理")//  namestr<<"用户名" << "用户类型" << "描述" << "创建时间"<<"修改时间" << "最近登录时间";
            {
                setusersetId(id);
                 ui->pushButton_41->setText("修改");
                 ui->lineEdit_28->setText(id);
                  setdlginfoselect(usersetdlglist, id);
                 if(name=="用户名")
                {
                 ui->lineEdit_24->setText(i.value().data);
                }
                else if(name=="用户类型")
                {

                   int comboBoxindex=ui->comboBox_19->findText(i.value().data);
                   ui->comboBox_19->setCurrentIndex(comboBoxindex);
                }
                 else if(name=="描述")
                 {
                    ui->lineEdit_27->setText(i.value().data);
                 }
            }

       }
 }
 void MainWindow::setnetworkfactorId(QString id)
 {
     networkfactorId=id;
 }

 QString  MainWindow::getnetworkfactorId()
 {
    return networkfactorId;
 }

 void  MainWindow::setqueryId(QString id)
 {
    queryId=id;
 }
 QString  MainWindow:: getqueryId()
 {
     return queryId;
 }
 void  MainWindow::setctrlCmdId(QString id)
 {
     ctrlCmdId =id;
 }
 QString  MainWindow::getctrlCmdId()
 {
     return ctrlCmdId ;
 }
 QString  MainWindow:: getsearchCmdId()
 {

             return searchcmdId;
 }
 void  MainWindow:: setsearchCmdId(QString id)
 {
     searchcmdId=id;
 }
 QString  MainWindow::getinstrumentconnectId()
 {
     return instrumentconnectId;
 }
 void   MainWindow::setinstrumentconnectId(QString id)
 {
     instrumentconnectId=id;
 }
 QString   MainWindow::getusersetId()
 {
     return usersetId;
 }
 void   MainWindow::setusersetId(QString id)
 {
     usersetId=id;
 }
 void  MainWindow::comRecv(QString instrumentname,QString cmd)
 {
     startinstrumentCmd(instrumentname,cmd);
 }

void MainWindow::on_comboBox_14_currentTextChanged(const QString &arg1)
{

    initnetworkfactorIdDlg(arg1);
}
/**显示多参数因子
  * @brief MainWindow::showOtherfactor
  */
 void MainWindow::initOtherfactor()
 {
     MultipleParameters=helpclass.getiniData("setting.ini","otherfactorset/MultipleParameters");
     if(MultipleParameters=="open")
     {
     int i=0;
     scrollArea=new QScrollArea(ui->tab_9);
     scrollArea->setStyleSheet("QScrollArea{background:transparent;}"
                               "QScrollBar::vertical{background:#35A739;border:-5px solid grey;margin:-2px 0px 0px 0px;width:8px;}"
                               "QScrollBar::horizontal{background:#35A739;border:0px solid #126691;height:10px;}"
                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background:#D3D3D3;}"
                               );

     scrollArea->setFrameShape(QFrame::NoFrame);
     scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     scrollArea->setFocusPolicy(Qt::NoFocus);
    scrollArea->setStyleSheet("background:transparent");

     othorfactorwidget=new QWidget(scrollArea);
      scrollArea->setWidget(othorfactorwidget);
    // othorfactorwidget->show();
     othorfactorframe=new QFrame(othorfactorwidget);
     othorfactorframe->setStyleSheet("QFrame{border-image:url(:/image/set.png)}");
     //othorfactorframe->show();
     int columnnum=helpclass.getiniData("setting.ini","otherfactorset/columnnum").toInt();
     int row=helpclass.getiniData("setting.ini","otherfactorset/rownum").toInt();
     int width=helpclass.getiniData("setting.ini","otherfactorset/width").toInt();
     int high=helpclass.getiniData("setting.ini","otherfactorset/high").toInt();
     if(width<=0)
         width=200;
     if(high<=0)
         high=30;
     for( i=0;i<row;i++)
     for(int j=0;j<columnnum;j++)
     {
         QLabel *label=new QLabel(othorfactorwidget);
         label->setGeometry(80+j*width,high*i+20,width-20,high-10);
         label->setText("label");
         factordatalist.append(label);
          label->setStyleSheet("background:transparent");
         label->hide();
     }
     Othorfactorindex=i;
   }

 }
 /**显示多参数仪器的所有信息
   * @brief MainWindow::showOtherfactor
   */
  void MainWindow::showOtherfactor()
  {
      if(MultipleParameters=="open")
      {
          ui->btnMain_2->show();
      int labelnum=factordatalist.size();
      int i=0;
     int instrumentnum= pinstrumentManage->getinstrumentIndex();
     for(int j=0;j<instrumentnum;j++)
     {

      if(pinstrumentManage->m_ctrlInstrument[j]->getinstrumentinfo().type=="多参数")
      {
      QMapIterator<int,factorData> item(pinstrumentManage->m_ctrlInstrument[j]->getfactorDataMap());

      QString showstr;
      while(item.hasNext()&&i<FACTORDATA_MAX)
      {
         item.next();
        // QString factorstr;
         showstr=item.value().factorinfodata.name+":          ";
         if(item.value().factorinfodata.unit!="--")
         {
             if(i<labelnum)
             {
                 factordatalist.at(i)->setText(showstr+item.value().factorinfodata.unit);
             }
         }
         else
         {
             if(i<labelnum)
             {
                 factordatalist.at(i)->setText(showstr);
             }
         }
         factordatalist.at(i)->show();
       i++;

      }
      }
     }
      }
      else
      {
          ui->btnMain_2->hide();
      }

  }


 void MainWindow::resizeEvent(QResizeEvent *event)
 {
    initmulUI();
 }
 void MainWindow::initmulUI()
 {
     int high=helpclass.getiniData("setting.ini","otherfactorset/high").toInt();
     if(scrollArea!=NULL)
     {
          othorfactorwidget->resize(ui->tab_9->width()-30,Othorfactorindex*high+20);
          othorfactorframe->setGeometry(10, 10, ui->tab_9->width()-35, Othorfactorindex*high+20);
          scrollArea->setGeometry(10, 10, ui->tab_9->width()-11, ui->tab_9->height() -39);
     }
 }

