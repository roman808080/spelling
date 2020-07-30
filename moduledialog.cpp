#include "moduledialog.h"
#include "ui_moduledialog.h"

ModuleDialog::ModuleDialog(const std::string& key,
                           std::shared_ptr<QJsonObject> jsonObject,
                           QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModuleDialog),
    key(key),
    jsonObject(jsonObject)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(key));
}

ModuleDialog::~ModuleDialog()
{
}
