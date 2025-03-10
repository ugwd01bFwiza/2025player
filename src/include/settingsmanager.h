#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QStringList>
#include <QKeySequence>

class SettingsManager {
public:
    explicit SettingsManager(const QString &filePath);

    void saveSettings(const QStringList &paths, const QKeySequence &shortcut);

    void loadSettings(QStringList &paths, QKeySequence &shortcut); // 原始
    void loadSettings(QStringList &paths);                         // 只读路径
    void loadSettings(QKeySequence &shortcut);                     // 只读快捷键

private:
    QString settingsFilePath;
};

#endif // SETTINGSMANAGER_H
