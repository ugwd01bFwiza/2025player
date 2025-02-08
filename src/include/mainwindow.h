#ifndef MainWindow_H
#define MainWindow_H
#include "navwidget.h"
#include"musictable.h"
#include<controlbar.h>
#include <DMainWindow>
#include <DGuiApplicationHelper>//用来适配深色模式
#include<QVBoxLayout>
#include<QMediaPlayer>
DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private:
    QWidget *cw = new QWidget();
    NavWidget *Navw = new  NavWidget;
    ControlBar * cbar = new ControlBar(this);
    //主布局
    QVBoxLayout* MainVLayout = new QVBoxLayout;

    QHBoxLayout* UpHLayout = new QHBoxLayout;
    QHBoxLayout* DownHLayout = new QHBoxLayout;
    //有奖
    QHBoxLayout* RightHLayout = new QHBoxLayout;   
    QMediaPlayer *player = new QMediaPlayer(this);
    QStackedWidget * page;
public slots:
    void setTheme(DGuiApplicationHelper::ColorType);
    void currentchange(const QModelIndex &current,const QModelIndex &previous);

};

#endif // MAINWINDOW_H
