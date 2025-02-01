#include "controlbar.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DLabel>
#include<DSlider>
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

    btplay->setIcon(QIcon(":/asset/image/play.PNG"));
    btplay->setIconSize(QSize(24,24));
    btplay->setFixedSize(QSize(36,36));
   // btplay->setStyleSheet("background: transparent;");
    btpre->setIcon(QIcon(":/asset/image/previous.PNG"));
    btpre->setIconSize(QSize(18,18));
   // btpre->setStyleSheet("background: transparent;");
    btstop->setIcon(QIcon(":/asset/image/stop.PNG"));
    btstop->setIconSize(QSize(18,18));
    //btstop->setStyleSheet("background: transparent;");
    btnex->setIcon(QIcon(":/asset/image/next.PNG"));
    btnex->setIconSize(QSize(18,18));
    //btnex->setStyleSheet("background: transparent;");
    btvolume->setIcon(QIcon(":/asset/image/fvolume.PNG"));
    btvolume->setIconSize(QSize(18,18));
   // btvolume->setStyleSheet("background: transparent;");

    btscreen->setIcon(QIcon(":/asset/image/fscreen.PNG"));
    btscreen->setIconSize(QSize(24,24));
    //btscreen->setStyleSheet("background: transparent;");

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
    DownHlayout->addWidget(btplay);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(btpre);
    DownHlayout->addWidget(btstop);
    DownHlayout->addWidget(btnex);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(btvolume);
    DownHlayout->addSpacing(5);
    DownHlayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    DownHlayout->addWidget(btscreen);
    connect(btplay,&DIconButton::clicked,this, &ControlBar::playslot);
    connect(btpre,&DIconButton::clicked,this, &ControlBar::preslot);
    connect(btstop,&DIconButton::clicked,this, &ControlBar::stopslot);
    connect(btnex,&DIconButton::clicked,this, &ControlBar::nexslot);

    connect(&MusicPlayer::instance(),&MusicPlayer::stateChanged,this,&ControlBar::stchange);
}
void ControlBar::stchange(QMediaPlayer::State state){
    if(state==QMediaPlayer::StoppedState){
         btplay->setIcon(QIcon(":/asset/image/play.PNG"));
    //todo
    }
    else if(state==QMediaPlayer::PlayingState){
         btplay->setIcon(QIcon(":/asset/image/pause.PNG"));
    }
    else{
         btplay->setIcon(QIcon(":/asset/image/play.PNG"));
    }
}
void ControlBar::playslot(){
    auto &player= MusicPlayer::instance();
    if(player.state()==QMediaPlayer::PlayingState){

        player.pause();
    }
    else{

        player.play();
    }
}
void ControlBar::preslot(){
      MusicPlayer::instance().playlist()->previous();
}
void ControlBar::stopslot(){
     MusicPlayer::instance().stop();

}
void ControlBar::nexslot(){
       MusicPlayer::instance().playlist()->next();
}
