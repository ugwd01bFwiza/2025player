#include "settingsmanager.h"
#include <QFileInfo>
#include <QDir>

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

void SettingsManager::saveSettings(const QStringList &paths, const QKeySequence &shortcut)
{
    settings->beginWriteArray("localPaths");
    for (int i = 0; i < paths.size(); ++i) {
        settings->setArrayIndex(i);
        settings->setValue("path", paths.at(i));
    }
    settings->endArray();

    settings->setValue("shortcut", shortcut.toString());
    settings->sync();
}

void SettingsManager::loadSettings(QStringList &paths, QKeySequence &shortcut)
{
    paths.clear();
    int size = settings->beginReadArray("localPaths");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        paths.append(settings->value("path").toString());
    }
    settings->endArray();

    QString shortcutStr = settings->value("shortcut").toString();
    shortcut = QKeySequence(shortcutStr);
}

void SettingsManager::loadSettings(QStringList &paths)
{
    QKeySequence dummy;
    loadSettings(paths, dummy);
}

void SettingsManager::loadSettings(QKeySequence &shortcut)
{
    QStringList dummy;
    loadSettings(dummy, shortcut);
}
