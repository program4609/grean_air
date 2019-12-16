#include "frmdevice.h"
#include "ui_frmdevice.h"

frmdevice::frmdevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmdevice)
{
    ui->setupUi(this);
}

frmdevice::~frmdevice()
{
    delete ui;
}
