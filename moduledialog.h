#ifndef MODULEDIALOG_H
#define MODULEDIALOG_H

#include <QDialog>
#include <QJsonObject>

#include <memory>
#include <string>

namespace Ui {
class ModuleDialog;
}

class ModuleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleDialog(const std::string& key,
                          std::shared_ptr<QJsonObject> jsonObject,
                          QWidget* parent = nullptr);
    ~ModuleDialog();

private:
    std::unique_ptr<Ui::ModuleDialog> ui;
    std::string key;
    std::shared_ptr<QJsonObject> jsonObject;
};

#endif // MODULEDIALOG_H
