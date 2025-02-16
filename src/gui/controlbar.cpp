#include "controlbar.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DLabel>
#include<DIconButton>
#include<QFile>

ControlBar::ControlBar(QWidget *parent) : QFrame(parent)
{
    currenttime=0;
    cTimer=new QTimer(this);
    LoadStyleSheet();
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QPalette qp = parent->palette();
    qp.setColor(QPalette::Background, Qt::transparent);
    QVBoxLayout* MainVlayout = new QVBoxLayout(this);
    QHBoxLayout* UpHlayout = new QHBoxLayout();
    QHBoxLayout* DownHlayout = new QHBoxLayout();
    playtime = new DLabel(this);
    endtime = new DLabel(this);
    processSlider=new DSlider (Qt::Horizontal,this);
    volumeSlider = new DSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setLeftIcon(QIcon(":/asset/image/fvolume.PNG"));
    volumeSlider->setMaximumWidth(100);
    volumeSlider->setIconSize(QSize(24,24));
    btplay->setIcon(QIcon(":/asset/image/play.PNG"));
    btplay->setIconSize(QSize(24,24));
    btplay->setFixedSize(QSize(36,36));
    btplay->setObjectName("bt_play");
    btplay->setFlat(false);
    btpre->setIcon(QIcon(":/asset/image/previous.PNG"));
    btpre->setIconSize(QSize(18,18));
    btpre->setObjectName("bt_pre");
    //btpre->setStyleSheet("#bt_pre{ background-color: transparent;}");

    btstop->setIcon(QIcon(":/asset/image/stop.PNG"));
    btstop->setIconSize(QSize(18, 18));
    btstop->setObjectName("bt_stop");

    btnex->setIcon(QIcon(":/asset/image/next.PNG"));
    btnex->setIconSize(QSize(18, 18));
    btnex->setObjectName("bt_next");


//    btvolume->setIcon(QIcon(":/asset/image/fvolume.PNG"));
//    btvolume->setIconSize(QSize(18, 18));
//    btvolume->setObjectName("bt_volume");
//    btvolume->setStyleSheet("#bt_volume{ background-color: transparent;}");
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
    UpHlayout->addWidget(processSlider);
    UpHlayout->addWidget(endtime);

    DownHlayout->addSpacing(4);
    DownHlayout->addWidget(btplay);
    DownHlayout->addSpacing(5);
    DownHlayout->addWidget(btpre);
    DownHlayout->addWidget(btstop);
    DownHlayout->addWidget(btnex);
    DownHlayout->addSpacing(5);
    //DownHlayout->addWidget(btvolume);

    DownHlayout->addWidget(volumeSlider);
    DownHlayout->addSpacing(5);
    DownHlayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    DownHlayout->addWidget(btscreen);
    connect(btplay,&DIconButton::clicked,this, &ControlBar::playslot);
    connect(btpre,&DIconButton::clicked,this, &ControlBar::preslot);
    connect(btstop,&DIconButton::clicked,this, &ControlBar::stopslot);
    connect(btnex,&DIconButton::clicked,this, &ControlBar::nexslot);
    connect(&MusicPlayer::instance(),&MusicPlayer::stateChanged,this,&ControlBar::stchange);
    connect(MusicPlayer::instance().locallist,&QMediaPlaylist::currentIndexChanged,this,&ControlBar::mediachange);
    connect(cTimer, &QTimer::timeout, this, &ControlBar::handleTimeout);
    connect(processSlider,&DSlider::valueChanged,this,&ControlBar::sliderchange);
    connect(processSlider,&DSlider::sliderReleased ,this,&ControlBar::processsetting);
    connect(volumeSlider,&DSlider:: valueChanged,this,&ControlBar::volumesetting);
    //connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&MusicTable::setTheme);
    //connect(btvolume, &DIconButton::clicked, this, &ControlBar::switchvolume);


//    connect(volumeSlider, &DSlider::valueChanged, mediaPlayer, &QMediaPlayer::setVolume);
}
///读取设置之前的音量设置(todo
void ControlBar::readVolume(const QString &filePath){
    volumeSlider->setValue(preVolume);
    mediaPlayer->setVolume(preVolume);
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
///计算分秒
QString formatTime(int timeInSeconds) {
        if (timeInSeconds == 0) {
            return "00.00";
        } int minutes = timeInSeconds / 60;
          int seconds = timeInSeconds % 60;
          QString a;
          if(minutes>=10){
              a+=QString("%1").arg(minutes);
            }
            else {
              a+=QString("0%1").arg(minutes);

          }
          a+=".";
          if(seconds>=10){
            a+=QString("%1").arg(seconds);
          }
          else{
            a+=QString("0%1").arg(seconds);
          }
          return a;
    }

void ControlBar::stchange(QMediaPlayer::State state){
    if(state==QMediaPlayer::StoppedState){
         btplay->setIcon(QIcon(":/asset/image/play.PNG"));
         currenttime=0;

         playtime ->setText("--.--");
         endtime->setText("--.--");
         cTimer->stop();
         processSlider->setValue(0);
    }
    else if(state==QMediaPlayer::PlayingState){
         btplay->setIcon(QIcon(":/asset/image/pause.PNG"));
         if(currenttime){
             cTimer->start();

         }


    }
    else{
         btplay->setIcon(QIcon(":/asset/image/play.PNG"));
         cTimer->stop();
    }
}
void ControlBar::playslot(){
    auto player= mediaPlayer;
    if(player->state()==QMediaPlayer::PlayingState){

        player->pause();
    }
    else{

        player->play();
    }
}
void ControlBar::preslot(){
      mediaPlayer->playlist()->previous();
      mediaPlayer->play();
}
void ControlBar::stopslot(){
     mediaPlayer->stop();


}
void ControlBar::nexslot(){
      mediaPlayer->playlist()->next(); mediaPlayer->play();
}

void ControlBar::handleTimeout(){
     currenttime+=1;

     playtime ->setText(formatTime(currenttime));

     processSlider->setValue(currenttime);

}
void ControlBar::mediachange(int index){
    currenttime=0;
    cTimer->start(1000);
    processSlider->setMinimum(0);

    playtime ->setText(formatTime(currenttime));
    processSlider->setValue(currenttime);
    endtime->setText(QString(formatTime(mediaPlayer->MMetalist[index].duration)));
    processSlider->setMaximum(mediaPlayer->MMetalist[index].duration);
}
void ControlBar::sliderchange(int value){
    currenttime=value;
    playtime ->setText(formatTime(currenttime));
}
void ControlBar::volumesetting(int value){
    mediaPlayer->setVolume(value);
}
void ControlBar::processsetting(){
    mediaPlayer->setPosition(processSlider->value()*1000);
}
void ControlBar::switchvolume() {
    if(volumeSlider->value()){
        //关
        preVolume=volumeSlider->value();
        volumeSlider->setValue(0);

    }
    else{
        volumeSlider->setValue(preVolume);

    }

}
