#ifndef CONTROLBAR_H
#define CONTROLBAR_H
#include"musicplayer.h"
#include<DIconButton>
#include <DWidget>

DWIDGET_USE_NAMESPACE
class ControlBar : public QFrame
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);
    DIconButton *btplay=new DIconButton(this);
    DIconButton *btpre=new DIconButton(this);
    DIconButton *btstop=new DIconButton(this);
    DIconButton *btnex=new DIconButton(this);
    DIconButton *btvolume=new DIconButton(this);
    DIconButton *btscreen=new DIconButton(this);

    void LoadStyleSheet();
public slots:
    void stchange(QMediaPlayer::State state);
    void playslot();

    void preslot();
    void stopslot();
    void nexslot();
};

#endif // CONTROLBAR_H
