#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QWidget>
struct MMeta{
    QString artist;
    QString sname;
    QString album;
    QString filePath;
    QPixmap covpix;
    int duration;
    MMeta(const QString &filePath);
};

class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    MusicPlayer();
    QList<MMeta> MMetalist;
    QMediaPlaylist *locallist;

private:
    void InitLocateMusic();

};

#endif // MUSICPLAYER_H
