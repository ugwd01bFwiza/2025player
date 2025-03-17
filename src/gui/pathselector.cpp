#include "pathselector.h"
#include "musicplayer.h"
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <DLabel>
#include <DToolButton>
#include <DPushButton>
#include <QDebug>
#include <QFileDialog>
#include <DFileDialog>

PathSelector::PathSelector(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(8);

     
     
    // 创建按钮和菜单
    menu = new DMenu(this);
    pathButton = new DPushButton("选择路径 ▾", this);
    pathButton->setMenu(menu);
    mainLayout->addWidget(pathButton);

    // 每次点击按钮前刷新菜单
    connect(pathButton, &DPushButton::clicked, this, &PathSelector::updateMenu);
    connect(this, &PathSelector::pathSelected, 
        &MusicPlayer::instance(), &MusicPlayer::installPath);
    connect(this,&PathSelector::pathDeleted,
        &MusicPlayer::instance(), &MusicPlayer::uninstallPath); 

    initUpdateMenu();

}
///第一次，播放器读取音乐就是从这里开始的
void PathSelector::initUpdateMenu()
{
    // 清空菜单
    menu->clear();

    // 遍历每个路径，创建自定义菜单项a
    for (const QString &path :SettingsManager::instance()->paths) {
       //以这种方式加载路径
        MusicPlayer::instance().initMusicByFilePath(path);
        QWidget *itemWidget = new QWidget;
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(8, 4, 8, 4);
        itemLayout->setSpacing(10);

        DLabel *label = new DLabel(path, itemWidget);
        label->setStyleSheet("font-size: 13px; color: #333;");
        DToolButton *deleteButton = new DToolButton(itemWidget);
        deleteButton->setText("✖");
        deleteButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setStyleSheet(
            "QToolButton { border: none; color: #888; }"
            "QToolButton:hover { color: red; }"
        );

        itemLayout->addWidget(label);
        itemLayout->addStretch();
        itemLayout->addWidget(deleteButton);

        // 使用 QWidgetAction 将自定义 widget 添加到菜单中
        QWidgetAction *action = new QWidgetAction(menu);
        action->setDefaultWidget(itemWidget);
        menu->addAction(action);

        // 点击删除按钮时，移除该路径
        connect(deleteButton, &DToolButton::clicked, this, [=]() {
            removePath(path);
        });
    }

    MusicPlayer::instance().readMusicList("locallist");
    // 分隔线
    menu->addSeparator();

    // 添加“添加新文件夹”菜单项
    DPushButton *addBtn = new DPushButton("➕ 添加新文件夹", menu);
    addBtn->setStyleSheet(
        "QPushButton { padding: 6px 12px; color: #007AFF; border: none; background: transparent; }"
        "QPushButton:hover { background-color: #eee; }"
    );
    QWidgetAction *addAction = new QWidgetAction(menu);
    addAction->setDefaultWidget(addBtn);
    menu->addAction(addAction);

    connect(addBtn, &QPushButton::clicked, this, &PathSelector::addNewPath);

}
void PathSelector::updateMenu()
{
    // 清空菜单
    menu->clear();

    // 遍历每个路径，创建自定义菜单项a
    for (const QString &path : SettingsManager::instance()->paths) {
        // 自定义 widget，内含路径标签和删除按钮
        QWidget *itemWidget = new QWidget;
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);
        itemLayout->setContentsMargins(8, 4, 8, 4);
        itemLayout->setSpacing(10);

        DLabel *label = new DLabel(path, itemWidget);
        label->setStyleSheet("font-size: 13px; color: #333;");
        DToolButton *deleteButton = new DToolButton(itemWidget);
        deleteButton->setText("✖");
        deleteButton->setCursor(Qt::PointingHandCursor);
        deleteButton->setStyleSheet(
            "QToolButton { border: none; color: #888; }"
            "QToolButton:hover { color: red; }"
        );

        itemLayout->addWidget(label);
        itemLayout->addStretch();
        itemLayout->addWidget(deleteButton);

        // 使用 QWidgetAction 将自定义 widget 添加到菜单中
        QWidgetAction *action = new QWidgetAction(menu);
        action->setDefaultWidget(itemWidget);
        menu->addAction(action);

        // 点击删除按钮时，移除该路径
        connect(deleteButton, &DToolButton::clicked, this, [=]() {
            removePath(path);
        });
    }

    // 分隔线
    menu->addSeparator();

    // 添加“添加新文件夹”菜单项
    DPushButton *addBtn = new DPushButton("➕ 添加新文件夹", menu);
    addBtn->setStyleSheet(
        "QPushButton { padding: 6px 12px; color: #007AFF; border: none; background: transparent; }"
        "QPushButton:hover { background-color: #eee; }"
    );
    QWidgetAction *addAction = new QWidgetAction(menu);
    addAction->setDefaultWidget(addBtn);
    menu->addAction(addAction);

    connect(addBtn, &QPushButton::clicked, this, &PathSelector::addNewPath);
}

void PathSelector::addNewPath()
{
    QString dir = DFileDialog::getExistingDirectory(this, "选择路径");
    if (!dir.isEmpty() && !SettingsManager::instance()->paths.contains(dir)) {

        SettingsManager::instance()->addNewPath(dir);
        
        updateMenu();
        
        emit pathSelected(dir);

    }

}

void PathSelector::removePath(const QString &path)
{
    if (SettingsManager::instance()->paths.contains(path)) {
        SettingsManager::instance()->deletePath(path);
        updateMenu();
        emit pathDeleted(path);

    }
}
