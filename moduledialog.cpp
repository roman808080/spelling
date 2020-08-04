#include "moduledialog.h"
#include "ui_moduledialog.h"

#include <QMediaPlayer>
#include <QString>
#include <QJsonArray>

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
    player(new QMediaPlayer),
    currentWord(0)
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
    auto module = jsonObject->value(QString::fromStdString(key)).toArray();
    if (module.size() == 0 or
        currentWord > module.size())
    {
        return;
    }

    auto ukAudioPath = module[currentWord].toObject().value("uk_audio").toString();

    player->setMedia(QUrl::fromLocalFile(audioPath.path() + QDir::separator() + ukAudioPath));
    player->setVolume(kVolume);
    player->play();

    ++currentWord;
}
