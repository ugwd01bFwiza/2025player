#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include "settingsmanager.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QKeySequenceEdit>
#include <QMap>
#include <DScrollArea>

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
    void setupUI();
    void loadShortcuts();

    QVBoxLayout *mainLayout;
    QHBoxLayout *shortcutsLayout;
    QMap<QString, QKeySequenceEdit*> shortcutEditors;
    QPushButton *saveButton;
    QPushButton *resetButton;
    SettingsManager *settingsManager;
    DScrollArea *scrollArea;
};

#endif // SETTINGPAGE_H
