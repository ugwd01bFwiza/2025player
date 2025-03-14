#include "settingsmanager.h"
#include <QFileInfo>
#include <QDir>

SettingsManager* SettingsManager::s_instance = nullptr;

SettingsManager* SettingsManager::instance() {
    if (!s_instance) {
        s_instance = new SettingsManager("config.ini");
    }
    return s_instance;
}

SettingsManager::SettingsManager(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    settings.reset(new QSettings(filePath, QSettings::IniFormat));

    // 初始化默认值
    if (!settings->contains("shortcut")) {
        settings->beginWriteArray("localPaths");
        settings->endArray(); // 创建空路径数组
        settings->setValue("shortcut", "");
        settings->sync();
    }
}

void SettingsManager::saveSettings(const QString &tag, const QStringList &paths)
{
    settings->beginWriteArray(tag);
    for (int i = 0; i < paths.size(); ++i) {
        settings->setArrayIndex(i);
        settings->setValue(tag, paths.at(i));
    }
    settings->endArray();
    settings->sync();
}

void SettingsManager::loadSettings(const QString &tag, QStringList &paths)
{
    paths.clear();
    int size = settings->beginReadArray(tag);
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        paths.append(settings->value(tag).toString());
    }
    settings->endArray();
}

void SettingsManager::saveSettingsShortcutsMap(const QMap<QString, QKeySequence> &shortcuts)
{    settings->beginGroup("Shortcuts");
    for (auto it = shortcuts.begin(); it != shortcuts.end(); ++it) {
        settings->setValue(it.key(), it.value().toString());
    }
    settings->endGroup();
    settings->sync();
}

void SettingsManager::loadSettingsShortcutsMap(QMap<QString, QKeySequence> &shortcuts)
{
    shortcuts.clear();
    settings->beginGroup("Shortcuts");
    QStringList keys = settings->childKeys();
    for (const QString &key : keys) {
        QString shortcutStr = settings->value(key).toString();
        shortcuts[key] = QKeySequence(shortcutStr);
    }
    settings->endGroup();
}
