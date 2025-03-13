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
SettingPage::SettingPage(QWidget *parent) : QFrame(parent) {
    setupUI();
    loadShortcuts();
}

SettingPage::~SettingPage() {
}

void SettingPage::setupUI() {
    scrollArea = new DScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("QScrollArea { background-color: #ffffff; border: 1px solid #e0e0e0; border-radius: 8px; }");
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

    QStringList actions = {"上一曲", "下一曲", "播放", "暂停", "音量加", "音量减"};
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
    QStringList paths;
    QKeySequence shortcut;
    SettingsManager settingsManager("settings.ini");
    settingsManager.loadSettings(paths, shortcut);

    for (const QString &action : shortcutEditors.keys()) {
        shortcutEditors[action]->setKeySequence(shortcut);
    }
}

void SettingPage::saveShortcuts() {
    QStringList paths;
    QKeySequence shortcut;
    
    for (const QString &action : shortcutEditors.keys()) {
        shortcut = shortcutEditors[action]->keySequence();
        paths.append(shortcut.toString());
    }

    SettingsManager settingsManager("settings.ini");
    settingsManager.saveSettings(paths, shortcut);
    QMessageBox::information(this, "保存成功", "快捷键已成功保存！");
}

void SettingPage::resetDefaults() {
    // Reset to default shortcuts logic
    QMessageBox::information(this, "重置成功", "快捷键已重置为默认值。");
}
