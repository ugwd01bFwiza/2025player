///最下面控制栏，调音量的
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
enum LoopState{

   Loop,
   Random,
   Queue,

};
class ControlBar : public QFrame
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);

    LoopState loopstate=Loop;
    DIconButton *btplay;
    DIconButton *btpre;
    DIconButton *btstop;
    DIconButton *btnex;
    DIconButton *btloop;
    //DIconButton *btvolume=new DIconButton(this);
    DIconButton *btscreen;
    MusicTable*table;
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
void PlaySliderValueReset();
private:
    void ChangeLoopBtIcon();
public slots:
    void stchange(QMediaPlayer::State state);
    void playslot();
    ///更改进度条
    void handleTimeout();
    void preslot();
    void stopslot();
    void nexslot();
    void mediachange(QMediaPlayer::MediaStatus state);
    void sliderchange(int value);
    void volumesetting(int value);
    void processsetting();
    void switchvolume();
    void readVolume(const QString &filePath);

    void onLoopChange();
};

#endif // CONTROLBAR_H
