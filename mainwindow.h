#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "moduledialog.h"

#include <QMainWindow>
#include <QJsonObject>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void handleButton();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<ModuleDialog> moduleWindow;
    std::shared_ptr<QJsonObject> moduleJsonObject;
};
#endif // MAINWINDOW_H
