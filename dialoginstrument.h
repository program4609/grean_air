#ifndef DIALOGINSTRUMENT_H
#define DIALOGINSTRUMENT_H

#include <QDialog>

namespace Ui {
class DialogInstrument;
}

class DialogInstrument : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInstrument(QWidget *parent = 0);
    ~DialogInstrument();

private:
    Ui::DialogInstrument *ui;
};

#endif // DIALOGINSTRUMENT_H
