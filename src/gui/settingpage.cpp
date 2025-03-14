/**
 * @brief Sets up the user interface for the settings page
 * 
 * This function initializes and arranges the UI elements for the shortcut settings page:
 * - Creates a title label for the shortcut settings
 * - Creates QKeySequenceEdit widgets for each action to capture keyboard shortcuts
 * - Adds save and reset buttons
 * - Connects button signals to their respective slots
 * 
 * The UI elements are arranged vertically using a QVBoxLayout.
 * Each shortcut editor is stored in the shortcutEditors map with its action name as the key.
 */
#include "settingpage.h"
#include <QSettings>
#include <QMessageBox>
#include"shortcutmanager.h"
SettingPage::SettingPage(QWidget *parent) : QFrame(parent) {
    setupUI();
    loadShortcuts();
}

SettingPage::~SettingPage() {
}

void SettingPage::setupUI() {
    scrollArea = new DScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background-color: #ffffff; border: 1px solid #e0e0e0; border-radius: 18px; }");
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget(scrollArea);
    mainLayout = new QVBoxLayout(scrollWidget);

    QLabel *titleLabel = new QLabel("快捷键设置", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    // Create shortcut editors layout
    shortcutsLayout = new QHBoxLayout();
    QVBoxLayout *leftColumn = new QVBoxLayout();
    QVBoxLayout *rightColumn = new QVBoxLayout();
    shortcutsLayout->addLayout(leftColumn);
    shortcutsLayout->addLayout(rightColumn);

    
    for (int i = 0; i < actions.size(); ++i) {
        const QString &action = actions[i];
        QKeySequenceEdit *editor = new QKeySequenceEdit(this);
        shortcutEditors[action] = editor;
        QLabel *actionLabel = new QLabel(action, this);

        if (i % 2 == 0) {
            leftColumn->addWidget(actionLabel);
            leftColumn->addWidget(editor);
        } else {
            rightColumn->addWidget(actionLabel);
            rightColumn->addWidget(editor);
        }
    }

    mainLayout->addLayout(shortcutsLayout);

    saveButton = new QPushButton("保存", this);
    resetButton = new QPushButton("重置默认", this);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(resetButton);

    connect(saveButton, &QPushButton::clicked, this, &SettingPage::saveShortcuts);
    connect(resetButton, &QPushButton::clicked, this, &SettingPage::resetDefaults);

    scrollArea->setWidget(scrollWidget);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    setLayout(layout);
}

void SettingPage::loadShortcuts() {
    QMap<QString, QKeySequence> shortcuts;
    SettingsManager::instance()->loadSettingsShortcutsMap(shortcuts);

    for (const QString &action : shortcutEditors.keys()) {
        if (shortcuts.contains(action)) {
            shortcutEditors[action]->setKeySequence(shortcuts[action]);
        }
    }
}

void SettingPage::saveShortcuts() {
    QMap<QString, QKeySequence> shortcuts;
    
    for (const QString &action : shortcutEditors.keys()) {
        QKeySequence sequence = shortcutEditors[action]->keySequence();
        shortcuts[action] = sequence;
        // 直接更新快捷键，无需重连
        ShortcutManager::instance()->updateShortcut(action, sequence);
    }

    SettingsManager::instance()->saveSettingsShortcutsMap(shortcuts);
    QMessageBox::information(this, "保存成功", "快捷键已成功保存并生效！");
}


void SettingPage::resetDefaults() {
    // 获取ShortcutManager实例并设置默认快捷键
    ShortcutManager* manager = ShortcutManager::instance();
    manager->setupDefaultShortcuts(); // 重置内存中的快捷键

    // 构建默认快捷键映射（直接从ShortcutManager获取）
    QMap<QString, QKeySequence> defaultShortcuts;
    const QStringList actionNames = {"播放", "暂停", "下一曲", "上一曲", "音量加", "音量减"};
    for (const QString &action : actionNames) {
        if (manager->actions.contains(action)) {
            defaultShortcuts[action] = manager->actions[action]->shortcut();
        }
    }

    // 更新UI中的QKeySequenceEdit控件
    for (const QString &action : shortcutEditors.keys()) {
        if (defaultShortcuts.contains(action)) {
            shortcutEditors[action]->setKeySequence(defaultShortcuts[action]);
        }
    }

    // 保存默认值到配置文件
    SettingsManager::instance()->saveSettingsShortcutsMap(defaultShortcuts);
    DMessageManager::instance()->sendMessage(this, style()->standardIcon(QStyle::SP_MessageBoxWarning),
    "重置成功" );
    
}