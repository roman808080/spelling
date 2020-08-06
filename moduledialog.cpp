#include "moduledialog.h"
#include "ui_moduledialog.h"

#include <QMediaPlayer>
#include <QString>
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

    connect(ui->playButton, &QPushButton::clicked, this, &ModuleDialog::playCurrentWord);
    connect(ui->nextButton, &QPushButton::clicked, this, &ModuleDialog::switchToNextWord);
    connect(ui->backButton, &QPushButton::clicked, this, &ModuleDialog::switchToPreviousWorld);
    connect(ui->answerButton, &QPushButton::clicked, this, &ModuleDialog::showAnswer);

    playCurrentWord();
}

ModuleDialog::~ModuleDialog()
{
}

void ModuleDialog::playCurrentWord()
{
    auto module = jsonObject->value(QString::fromStdString(key)).toArray();
    if (module.size() == 0 or
        currentWord >= module.size())
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
    auto module = jsonObject->value(QString::fromStdString(key)).toArray();
    if (module.size() == 0 or
        currentWord >= module.size())
    {
        return;
    }

    auto answer = module[currentWord].toObject().value("expression").toString();
    ui->answerLabel->setText(answer);
}

void ModuleDialog::switchWord(int step)
{
    currentWord += step;

    auto module = jsonObject->value(QString::fromStdString(key)).toArray();
    if (currentWord >= module.size() or
        currentWord < 0)
    {
        return;
    }

    playCurrentWord();
    ui->answerLabel->setText("");
    ui->answerText->clear();
}

bool ModuleDialog::isWordOutOfScope()
{
    return false;
}
