#include "moduledialog.h"
#include "ui_moduledialog.h"

ModuleDialog::ModuleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleDialog)
{
    ui->setupUi(this);
}

ModuleDialog::~ModuleDialog()
{
}
