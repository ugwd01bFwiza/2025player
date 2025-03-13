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


    void initMusicByFilePath(QString mediaPath) ;
    void uninstallPath(DataBase *db, const QString &filePath,const QString &playListName);
    static MusicPlayer& instance() {
            static MusicPlayer player;
            return player;
        }
   QVector< MetaData> MMetalist;
private:
QStringList musicExtensions = {"mp3", "wav", "flac", "aac"};
void readList(DataBase*db,const QString &playListName);
void loadLocalMusic(const QString &url,const QString &playListName);
bool isUrlInDatabase(DataBase *db, const QString &url, const QString &playListName);
public slots:
void play(QString url);


};


#endif // MUSICPLAYER_H
