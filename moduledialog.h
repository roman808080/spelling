#ifndef MODULEDIALOG_H
#define MODULEDIALOG_H

#include <QDialog>

#include <memory>

namespace Ui {
class ModuleDialog;
}

class ModuleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleDialog(QWidget *parent = nullptr);
    ~ModuleDialog();

private:
    std::unique_ptr<Ui::ModuleDialog> ui;
};

#endif // MODULEDIALOG_H
