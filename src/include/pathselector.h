///添加文件夹按钮的类

#ifndef PATHSELECTOR_H
#define PATHSELECTOR_H

#include"settingsmanager.h"
#include <QWidget>
#include <QString>
#include <QMenu>


#include <DPushButton>
#include <DMenu>

#include <QCoreApplication>
#include<QDir>
DWIDGET_USE_NAMESPACE
class PathSelector : public QWidget
{
    Q_OBJECT
public:
    explicit PathSelector(QWidget *parent = nullptr);

signals:
    // 当添加或删除路径时可通知上层
    void pathSelected(const QString &path);
    void pathDeleted(const QString &path);

private slots:
    void updateMenu();
    void addNewPath();
    void removePath(const QString &path);

private:
    DPushButton *pathButton; // 下拉菜单按钮
    DMenu *menu;             // 下拉菜单
void initUpdateMenu();

   const QString settingPath = QDir(QCoreApplication::applicationDirPath()).filePath("config.ini");

    // SettingsManager *settingManager; // 移除此行
};

#endif // PATHSELECTOR_H
