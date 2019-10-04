#include "exportdialog.h"
#include "ui_exportdialog.h"
#include <QFile>
#include <QPushButton>
#include <vector>
#include <algorithm>
#include <functional>

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::setList(QListWidget *l)
{
    for(int i=0;i<l->count();i++)
    {
        ui->listWidget->addItem(l->item(i)->text());
    }
}

void ExportDialog::on_pushButton_explor_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save OBJ File"), "",
        tr("OBJ file (*.obj);;All Files (*)"));
    if (!fileName.isNull())
    {
        ui->lineEdit_path->setText(fileName);
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
    }
    else
    {
        //点的是取消
    }
}

void ExportDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button==ui->buttonBox->button(QDialogButtonBox::Save))
    {
        QFile file(ui->lineEdit_path->text());
        if (!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::information(this, "Error Message", "Please Select a Text File!");
            return;
        }
        QTextStream out(&file);
        std::vector<Vertex> vst;
        for(Vertex v:pool->vs)
        {
            vst.push_back(v);
            out<<"v "<<v.x<<" "<<v.y<<" "<<v.z<<"\r\n";
        }
        //std::vector<Vertex>::iterator index;
        for(Face f:pool->fs)
        {
            out<<"f ";
            for(int i=0;i<f.a.size();i++)
            {
                for(int j=0;j<vst.size();j++)
                {
                    if(vst.at(j).id==f.a.at(i)->id)
                    {
                        out<<j+1<<" ";
                    }
                }
            }
            out<<"\r\n";
        }
        accept();
    }
    else if(button == ui->buttonBox->button((QDialogButtonBox::Cancel)))
    {

    }
}
