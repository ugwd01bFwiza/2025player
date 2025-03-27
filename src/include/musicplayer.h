/// 播放器的抽象
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include "database.h"
#include "metadata.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>
#include <QVector>

class HistoryList :public QObject
{

    Q_OBJECT
private:
    const int MAX_HISTORY = 100; // 限制历史记录数量

public:

    QList<HistoryMData> history;
    void addToHistory(const HistoryMData &item)
    {
        // 检查是否存在相同项
        auto it = std::find(history.begin(), history.end(), item);
        if (it != history.end())
        {
            int index = std::distance(history.begin(), it);
            history.erase(it);
            emit historyListRemove(index);
        }
        history.prepend(item);

        while (history.size() > MAX_HISTORY)
        {
            history.removeLast();
            emit historyListRemove(history.size()-1);
        }
    }
    signals:void historyListRemove(int index);
};

class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    MusicPlayer();

    HistoryList history;

    void initMusicByFilePath(const QString &mediaPath);

    static MusicPlayer &instance()
    {
        static MusicPlayer player;
        return player;
    }
    QVector<MetaData> MMetalist;
    //nh
    void play();
    void pause();

    void stop();
    QMediaPlayer::State state();
    void setVolume(int volume);
    void setPosition(qint64 position);
    qint64 duration();
//nh

    void readHistoryList();

    void readMusicList( const QString &playListName);

// 在MusicPlayer类中添加以下内容
public:
    // 视频相关
    void playVideo(const QString &url);
    void loadVideoMetadata(const QString &url, const QString &playListName);
    
private:
    const QString videolist = "videolist";
    QStringList videoExtensions = {"*.mp4", "*.avi", "*.mkv", "*.mov", "*.flv", "*.wmv"};

private:
    void initConnect();
    QMediaPlayer *player;
    const QString locallist = "locallist";
    const QString historylist = "historylist";
    QStringList musicExtensions = {"*.mp3", "*.wav", "*.flac", "*.aac"};

    void loadLocalMusic(const QString &url, const QString &playListName);
    bool isUrlInDatabase(DataBase *db, const QString &url, const QString &playListName);

signals:
    void mediaListChanged();

signals:
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);

signals:
    void stateChanged(QMediaPlayer::State newState);

signals:
    void historyListChange(HistoryMData& item);
signals:
    void historyListRemove(int index);
public slots:
    void play(QString url);

    /// 负责向数据库上传路径并发送信号给musictable使其更新页面;
    void installPath(const QString &filePath);
    /// 负责向数据库卸载路径并发送信号给musictable使其更新页面;
    void uninstallPath(const QString &filePath);

    void onMediaChange(QMediaPlayer::MediaStatus state);

    void onAppAboutToQuit();
};
#endif // MUSICPLAYER_H
