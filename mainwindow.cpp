#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    auto currentPath = QDir::currentPath();
    QDir jsonPath(currentPath + QDir::separator() +
                  "modules" + QDir::separator() +
                  "default" + QDir::separator() +
                  "info.json");

    QFile file(jsonPath.path());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto bytes = file.readAll();
    file.close();

    auto jsonDocument = QJsonDocument::fromJson(bytes);
    auto jsonObject = jsonDocument.object();

    ui->setupUi(this);

    ui->lessons->clear();
    for (const auto& key: jsonObject.keys())
    {
        ui->lessons->addItem(key);
    }

    connect(ui->goButton, &QPushButton::clicked, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleButton()
{
    if (!moduleWindow or !moduleWindow->isVisible())
    {
        moduleWindow.reset(new ModuleDialog);
        moduleWindow->show();
    }
}
