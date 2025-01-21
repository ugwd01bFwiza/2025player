#ifndef MainWindow_H
#define MainWindow_H
#include "navwidget.h"
#include <DMainWindow>
#include <DGuiApplicationHelper>//用来适配深色模式
#include<QVBoxLayout>
DWIDGET_USE_NAMESPACE
class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    QWidget *cw = new QWidget(this);
    QWidget *listshow=new QWidget(this);
    NavWidget *Navw = new  NavWidget;
    QVBoxLayout* MainVLayout = new QVBoxLayout;
    QHBoxLayout* UpHLayout = new QHBoxLayout;
    QHBoxLayout* DownHLayout = new QHBoxLayout;
    QHBoxLayout* RightHLayout = new QHBoxLayout;
    void setTheme(DGuiApplicationHelper::ColorType);
    void currentchange(const QModelIndex &current,const QModelIndex &previous);
};

#endif // MUSIWINDOW_H
