#ifndef SETINFODLG_H
#define SETINFODLG_H

#include <QWidget>

namespace Ui {
class setinfoDlg;
}

class setinfoDlg : public QWidget
{
    Q_OBJECT

public:
    explicit setinfoDlg(QWidget *parent = 0);
    ~setinfoDlg();

private:
    Ui::setinfoDlg *ui;
};

#endif // SETINFODLG_H
