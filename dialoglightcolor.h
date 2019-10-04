#ifndef DIALOGLIGHTCOLOR_H
#define DIALOGLIGHTCOLOR_H

#include <QDialog>

namespace Ui {
class Dialoglightcolor;
}

class Dialoglightcolor : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoglightcolor(QWidget *parent = nullptr);
    ~Dialoglightcolor();
private slots:
    void on_buttonBox_accepted();


private:
    Ui::Dialoglightcolor *ui;
};

#endif // DIALOGLIGHTCOLOR_H
