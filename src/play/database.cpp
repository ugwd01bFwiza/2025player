#include "database.h"
#include <QFileInfo>
#include<QBuffer>
#include<QDebug>

DataBase* DataBase::instance = nullptr;
DataBase* DataBase::Instance()
{
    if (instance == nullptr) {
        instance = new DataBase();  // 创建唯一的实例
    }
    return instance;
}
DataBase::DataBase()
{
    createConnection("metaData"); //建立数据库连接接口
    db = QSqlDatabase::database("conToMetaData");//通过接口连接数据库
}
 bool DataBase::createConnection(QString dataBase_Name)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "conToMetaData");
    db.setDatabaseName(QString("%1%2").arg(dataBase_Name,".db"));

    //判断是否连接成功
    if (!db.open()) { //未连接到数据库
        qDebug() << "Error: Failed to connect database." << db.lastError();
        return false;
    }
    else { //连接到数据库
        return true;
    }
}
 bool DataBase::createPlayListNotExist(const QString &playListName)
 {
     QSqlQuery sql_query(db);
     QString sqlStatement;

     //查询数据库中是否存在该歌单
     sql_query.prepare("select count(*) from sqlite_master where type='table' and name=:tableName;");
     sql_query.bindValue(":tableName",playListName);
     if (!sql_query.exec()) {
         qDebug() << "查找歌单失败：" << playListName << sql_query.lastError();
         return false;
     }

     if (sql_query.next()) {
         if (sql_query.value(0).toInt() == 0) {//如果不存在该歌单，则创建
             /*歌单表属性
              * 1.  id
              * 2.  url
              * 3.  title
              * 4.  artist
              * 5.  album
              * 6.  duration
              * 7.  poster

              */
             sqlStatement = QString("create table %1 (id INTEGER PRIMARY KEY, url text not null, title text,"
                                    "artist text, album text,"
                                    "duration text, poster BLOB"
                                    ");").arg(playListName);
             if (!sql_query.exec(sqlStatement)) {
                 qDebug() << "歌单创建失败：" << playListName << sql_query.lastError();
                 return false;
             }
         }
     }

     return true;
 }

 bool DataBase::saveMetaData(const QMap<QString, QString> &metaDataMap, const QString &playListName, const QPixmap &img, bool status)
 {
     QSqlQuery sql_query(db);
     QString sqlStatement;

     QString url;
     QString title;
     QString artist;
     QString album;

     QString duration;

     QByteArray poster;
     QBuffer buffer(&poster);
     buffer.open(QIODevice::WriteOnly);

     img.save(&buffer, "PNG");


     for (QMap<QString,QString>::const_iterator it = metaDataMap.constBegin(); it != metaDataMap.constEnd(); it++) {
         if      (it.key() == "url")         { url = it.value();}
         else if (it.key() == "title")       { title = it.value();}
         else if (it.key() == "artist")      { artist = it.value();}
         else if (it.key() == "album")       { album = it.value();}
         else if (it.key() == "duration")    { duration = it.value();}

     }
     if (url.isNull()) {
         return false;
     }



     if (title.isNull()) {
         QFileInfo info(url);
         title = info.fileName();
         if (title.isNull()) {
             title = "未知歌名";
         }
     }
     if (artist.isNull()) {
         artist = "未知艺术家";
     }
     if (album.isNull()) {
         album = "未知专辑";
     }


     //创建或检查歌单
     if (!createPlayListNotExist(playListName)) {
         qDebug() << "无法创建歌单：" << playListName;
         return false;
     }

     sqlStatement = QString("select count(*) from %1 where url = :url;").arg(playListName);
     sql_query.prepare(sqlStatement);
     sql_query.bindValue(":url",url);
     if (!sql_query.exec()) {
         qDebug() << "无法查找重名url：" << url << sql_query.lastError();
         return false;
     } else if (sql_query.next()) {
         if (sql_query.value(0).toInt()>0) {
             status = false;
         }
     }

     //删除歌单中具有相同路径的歌曲元数据
     sqlStatement = QString("delete from %1 where url = :url").arg(playListName);
     sql_query.prepare(sqlStatement);
     sql_query.bindValue(":url",url);
     if (!sql_query.exec()) {
         qDebug() << "无法清除相同源的歌曲元数据：" << url << sql_query.lastError();
         return false;
     }

     sqlStatement = QString("insert into %1 (url,title,artist,album,duration,poster)"
                            "values(:url,:title,:artist,:album,:duration,:poster);").arg(playListName);
     sql_query.prepare(sqlStatement);
     sql_query.bindValue(":url",url);
     sql_query.bindValue(":title",title);
     sql_query.bindValue(":artist",artist);
     sql_query.bindValue(":album",album);
     sql_query.bindValue(":duration",duration);
     sql_query.bindValue(":poster",poster);


     if (!sql_query.exec()) {
         qDebug() << "插入歌曲元数据失败：" << playListName << sql_query.lastError();
         return false;
     }

     return true;
 }
 QStringList DataBase::getUrlFromPlayList(const QString &playListName)
 {
     QSqlQuery sql_query(db);
     QString sqlStatement;

     QStringList urlList;

     sqlStatement = QString("select url from %1;").arg(playListName);
     if (!sql_query.exec(sqlStatement)) {
         qDebug() << "无法获取到歌单中所有歌曲的url：" << playListName << sql_query.lastError();
         return urlList;
     }

     while(sql_query.next()) {
         QString url = sql_query.value(0).toString();
         if (!url.isNull()) {
            urlList.append(url);
         }
     }
     return urlList;
 }

 bool DataBase::deleteByUrl(const QStringList &url,const QString&playListName){

   QSqlQuery sql_query(db);
   QString sqlStatement;
   QStringList urlList = getUrlFromPlayList("url");
   for(QString itUrl : urlList) {
         sqlStatement = QString("delete from %1 where url = :url").arg(playListName);
         sql_query.prepare(sqlStatement);
         sql_query.bindValue(":url",itUrl);
         if (!sql_query.exec()) {
             qDebug() << "删除歌曲元数据失败：" << playListName << sql_query.lastError();
             return false;
         }
   }
   return true;
 }
