#ifndef CONTROLBAR_H
#define CONTROLBAR_H
#include"musicplayer.h"
#include"musictable.h"
#include<DIconButton>
#include <DWidget>
#include<QTimer>
#include<DLabel>
#include<DSlider>
DWIDGET_USE_NAMESPACE
///最下面控制栏
class ControlBar : public QFrame
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);
    DIconButton *btplay=new DIconButton(this);
    DIconButton *btpre=new DIconButton(this);
    DIconButton *btstop=new DIconButton(this);
    DIconButton *btnex=new DIconButton(this);
    //DIconButton *btvolume=new DIconButton(this);
    DIconButton *btscreen=new DIconButton(this);
    MusicPlayer* mediaPlayer;
    QTimer* cTimer;
    DSlider* processSlider;
    DLabel*playtime;
    DLabel* endtime;
    DSlider* volumeSlider;


    MusicTable * temp;
    ///记录归零之前的音量
    int preVolume=100;
    int  currenttime;
    void LoadStyleSheet();

public slots:
    void stchange(QMediaPlayer::State state);
    void playslot();
    ///更改进度条
    void handleTimeout();
    void preslot();
    void stopslot();
    void nexslot();
    void mediachange(int index);
    void sliderchange(int value);
    void volumesetting(int value);
    void processsetting();
    void switchvolume();
    void readVolume(const QString &filePath);

};

#endif // CONTROLBAR_H
