#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include "geoobjlist.h"
#include "geoobj.h"
#include "pool.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    void setList(QListWidget *l);
    explicit ExportDialog(QWidget *parent = 0);
    ~ExportDialog();
    Pool *pool;

private slots:
    void on_pushButton_explor_clicked();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ExportDialog *ui;
};

#endif // EXPORTDIALOG_H
