///管理设置的类
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include <QStringList>
#include <QKeySequence>
#include <QScopedPointer>
#include <QMap>

class SettingsManager
{
public:
    static SettingsManager* instance();
    
    void saveSettings(const QString &tag, const QStringList &paths);
    void loadSettings(const QString &tag, QStringList &paths);
    void saveSettingsShortcutsMap(const QMap<QString, QKeySequence> &shortcuts);
    void loadSettingsShortcutsMap(QMap<QString, QKeySequence> &shortcuts);

private:
    explicit SettingsManager(const QString &filePath);
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    static SettingsManager* s_instance;
    QScopedPointer<QSettings> settings;
};

#endif // SETTINGSMANAGER_H