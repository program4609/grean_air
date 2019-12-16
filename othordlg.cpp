#include "othordlg.h"
#include "ui_othordlg.h"

Othordlg::Othordlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Othordlg)
{
    ui->setupUi(this);
}

Othordlg::~Othordlg()
{
    delete ui;
}
