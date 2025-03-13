///管理设置的类

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include <QStringList>
#include <QKeySequence>

class SettingsManager
{
public:
    SettingsManager(const QString &filePath);
    void saveSettings(const QStringList &paths, const QKeySequence &shortcut);
    void loadSettings(QStringList &paths, QKeySequence &shortcut);
    void loadSettings(QStringList &paths);
    void loadSettings(QKeySequence &shortcut);

private:
    QScopedPointer<QSettings> settings;
};


#endif