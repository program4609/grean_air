#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QWidget>

namespace Ui {
class loginDlg;
}

class loginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = 0);
    ~loginDlg();

private:
    Ui::loginDlg *ui;
};

#endif // LOGINDLG_H
