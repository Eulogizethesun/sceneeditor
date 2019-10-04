#include "newgeoobjdialog.h"
#include "ui_newgeoobjdialog.h"
#include "geoobj.h"
#include <QPushButton>

NewGeoObjDialog::NewGeoObjDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGeoObjDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

NewGeoObjDialog::~NewGeoObjDialog()
{
    delete ui;
}

////////////////////////////////////////////////////////
// create dynamic widgets

void NewGeoObjDialog::on_radioButton_cube_clicked()
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("Side length (a)", txtSideLen = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_cuboid_clicked()
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("Base length (a)", txtBaseLen = new QLineEdit);
    form->addRow("Base width (b)", txtBaseWidth = new QLineEdit);
    form->addRow("Height (c)", txtHeight = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_sphere_clicked()
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("Radius (r)", txtRadius = new QLineEdit);
    form->addRow("X of center (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center (cz)", txtCenterZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_cylinder_clicked() // yuan zhu
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("radius of base (r)", txtRadius = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_cone_clicked() // yuan zhui
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("radius of base (r)", txtRadius = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_frustum_of_cone_clicked() // yuan tai
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("radius of lower base (r1)", txtLowerRadius = new QLineEdit);
    form->addRow("radius of upper base (r2)", txtUpperRadius = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("X of center of lower base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of lower base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of lower base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_prism_clicked() // leng zhu
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("Base length (a)", txtBaseLen = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("number (n)", txtNumber = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_pyramid_clicked() // leng tai
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("Base length (a)", txtBaseLen = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("number (n)", txtNumber = new QLineEdit);
    form->addRow("X of center of base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

void NewGeoObjDialog::on_radioButton_frustum_of_pyramid_clicked() // leng zhui
{
    clearDynamicWidgets();
    auto &form = ui->formLayout_param;
    form->addRow("side length of lower base (a1)", txtLowerSideLen = new QLineEdit);
    form->addRow("side length of upper base (a2)", txtUpperSideLen = new QLineEdit);
    form->addRow("height (h)", txtHeight = new QLineEdit);
    form->addRow("number (n)", txtNumber = new QLineEdit);
    form->addRow("X of center of lower base (cx)", txtCenterX = new QLineEdit);
    form->addRow("Y of center of lower base (cy)", txtCenterY = new QLineEdit);
    form->addRow("Z of center of lower base (cz)", txtCenterZ = new QLineEdit);
    form->addRow("X of outer-pointing normal of base (nx)", txtNormalX = new QLineEdit);
    form->addRow("Y of outer-pointing normal of base (ny)", txtNormalY = new QLineEdit);
    form->addRow("Z of outer-pointing normal of base (nz)", txtNormalZ = new QLineEdit);
    setLineEditValidators();
}

////////////////////////////////////////////////////////

GeoObj* NewGeoObjDialog::getGeoObj()
{
    //QButtonGroup bg = ui->buttonGroup_shape; // group of radio buttons
    GeoObj *obj ;
    if(ui->radioButton_cube->isChecked()) {
        double baseLen = txtSideLen->text().toDouble();
        obj = new Cuboid(baseLen, baseLen, baseLen,
                         txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                         txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());
    } else if(ui->radioButton_cuboid->isChecked()) {
        obj = new Cuboid(txtBaseLen->text().toDouble(), txtBaseWidth->text().toDouble(), txtHeight->text().toDouble(),
                         txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                         txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());
    } else if(ui->radioButton_sphere->isChecked()) {
        obj = new Sphere(txtRadius->text().toDouble(),
                         txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble());
    } else if(ui->radioButton_cylinder->isChecked()) {
        obj = new Cylinder(txtRadius->text().toDouble(),txtHeight->text().toDouble(),
                               txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                               txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());

    } else if(ui->radioButton_cone->isChecked()) {
        obj = new Cone(txtRadius->text().toDouble(),txtHeight->text().toDouble(),
                       txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                       txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());

    } else if(ui->radioButton_frustum_of_cone->isChecked()) {
        obj = new FrustumofCone(txtHeight->text().toDouble(),txtLowerRadius->text().toDouble(),txtUpperRadius->text().toDouble(),
                                txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                                txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());

    } else if(ui->radioButton_prism->isChecked()) {
        obj = new Prism(txtBaseLen->text().toDouble(), txtHeight->text().toDouble(), txtNumber->text().toDouble(),
                         txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                         txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());

    } else if(ui->radioButton_pyramid->isChecked()) {
        obj = new Pymarid(txtBaseLen->text().toDouble(), txtHeight->text().toDouble(), txtNumber->text().toDouble(),
                         txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                         txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());


    } else if(ui->radioButton_frustum_of_pyramid->isChecked()) {
        obj = new Frustum_of_pymarid(txtLowerSideLen->text().toDouble(),txtUpperSideLen->text().toDouble(),txtHeight->text().toDouble(),
                                txtNumber->text().toDouble(),
                                txtCenterX->text().toDouble(), txtCenterY->text().toDouble(), txtCenterZ->text().toDouble(),
                                txtNormalX->text().toDouble(), txtNormalY->text().toDouble(), txtNormalZ->text().toDouble());


    }
    return obj;
}


////////////////////////////////////////////////////////

void NewGeoObjDialog::clearDynamicWidgets()
{
    // delete each text field and clear the form layout
    auto &form = ui->formLayout_param;
    /*
    for (int i = 0; i < form->count(); ++i)
    {
      QWidget *widget = form->itemAt(i)->widget();
      if (widget != NULL)
      {
        delete widget;
      }
    }
    */
    while ( form->count() != 0)
    {
        QLayoutItem *forDeletion = form->takeAt(0);
        delete forDeletion->widget();
        delete forDeletion;
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

void NewGeoObjDialog::setLineEditValidators()
{
    auto &form = ui->formLayout_param;
    for (int i = 0; i < form->count(); ++i)
    {
      QWidget *widget = form->itemAt(i)->widget();
      if(QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget)) // it's a lineEdit
      {
          lineEdit->setValidator(new QDoubleValidator(form));
          connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(checkLineEditValidity()));
      }
    }
}

void NewGeoObjDialog::checkLineEditValidity()
{
    auto &form = ui->formLayout_param;
    bool ok = true;
    for (int i = 0; i < form->count(); ++i)
    {
      QWidget *widget = form->itemAt(i)->widget();
      if(QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget)) // it's a lineEdit
      {
          if( ! lineEdit->hasAcceptableInput())
          {
              ok = false;
              break;
          }
      }
    }
    //printf("%d\n", ok); fflush(stdout);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ok);
}
