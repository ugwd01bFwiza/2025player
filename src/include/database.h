
///目前主要用数据库存音频等元信息
#ifndef DATABASE_H
#define DATABASE_H
#include"metadata.h"
#include <QStringList>
#include <QMap>
#include <QPixmap>
#include <QList>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DataBase : public QObject
{

    Q_OBJECT
public:
        static DataBase* instance();


        DataBase(const DataBase&) = delete;
        void operator=(const DataBase&) = delete;

    QSqlDatabase db;
public:

    
    void clearTable(const QString &playListName);
    bool createConnection(QString dataBase_Name);


    bool createPlayListNotExist(const QString &playListName);
  bool createHistoryListNotExist(const QString &playListName);

 
    bool saveMetaData(const QMap<QString, QString> &metaDataMap, const QString &playListName, const QPixmap &img, bool status);

    bool deleteByUrl(const QStringList &urllist,const QString&playListName);
    bool saveHistoryData(const QList<HistoryMData> &history);
    bool queryByUrl(const QString &url, const QString &playListName, QMap<QString,QString> &map);
    QStringList getUrlFromPlayList(const QString &playListName);
private:
    DataBase();
     static DataBase* s_instance;
};

#endif // DATABASE_H
