#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include "settingsmanager.h"
#include "shortcutmanager.h"
#include<DMessageManager>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QKeySequenceEdit>
#include <QMap>
#include <DScrollArea>
#include<QStyle>

DWIDGET_USE_NAMESPACE
class SettingPage : public QFrame {
    Q_OBJECT
public:
    explicit SettingPage(QWidget *parent = nullptr);
    ~SettingPage();

private slots:
    void saveShortcuts();
    void resetDefaults();

     
private:

    static SettingsManager* s_instance;
    void setupUI();
    void loadShortcuts();

    QVBoxLayout *mainLayout;
    QHBoxLayout *shortcutsLayout;
    QMap<QString, QKeySequenceEdit*> shortcutEditors;
    QPushButton *saveButton;
    QPushButton *resetButton;
    DScrollArea *scrollArea;
    const QStringList actions = {"上一曲", "下一曲", "播放", "暂停", "音量加", "音量减"};
};


#endif // SETTINGPAGE_H
