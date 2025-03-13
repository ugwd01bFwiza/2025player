#ifndef MainWindow_H
#define MainWindow_H
#include"settingpage.h"
#include "navwidget.h"
#include"musictable.h"
#include<controlbar.h>
#include <DMainWindow>
#include <DGuiApplicationHelper>//用来适配深色模式
#include<QVBoxLayout>
#include<QMediaPlayer>
#include <QResizeEvent>
DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private:
    QWidget *cw = new QWidget(this);
    NavWidget *Navw = new  NavWidget;
    ControlBar * cbar = new ControlBar(this);
    //主布局
    QVBoxLayout* MainVLayout = new QVBoxLayout;

    QHBoxLayout* UpHLayout = new QHBoxLayout;
    QHBoxLayout* DownHLayout = new QHBoxLayout;
    //有奖
    QHBoxLayout* RightHLayout = new QHBoxLayout;   
    QHBoxLayout* LeftHLayout = new QHBoxLayout;
    QMediaPlayer *player = new QMediaPlayer(this);
    QStackedWidget * page;
    MusicTable *music_table;
    SettingPage *settingPage ;

    void LoadStyleSheet(QString url);

public slots:
    void setTheme(DGuiApplicationHelper::ColorType);
    void currentchange(const QModelIndex &current,const QModelIndex &previous);
    protected:
    void resizeEvent(QResizeEvent *event) override;
public emit:
    void showSettingPage();
};

#endif // MAINWINDOW_H
