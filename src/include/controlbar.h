#ifndef CONTROLBAR_H
#define CONTROLBAR_H
#include<DIconButton>
#include <DWidget>
DWIDGET_USE_NAMESPACE
class ControlBar : public QWidget
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);
    DIconButton *bt1=new DIconButton(this);
    DIconButton *bt2=new DIconButton(this);
    DIconButton *bt3=new DIconButton(this);
    DIconButton *bt4=new DIconButton(this);
    DIconButton *bt5=new DIconButton(this);
    DIconButton *bt6=new DIconButton(this);
    DIconButton *bt7=new DIconButton(this);
signals:

public slots:
};

#endif // CONTROLBAR_H
