#-------------------------------------------------
#
# Project created by QtCreator 2019-05-10T09:18:28
#
#-------------------------------------------------
QT += widgets serialport
QT       += core gui
QT +=sql
QT += core
QT  +=  printsupport
QT       += network
QT += axcontainer
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grean_air
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    db\dbconnect.cpp \
    db\dbbase.cpp \
    db\dbminutefactor.cpp \
    db\dbalarm.cpp \
    db\dbcfg_user.cpp \
    db\dbcombo_box.cpp \
    db\dbhourfactor.cpp \
    db\dbfactor.cpp \
    db\dbfactorda.cpp \
    db\dbinstrument.cpp \
    db\dbinstrumentcmd.cpp \
    db\dbinstrumentsearch.cpp \
    db\dblog.cpp \
    db\dbnet212set.cpp \
    db\dbnetpolid.cpp \
    db\dbnetworkset.cpp \
    db\dbstationinfo.cpp \
    ctrlinstrument.cpp \
    factordata.cpp \
    db/dbfiveminutefactor.cpp \
    help.cpp \
    instrumentmanage.cpp \
    db\dbtempdata.cpp \
    qcustomplot.cpp \
    db/dbcontrol.cpp \
    tcpclient.cpp \
    navbutton.cpp \
    frmdevice.cpp \
    panelwidget.cpp \
    unit.cpp \
    logindlg.cpp \
    applive.cpp \
    dialoginstrument.cpp \
    db/maintain.cpp \
    navlistview.cpp \
    appinit.cpp \
    iconhelper.cpp \
    sliderbar.cpp \
    XxwCustomPlot.cpp \
    XxwTracer.cpp \
    info.cpp \
    othordlg.cpp \
    qixiangdlg.cpp \
    setinfodlg.cpp

HEADERS += \
        mainwindow.h \
    db\dbconnect.h \
    db\dbbase.h \
    db\dbminutefactor.h \
    db\dbalarm.h \
    db\dbcfg_user.h \
    db\dbcombo_box.h \
    db\dbhourfactor.h \
    db\dbfactor.h \
    db\dbfactorda.h \
    db\dbinstrument.h \
    db\dbinstrumentcmd.h \
    db\dbinstrumentsearch.h \
    db\dblog.h \
    db\dbnet212set.h \
    db\dbnetpolid.h \
    db\dbnetworkset.h \
    db\dbstationinfo.h \
    ctrlinstrument.h \
    factordata.h \
    db/dbfiveminutefactor.h \
    help.h \
    instrumentmanage.h \
    db\dbtempdata.h \
    qcustomplot.h \
    db/dbcontrol.h \
    tcpclient.h \
    navbutton.h \
    frmdevice.h \
    panelwidget.h \
    unit.h \
    logindlg.h \
    applive.h \
    dialoginstrument.h \
    db/maintain.h \
    navlistview.h \
    appinit.h \
    iconhelper.h \
    sliderbar.h \
    XxwCustomPlot.h \
    XxwTracer.h \
    info.h \
    othordlg.h \
    qixiangdlg.h \
    setinfodlg.h

FORMS += \
        mainwindow.ui \
    frmdevice.ui \
    unit.ui \
    logindlg.ui \
    dialoginstrument.ui \
    info.ui \
    othordlg.ui \
    qixiangdlg.ui \
    setinfodlg.ui

DISTFILES += \
    other/image/btn_real.png \
    other/image/btn_real_checked.png
RESOURCES   += other/main.qrc
RESOURCES += \
    other/qss.qrc \
    realtime.qrc
