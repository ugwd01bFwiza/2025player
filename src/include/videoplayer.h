#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QVBoxLayout>
#include <DPushButton>
#include <DLabel>
//#include "controlbar.h"

DWIDGET_USE_NAMESPACE

class ControlBar;
class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    
    void playVideo(const QString &url);
    void toggleFullScreen();
    QString formatTime(int seconds);
    
private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    ControlBar *controlBar;
    DPushButton *fullScreenButton;
    DLabel *titleLabel;
    QVBoxLayout *mainLayout;
    QString currentUrl;
    bool isFullScreen = false;

    void setupUI();
    void connectSignals();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void onVideoStateChanged(QMediaPlayer::State state);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};

#endif // VIDEOPLAYER_H
