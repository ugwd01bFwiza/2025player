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
    playbackRateComboBox = new DComboBox(this);
    
    setupUI();
    setupPlaybackRates();
    connectSignals();
}

void VideoPlayer::setupPlaybackRates()
{
    // 添加常用的播放速率
    playbackRateComboBox->addItem("0.5x", 0.5);
    playbackRateComboBox->addItem("0.75x", 0.75);
    playbackRateComboBox->addItem("1.0x", 1.0);
    playbackRateComboBox->addItem("1.25x", 1.25);
    playbackRateComboBox->addItem("1.5x", 1.5);
    playbackRateComboBox->addItem("2.0x", 2.0);
    
    // 默认选择1.0x
    playbackRateComboBox->setCurrentIndex(2);
}

void VideoPlayer::setupUI()
{
    // 设置视频播放区域
    videoWidget->setMinimumSize(640, 360);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    
    // 设置标题、全屏按钮和倍速下拉框
    titleLabel = new DLabel("视频播放器");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    fullScreenButton = new DPushButton("全屏");
    
    // 设置倍速下拉框样式和大小
    playbackRateComboBox->setFixedWidth(80);
    playbackRateComboBox->setToolTip("播放速度");
    
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(titleLabel, 1);
    headerLayout->addWidget(playbackRateComboBox);
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

    // 设置窗口标题和大小
    setWindowTitle("视频播放");
    resize(800, 600);
}

void VideoPlayer::connectSignals()
{
    connect(fullScreenButton, &DPushButton::clicked, this, &VideoPlayer::toggleFullScreen);
    connect(player, &QMediaPlayer::stateChanged, this, &VideoPlayer::onVideoStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayer::onMediaStatusChanged);
    connect(playbackRateComboBox, QOverload<int>::of(&DComboBox::currentIndexChanged), 
            this, &VideoPlayer::onPlaybackRateChanged);
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

void VideoPlayer::setPlaybackRate(qreal rate)
{
    if (rate > 0) {
        currentPlaybackRate = rate;
        player->setPlaybackRate(currentPlaybackRate);
        qDebug() << "播放速度设置为:" << currentPlaybackRate << "倍";
    }
}

void VideoPlayer::toggleFullScreen()
{
    isFullScreen = !isFullScreen;
    
    if (isFullScreen) {
        // 隐藏控件，只显示视频
        titleLabel->hide();
        playbackRateComboBox->hide();
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
        playbackRateComboBox->show();
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
        // 播放状态 - 确保保持设定的倍速
        player->setPlaybackRate(currentPlaybackRate);
    } else if (state == QMediaPlayer::PausedState) {
        // 暂停状态
    } else if (state == QMediaPlayer::StoppedState) {
        // 停止状态
    }
}

void VideoPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia) {
        // 媒体加载完成后自动播放并设置倍速
        player->play();
        player->setPlaybackRate(currentPlaybackRate);
        
        // 设置控制栏
        controlBar->processSlider->setMaximum(player->duration() / 1000);
        controlBar->endtime->setText(formatTime(player->duration() / 1000));
        controlBar->PlaySliderValueReset();
    }
}

void VideoPlayer::onPlaybackRateChanged(int index)
{
    // 获取选择的倍速值
    qreal rate = playbackRateComboBox->itemData(index).toDouble();
    setPlaybackRate(rate);
}

void VideoPlayer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen) {
        toggleFullScreen();
    } else if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
        // 加号键增加播放速度
        int currentIndex = playbackRateComboBox->currentIndex();
        if (currentIndex < playbackRateComboBox->count() - 1) {
            playbackRateComboBox->setCurrentIndex(currentIndex + 1);
        }
    } else if (event->key() == Qt::Key_Minus) {
        // 减号键减小播放速度
        int currentIndex = playbackRateComboBox->currentIndex();
        if (currentIndex > 0) {
            playbackRateComboBox->setCurrentIndex(currentIndex - 1);
        }
    }
    QWidget::keyPressEvent(event);
}

QString VideoPlayer::formatTime(int seconds)
{
    int min = seconds /60;
    int sec = seconds %60;
    return QString("%1:%2").arg(min,2,10,QChar('0')).arg(sec,2,10,QChar('0'));
}
