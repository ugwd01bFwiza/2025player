#ifndef MEDIATABLE_H
#define MEDIATABLE_H
#include<QMediaPlayer>
#include<QDir>
#include <QMediaPlaylist>
#include<DTableWidget>
#include<QStandardItemModel>
 DWIDGET_USE_NAMESPACE
 struct MMeta{
     QString artist;
     QString sname;
     QString album;
     QString filePath;
     QPixmap covpix;
     int duration;
     MMeta(const QString &filePath);
 };

class MusicTable : public QWidget
{
Q_OBJECT
public:
    MusicTable(QWidget *parent );
    QWidget *music = new QWidget(this);
    QWidget *video = new QWidget (this);
    DTableWidget *music_Table;
    QDir localdir;
    QMediaPlaylist *playlist;

    QList<MMeta> MMetalist;
private:
    void ReadMediaFile();void AddSlot(QMediaPlayer::MediaStatus status);

};

#endif // MEDIATABLE_H
