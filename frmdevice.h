#ifndef FRMDEVICE_H
#define FRMDEVICE_H

#include <QWidget>

namespace Ui {
class frmdevice;
}

class frmdevice : public QWidget
{
    Q_OBJECT

public:
    explicit frmdevice(QWidget *parent = 0);
    ~frmdevice();

private:
    Ui::frmdevice *ui;
};

#endif // FRMDEVICE_H
