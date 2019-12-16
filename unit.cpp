#include "unit.h"
#include "ui_unit.h"

unit::unit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unit)
{
    ui->setupUi(this);
}

unit::~unit()
{
    delete ui;
}
