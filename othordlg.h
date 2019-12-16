#ifndef OTHORDLG_H
#define OTHORDLG_H

#include <QWidget>

namespace Ui {
class Othordlg;
}

class Othordlg : public QWidget
{
    Q_OBJECT

public:
    explicit Othordlg(QWidget *parent = 0);
    ~Othordlg();

private:
    Ui::Othordlg *ui;
};

#endif // OTHORDLG_H
