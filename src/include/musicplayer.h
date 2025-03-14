///播放器的抽象
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include"database.h"
#include"metadata.h"
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QWidget>
#include <QVector>



class MusicPlayer : public QObject
{
    Q_OBJECT
public:
    MusicPlayer();
    QMediaPlayer* player;



    void initMusicByFilePath(const QString &mediaPath) ;

       static MusicPlayer& instance() {
            static MusicPlayer player;
            return player;
        }
   QVector< MetaData> MMetalist;
private:

QStringList musicExtensions = {"*.mp3", "*.wav", "*.flac", "*.aac"};

void readList(DataBase*db,const QString &playListName);
void loadLocalMusic(const QString &url,const QString &playListName);
bool isUrlInDatabase(DataBase *db, const QString &url, const QString &playListName);

signals:
    void playListChanged();
public slots:
void play(QString url);

///负责向数据库上传路径并发送信号给musictable使其更新页面;
 void installPath(const QString & filePath);
 ///负责向数据库卸载路径并发送信号给musictable使其更新页面;
    void uninstallPath(const QString &filePath);



};


#endif // MUSICPLAYER_H
