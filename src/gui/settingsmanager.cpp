#include "settingsmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include<QFileInfo>
#include<QDir>

SettingsManager::SettingsManager(const QString &filePath) : settingsFilePath(filePath) {
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();

    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << dir.absolutePath();
        }
    }

    if (!fileInfo.exists()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QJsonObject defaultJson;
            defaultJson["localPaths"] = QJsonArray();
            defaultJson["shortcut"] = "";

            file.write(QJsonDocument(defaultJson).toJson());
            file.close();
            qDebug() << "Created settings.json at:" << filePath;
        } else {
            qWarning() << "Failed to create file:" << filePath << "Error:" << file.errorString();
        }
    } else {
        qDebug() << "Settings file already exists at:" << filePath;
    }
}






void SettingsManager::saveSettings(const QStringList &paths, const QKeySequence &shortcut) {
    QJsonObject json;
    QJsonArray pathsArray;
    for (const QString &path : paths) {
        pathsArray.append(path);
    }
    json["localPaths"] = pathsArray;
    json["shortcut"] = shortcut.toString();


    QFile file(settingsFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(json).toJson());
        file.close();
    } else {
        qWarning() << "Failed to open settings file for writing:" << settingsFilePath;
    }
}

void SettingsManager::loadSettings(QStringList &paths, QKeySequence &shortcut) {
    QFile file(settingsFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open settings file for reading:" << settingsFilePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) {
        qWarning() << "Invalid JSON format in settings file.";
         qWarning() << "Error: " << file.errorString();
        return;
    }

    QJsonObject json = doc.object();
    paths.clear();
    if (json.contains("localPaths") && json["localPaths"].isArray()) {
        QJsonArray pathsArray = json["localPaths"].toArray();
        for (const QJsonValue &value : pathsArray) {
            paths.append(value.toString());
        }
    }

    if (json.contains("shortcut")) {
        shortcut = QKeySequence(json["shortcut"].toString());
    }
}

void SettingsManager::loadSettings(QStringList &paths) {
    QKeySequence dummy;
    loadSettings(paths, dummy);
}

void SettingsManager::loadSettings(QKeySequence &shortcut) {
    QStringList dummy;
    loadSettings(dummy, shortcut);
}
