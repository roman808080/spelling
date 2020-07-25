#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i=0; i<100; ++i)
    {
        ui->lessons->addItem(QString::number(i));
    }
}

MainWindow::~MainWindow()
{
}
