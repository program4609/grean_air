#ifndef QIXIANGDLG_H
#define QIXIANGDLG_H

#include <QWidget>

namespace Ui {
class qixiangdlg;
}

class qixiangdlg : public QWidget
{
    Q_OBJECT

public:
    explicit qixiangdlg(QWidget *parent = 0);
    ~qixiangdlg();

private:
    Ui::qixiangdlg *ui;
};

#endif // QIXIANGDLG_H
