
///目前主要用数据库存音频等元信息
#ifndef DATABASE_H
#define DATABASE_H
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
        static DataBase* Instance();


        DataBase(const DataBase&) = delete;
        void operator=(const DataBase&) = delete;

    QSqlDatabase db;
public:

    
    bool createConnection(QString dataBase_Name);


    bool createPlayListNotExist(const QString &playListName);

 
    bool saveMetaData(const QMap<QString, QString> &metaDataMap, const QString &playListName, const QPixmap &img, bool status);

    bool deleteByUrl(const QStringList &urllist,const QString&playListName);
    QStringList getUrlFromPlayList(const QString &playListName);
private:
    DataBase();
     static DataBase* instance;
};

#endif // DATABASE_H
