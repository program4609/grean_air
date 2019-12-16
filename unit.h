#ifndef UNIT_H
#define UNIT_H

#include <QWidget>

namespace Ui {
class unit;
}

class unit : public QWidget
{
    Q_OBJECT

public:
    explicit unit(QWidget *parent = 0);
    ~unit();

private:
    Ui::unit *ui;
};

#endif // UNIT_H
