#include "dialoginstrument.h"
#include "ui_dialoginstrument.h"

DialogInstrument::DialogInstrument(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInstrument)
{
    ui->setupUi(this);
}

DialogInstrument::~DialogInstrument()
{
    delete ui;
}
