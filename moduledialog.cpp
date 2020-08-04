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
    connect(ui->nextButton, &QPushButton::clicked, this, &ModuleDialog::handleNextButton);
    connect(ui->backButton, &QPushButton::clicked, this, &ModuleDialog::handleBackButton);
    connect(ui->answerButton, &QPushButton::clicked, this, &ModuleDialog::handleAnswerButton);

    handlePlayButton();
}

ModuleDialog::~ModuleDialog()
{
}

void ModuleDialog::handlePlayButton()
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

void ModuleDialog::handleNextButton()
{
    auto module = jsonObject->value(QString::fromStdString(key)).toArray();
    if (currentWord >= module.size())
    {

    }

    ++currentWord;
    handlePlayButton();
    ui->answerLabel->setText("");
    ui->answerText->clear();
}

void ModuleDialog::handleBackButton()
{
    if (currentWord <= 0)
    {
        return;
    }

    --currentWord;
    handlePlayButton();
    ui->answerLabel->setText("");
    ui->answerText->clear();
}

void ModuleDialog::handleAnswerButton()
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
