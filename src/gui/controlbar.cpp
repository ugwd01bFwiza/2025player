#include "controlbar.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DLabel>
#include<DSlider>
#include<DPushButton>
#include<DIconButton>

ControlBar::ControlBar(QWidget *parent) : QWidget(parent)
{
    QPalette qp = parent->palette();
    qp.setColor(QPalette::Background, Qt::transparent);
    QVBoxLayout* MainVlayout = new QVBoxLayout(this);
    QHBoxLayout* UpHlayout = new QHBoxLayout();
    QHBoxLayout* DownHlayout = new QHBoxLayout();
    DLabel*playtime = new DLabel(this);
    DLabel* endtime = new DLabel(this);
    DSlider* slider=new DSlider (Qt::Horizontal,this);

    bt1->setIcon(QIcon(":/asset/image/play.PNG"));
    bt1->setIconSize(QSize(24,24));
    bt1->setStyleSheet("background: transparent;");
    bt2->setIcon(QIcon(":/asset/image/previous.PNG"));
    bt2->setIconSize(QSize(18,18));
    bt2->setStyleSheet("background: transparent;");
    bt3->setIcon(QIcon(":/asset/image/pause.PNG"));
    bt3->setIconSize(QSize(18,18));
    bt3->setStyleSheet("background: transparent;");
    bt4->setIcon(QIcon(":/asset/image/next.PNG"));
    bt4->setIconSize(QSize(18,18));
    bt4->setStyleSheet("background: transparent;");
    bt5->setIcon(QIcon(":/asset/image/fvolume.PNG"));
    bt5->setIconSize(QSize(18,18));
    bt5->setStyleSheet("background: transparent;");
    bt6->setIcon(QIcon(":/asset/image/stop.PNG"));
    bt6->setIconSize(QSize(18,18));
    bt6->setStyleSheet("background: transparent;");
    bt7->setIcon(QIcon(":/asset/image/fscreen.PNG"));
    bt7->setIconSize(QSize(24,24));
    bt7->setStyleSheet("background: transparent;");

    playtime ->setText("--.--");
    endtime->setText("--.--");
    MainVlayout->addLayout(UpHlayout);
    MainVlayout->addLayout(DownHlayout);
    MainVlayout->setStretch(0,2);
    MainVlayout->setStretch(1,1);
    UpHlayout->addWidget(playtime);
    UpHlayout->addWidget(slider);
    UpHlayout->addWidget(endtime);

    DownHlayout->addSpacing(4);
    DownHlayout->addWidget(bt1);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(bt2);
    DownHlayout->addWidget(bt3);
    DownHlayout->addWidget(bt4);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(bt5);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(bt6);
    DownHlayout->addSpacing(5);
    DownHlayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    DownHlayout->addWidget(bt7);


}
