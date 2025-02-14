#include "controlbar.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DLabel>
#include<DSlider>
#include<DIconButton>
#include<QFile>
ControlBar::ControlBar(QWidget *parent) : QFrame(parent)
{
    LoadStyleSheet();
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
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
    btplay->setObjectName("bt_play");
    btplay->setFlat(false);
    btpre->setIcon(QIcon(":/asset/image/previous.PNG"));
    btpre->setIconSize(QSize(18,18));
    btpre->setObjectName("bt_pre");
    btpre->setStyleSheet("#bt_pre{ background-color: transparent;}");

    btstop->setIcon(QIcon(":/asset/image/stop.PNG"));
    btstop->setIconSize(QSize(18, 18));
    btstop->setObjectName("bt_stop");

    btnex->setIcon(QIcon(":/asset/image/next.PNG"));
    btnex->setIconSize(QSize(18, 18));
    btnex->setObjectName("bt_next");

    btvolume->setIcon(QIcon(":/asset/image/fvolume.PNG"));
    btvolume->setIconSize(QSize(18, 18));
    btvolume->setObjectName("bt_volume");

    btscreen->setIcon(QIcon(":/asset/image/fscreen.PNG"));
    btscreen->setIconSize(QSize(24, 24));
    btscreen->setObjectName("bt_screen");

//    QString styleSheet = "#bt_play:hover, #bt_pre:hover, #bt_stop:hover, #bt_next:hover, #bt_volume:hover, #bt_screen:hover { background-color: #f1f1f1; }"
//                             "#bt_play:active, #bt_pre:active, #bt_stop:active, #bt_next:active, #bt_volume:active, #bt_screen:active { background-color: #ccc; }"
//                             "#bt_play, #bt_pre, #bt_stop, #bt_next, #bt_volume, #bt_screen { background-color: transparent; }";

//        // 应用样式到所有按钮
//        btplay->setStyleSheet(styleSheet);
//        btpre->setStyleSheet(styleSheet);
//        btstop->setStyleSheet(styleSheet);
//        btnex->setStyleSheet(styleSheet);
//        btvolume->setStyleSheet(styleSheet);
//        btscreen->setStyleSheet(styleSheet);
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

void ControlBar::LoadStyleSheet()
{
    QFile file(":/asset/qss/cbar.qss");
    file.open(QIODevice::ReadOnly);

    if (file.isOpen())
    {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
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
