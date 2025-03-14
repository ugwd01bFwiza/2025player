#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QAction>
#include <QKeySequence>
#include <QMap>

class ShortcutManager : public QObject
{
    Q_OBJECT
public:
    static ShortcutManager* instance();
    void updateShortcut(const QString &name, const QKeySequence &keySequence);

    QMap<QString, QAction*> actions;
    void setupDefaultShortcuts();
    void bindActionsTo(QWidget *target);
signals:
    void playTriggered();
    void pauseTriggered();
    void nextTriggered();
    void previousTriggered();
    void volumeUpTriggered();
    void volumeDownTriggered();



private:
    explicit ShortcutManager(QObject *parent = nullptr);
    static ShortcutManager* s_instance;

};

#endif // SHORTCUTMANAGER_H
