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



    static MusicPlayer& instance() {
            static MusicPlayer player;
            return player;
        }
   QVector< MetaData> MMetalist;
private:
    void InitLocateMusic();
void readList(DataBase*db,const QString &playListName);
void loadLocalMusic(const QString &url,const QString &playListName);
bool isUrlInDatabase(DataBase *db, const QString &url, const QString &playListName);
public slots:
void play(QString url);


};


#endif // MUSICPLAYER_H
