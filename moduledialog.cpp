#include "moduledialog.h"
#include "ui_moduledialog.h"

#include <QMediaPlayer>

namespace
{
    const int kVolume = 50;
}

ModuleDialog::ModuleDialog(const std::string& key,
                           std::shared_ptr<QJsonObject> jsonObject,
                           QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModuleDialog),
    key(key),
    jsonObject(jsonObject),
    player(new QMediaPlayer)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(key));

    auto currentPath = QDir::currentPath();
    audioPath = QDir(currentPath + QDir::separator() +
                     "modules" + QDir::separator() +
                     "default" + QDir::separator());

    connect(ui->playButton, &QPushButton::clicked, this, &ModuleDialog::handlePlayButton);
}

ModuleDialog::~ModuleDialog()
{
}

void ModuleDialog::handlePlayButton()
{
    player->setMedia(QUrl::fromLocalFile(audioPath.path() + QDir::separator() + "audio/uk_social.mp3"));
    player->setVolume(kVolume);
    player->play();
}
