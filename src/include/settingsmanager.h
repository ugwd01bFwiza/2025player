///管理设置的类
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include <QStringList>
#include <QKeySequence>
#include <QScopedPointer>
#include <QMap>
#include <QObject>

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    static SettingsManager* instance();
    
      void saveSettingsShortcutsMap(const QMap<QString, QKeySequence> &shortcuts);
    void loadSettingsShortcutsMap(QMap<QString, QKeySequence> &shortcuts);
    void addNewPath(const QString &path);
    void deletePath(const QString &path);
    QStringList paths;
private:
      void saveSettings(const QString &tag, const QStringList &paths);
    void loadSettings(const QString &tag, QStringList &paths);

    void deleteSettings(const QString &tag,const QString &key);
    explicit SettingsManager(const QString &filePath);
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    static SettingsManager* s_instance;
    QScopedPointer<QSettings> settings;

signals:
    void pathChange();
};

#endif // SETTINGSMANAGER_H
