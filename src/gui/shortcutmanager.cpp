#include "shortcutmanager.h"
#include <QApplication>

ShortcutManager* ShortcutManager::s_instance = nullptr;

ShortcutManager* ShortcutManager::instance() {
    if (!s_instance) {
        s_instance = new ShortcutManager(qApp);
    }
    return s_instance;
}

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent) {
    QStringList actionNames = {"播放", "暂停", "下一曲", "上一曲", "音量加", "音量减"};
    
    for (const QString &name : actionNames) {
        QAction *action = new QAction(this);
        action->setShortcutContext(Qt::ApplicationShortcut);
        actions[name] = action;
    }

    setupDefaultShortcuts();
    
    connect(actions["播放"], &QAction::triggered, this, &ShortcutManager::playTriggered);
    connect(actions["暂停"], &QAction::triggered, this, &ShortcutManager::pauseTriggered);
    connect(actions["下一曲"], &QAction::triggered, this, &ShortcutManager::nextTriggered);
    connect(actions["上一曲"], &QAction::triggered, this, &ShortcutManager::previousTriggered);
    connect(actions["音量加"], &QAction::triggered, this, &ShortcutManager::volumeUpTriggered);
    connect(actions["音量减"], &QAction::triggered, this, &ShortcutManager::volumeDownTriggered);
}

void ShortcutManager::setupDefaultShortcuts() {
    // 设置默认快捷键
    actions["播放"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    actions["暂停"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Space));
    actions["下一曲"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));
    actions["上一曲"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));
    actions["音量加"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left));
    actions["音量减"]->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right));
}

void ShortcutManager::updateShortcut(const QString &name, const QKeySequence &keySequence) {
    if (actions.contains(name)) {
        actions[name]->setShortcut(keySequence);
    }
}

void ShortcutManager::bindActionsTo(QWidget *target) {
    for (auto action : actions) {
        // 设置作用域：整个应用都能响应
        action->setShortcutContext(Qt::ApplicationShortcut);
        // 添加到目标窗口
        target->addAction(action);
    }
}
