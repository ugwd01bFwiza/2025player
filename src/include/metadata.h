///封装音乐元信息的类
#ifndef METADATA_H
#define METADATA_H
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

private:
};
class HistoryMData{
public:

    QString url;
    QString title;
    int duration;
    HistoryMData():
       url(""), title(""),duration(3){}
    HistoryMData(const QString &url, const QString &title, const int &duration)
            : url(url), title(title), duration(duration) {}
    HistoryMData(const QMap <QString,QString> &map){
        url=map["url"];
        title=map["title"];
        duration=map["duration"].toInt();
    }
   bool operator==(const HistoryMData& other) {
          return       url == other.url&&
            title ==other.title&&
            duration==other.duration;
               }
};

#endif // METADATA_H
