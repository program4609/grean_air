#include "setinfodlg.h"
#include "ui_setinfodlg.h"

setinfoDlg::setinfoDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setinfoDlg)
{
    ui->setupUi(this);
}

setinfoDlg::~setinfoDlg()
{
    delete ui;
}
