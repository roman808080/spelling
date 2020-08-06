#include "moduledialog.h"
#include "ui_moduledialog.h"

#include <QMediaPlayer>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

namespace
{
    const int kVolume = 50;
    const int kBack = -1;
    const int kNext = 1;
}

ModuleDialog::ModuleDialog(const std::string& key,
                           std::shared_ptr<QJsonObject> jsonObject,
                           QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ModuleDialog),
    key(key),
    player(new QMediaPlayer),
    currentWord(0)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(key));

    auto currentPath = QDir::currentPath();
    audioPath = QDir(currentPath + QDir::separator() +
                     "modules" + QDir::separator() +
                     "default" + QDir::separator());

    module = jsonObject->value(QString::fromStdString(key)).toArray();

    connect(ui->playButton, &QPushButton::clicked, this, &ModuleDialog::playCurrentWord);
    connect(ui->nextButton, &QPushButton::clicked, this, &ModuleDialog::switchToNextWord);
    connect(ui->backButton, &QPushButton::clicked, this, &ModuleDialog::switchToPreviousWorld);
    connect(ui->answerButton, &QPushButton::clicked, this, &ModuleDialog::showAnswer);

    playCurrentWord();
    clearAnswer();
}

ModuleDialog::~ModuleDialog()
{
}

void ModuleDialog::playCurrentWord()
{
    if (isWordOutOfScope())
    {
        return;
    }

    auto ukAudioPath = module[currentWord].toObject().value("uk_audio").toString();

    player->setMedia(QUrl::fromLocalFile(audioPath.path() + QDir::separator() + ukAudioPath));
    player->setVolume(kVolume);
    player->play();
}

void ModuleDialog::switchToNextWord()
{
    switchWord(kNext);
}

void ModuleDialog::switchToPreviousWorld()
{
    switchWord(kBack);
}

void ModuleDialog::showAnswer()
{
    if (isWordOutOfScope())
    {
        return;
    }

    auto answer = module[currentWord].toObject().value("expression").toString();
    ui->answerLabel->setText(answer);
}

void ModuleDialog::switchWord(int step)
{
    currentWord += step;
    if (isWordOutOfScope())
    {
        return;
    }

    playCurrentWord();
    clearAnswer();
}

bool ModuleDialog::isWordOutOfScope()
{
    return currentWord >= module.size() or
           currentWord < 0;
}

void ModuleDialog::clearAnswer()
{
    ui->answerLabel->setText("");
    ui->answerText->clear();
}
