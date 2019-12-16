#include "logindlg.h"
#include "ui_logindlg.h"

loginDlg::loginDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
}

loginDlg::~loginDlg()
{
    delete ui;
}
