#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget* parent)
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
    moduleJsonObject = std::make_shared<QJsonObject>(jsonDocument.object());

    ui->setupUi(this);

    ui->lessons->clear();
    for (const auto& key: moduleJsonObject->keys())
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
        int numberOfCurrentRow = ui->lessons->currentRow();
        auto row = ui->lessons->item(numberOfCurrentRow);
        auto key = row->text();

        moduleWindow.reset(new ModuleDialog(key.toStdString(), moduleJsonObject));
        moduleWindow->show();
    }
}
