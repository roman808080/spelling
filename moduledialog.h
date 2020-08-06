#ifndef MODULEDIALOG_H
#define MODULEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QDir>

#include <memory>
#include <string>

class QMediaPlayer;

namespace Ui {
class ModuleDialog;
}

class ModuleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleDialog(const std::string& key,
                          std::shared_ptr<QJsonObject> jsonObject,
                          QWidget* parent = nullptr);
    ~ModuleDialog();

public slots:
    void playCurrentWord();
    void switchToNextWord();
    void switchToPreviousWorld();
    void showAnswer();

private:
    void switchWord(int step);
    bool isWordOutOfScope();

private:
    std::unique_ptr<Ui::ModuleDialog> ui;
    std::string key;
    std::shared_ptr<QJsonObject> jsonObject;
    std::unique_ptr<QMediaPlayer> player;

    QDir audioPath;
    int currentWord;
};

#endif // MODULEDIALOG_H
