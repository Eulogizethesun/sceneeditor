#ifndef DIALOGLIGHTPOSITION_H
#define DIALOGLIGHTPOSITION_H

#include <QDialog>

namespace Ui {
class Dialoglightposition;
}

class Dialoglightposition : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoglightposition(QWidget *parent = 0);
    ~Dialoglightposition();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialoglightposition *ui;
};

#endif // DIALOGLIGHTPOSITION_H
