#include "videoplayer.h"
#include "controlbar.h"
#include <QFileInfo>
#include <QKeyEvent>
#include <QDebug>

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent)
{
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    controlBar = new ControlBar(this);
    
    setupUI();
    connectSignals();
}

void VideoPlayer::setupUI()
{
    // 设置视频播放区域
    videoWidget->setMinimumSize(640, 360);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    
    // 设置标题和全屏按钮
    titleLabel = new DLabel("视频播放器");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    fullScreenButton = new DPushButton("全屏");
    
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(titleLabel, 1);
    headerLayout->addWidget(fullScreenButton);
    
    // 主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(videoWidget, 1);
    mainLayout->addWidget(controlBar);
    
    setLayout(mainLayout);
    
    // 将视频输出设置到videoWidget
    player->setVideoOutput(videoWidget);
    
    // 设置controlBar的mediaPlayer
//    controlBar->mediaPlayer = player;
    connect(player, &QMediaPlayer::stateChanged, controlBar,&ControlBar::stchange);
}

void VideoPlayer::connectSignals()
{
    connect(fullScreenButton, &DPushButton::clicked, this, &VideoPlayer::toggleFullScreen);
    connect(player, &QMediaPlayer::stateChanged, this, &VideoPlayer::onVideoStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayer::onMediaStatusChanged);
}

void VideoPlayer::playVideo(const QString &url)
{
    if (!url.isEmpty()) {
        currentUrl = url;
        QFileInfo fileInfo(url);
        titleLabel->setText(fileInfo.fileName());
        
        player->setMedia(QUrl::fromLocalFile(url));
        player->play();
    }
}

void VideoPlayer::toggleFullScreen()
{
    isFullScreen = !isFullScreen;
    
    if (isFullScreen) {
        // 隐藏控件，只显示视频
        titleLabel->hide();
        fullScreenButton->hide();
        controlBar->hide();
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        showFullScreen();
        
        // 设置视频控件大小为全屏
        videoWidget->setGeometry(0, 0, width(), height());
    } else {
        // 恢复正常显示
        setWindowFlags(Qt::Widget);
        showNormal();
        titleLabel->show();
        fullScreenButton->show();
        controlBar->show();
        
        // 恢复布局
        mainLayout->addWidget(videoWidget, 1);
    }
}

void VideoPlayer::onVideoStateChanged(QMediaPlayer::State state)
{
    // 可以添加状态改变时的处理
    if (state == QMediaPlayer::PlayingState) {
        // 播放状态
    } else if (state == QMediaPlayer::PausedState) {
        // 暂停状态
    } else if (state == QMediaPlayer::StoppedState) {
        // 停止状态
    }
}

void VideoPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        // 媒体加载完成后自动播放
        player->play();
        
        // 设置控制栏
        controlBar->processSlider->setMaximum(player->duration() / 1000);
        controlBar->endtime->setText(formatTime(player->duration() / 1000));
        controlBar->PlaySliderValueReset();
    }
}

void VideoPlayer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen) {
        toggleFullScreen();
    }
    QWidget::keyPressEvent(event);
}

QString VideoPlayer::formatTime(int seconds)
{
    int min = seconds /60;
    int sec = seconds %60;
    return QString("%1:%2").arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0'));
}
