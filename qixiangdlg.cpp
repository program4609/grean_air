#include "qixiangdlg.h"
#include "ui_qixiangdlg.h"

qixiangdlg::qixiangdlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qixiangdlg)
{
    ui->setupUi(this);
}

qixiangdlg::~qixiangdlg()
{
    delete ui;
}
