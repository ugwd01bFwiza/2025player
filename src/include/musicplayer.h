#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QWidget>
#include <QVector>
struct MMeta{
    QString artist;
    QString sname;
    QString album;
    QString filePath;
    QPixmap covpix;
    int duration;
    MMeta(const QString &filePath);
    MMeta()
            : artist(""), sname(""), album(""), filePath(""), covpix(), duration(3) {}

};

class MusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    MusicPlayer();
    QVector<MMeta> MMetalist;
    QMediaPlaylist *locallist;
    static MusicPlayer& instance() {
            static MusicPlayer player;
            return player;
        }

private:
    void InitLocateMusic();

};

#endif // MUSICPLAYER_H
