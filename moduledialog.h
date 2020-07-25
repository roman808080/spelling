#ifndef MODULEDIALOG_H
#define MODULEDIALOG_H

#include <QDialog>

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
    Ui::ModuleDialog *ui;
};

#endif // MODULEDIALOG_H
