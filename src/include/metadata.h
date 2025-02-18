#ifndef METADATA_H
#define METADATA_H
#include"database.h"
#include<QWidget>
#include<QDir>
#include<QDebug>

class MetaData {
public:
    QString url;
    QString artist;
    QString title;
    QString album;
    QPixmap covpix;
    int duration;

    MetaData():
        artist(""), title(""), album(""), covpix(), duration(3) {}
    MetaData(const QString &url, const QString &title, const QString &artist, const QString &album, const int &duration, const QPixmap &poster)
            : url(url), title(title), artist(artist), album(album), duration(duration), covpix(poster) {}
    void loadLocalMusic(const QString &url,const QString &playListName);

private:
    bool isUrlInDatabase( DataBase *db,const QString &url, const QString &playListName);
};


#endif // METADATA_H
