#include"musicplayer.h"
#include<QDir>
#include <fileref.h>
#include<tag.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include <mpegfile.h>
#include <mp4file.h>
#include<QDebug>
MusicPlayer::MusicPlayer()
{

    locallist=new QMediaPlaylist(this);
    this->setPlaylist(locallist);
    InitLocateMusic();


}

void MusicPlayer::InitLocateMusic() {
    QString homePath = QDir::homePath();
    QString mediaPath = homePath + "/Desktop/media/";  // 拼接桌面路径和 media 文件夹


    QDir localdir(mediaPath);
    if (localdir.exists()) {
        QStringList filters;
        filters << "*.mp3" << "*.wav" << "*.flac";
        localdir.setNameFilters(filters);
        QFileInfoList files = localdir.entryInfoList();

        for (const QFileInfo& fileInfo : files) {
            // qDebug()<<fileInfo;
            QString filePath = fileInfo.absoluteFilePath();
            locallist->addMedia(QUrl::fromLocalFile(filePath));
            // qDebug() << "Processing file: " << filePath;
            TagLib::FileRef f(filePath.toStdString().c_str());
            if (!f.isNull() && f.tag()) {


                MMeta music(filePath);
                this ->MMetalist.append(music);
            }
        }
    }
}


MMeta::MMeta(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.completeSuffix();
    artist = "";
    sname = "";
    album = "";
    covpix = QPixmap();


    if (fileExtension == "m4a") {
        // 处理 m4a 文件
        TagLib::MP4::File *mp4File = new TagLib::MP4::File(QFile::encodeName(filePath).constData());
        if (!mp4File->isOpen()) {
            covpix.load(":/asset/image/logo.png");
            return;
        }

        sname = QString(mp4File->tag()->title().toCString(true));
        artist = QString(mp4File->tag()->artist().toCString(true));
        album = QString(mp4File->tag()->album().toCString(true));

        TagLib::MP4::ItemListMap itemListMap = mp4File->tag()->itemListMap();
        TagLib::MP4::Item albumArtItem = itemListMap["covr"];
        TagLib::MP4::CoverArtList albumArtList = albumArtItem.toCoverArtList();
        TagLib::MP4::CoverArt albumArt = albumArtList.front();
        TagLib::AudioProperties *audioProperties = mp4File->audioProperties();
        duration = audioProperties->lengthInSeconds(); // 获取音频时长，单位：秒


        //covpix.loadFromData((const uchar *)albumArt.data().data(), albumArt.data().size());
        covpix.loadFromData(reinterpret_cast<const uchar*>(albumArt.data().data()), albumArt.data().size());
        if (!covpix.isNull()) {
            qDebug() << "读取M4A封面信息成功";
        } else {
            covpix.load(":/asset/image/logo.png");
            qDebug() << "读取音乐封面信息失败";
        }
    } else if (fileExtension == "mp3") {
        // 处理 mp3 文件
        TagLib::MPEG::File *mpegFile = new TagLib::MPEG::File(QFile::encodeName(filePath).constData());
        if (!mpegFile->isOpen()) {
            covpix.load(":/asset/image/logo.png");
            return;
        } else {
            sname = QString(mpegFile->tag()->title().toCString(true));
            artist = QString(mpegFile->tag()->artist().toCString(true));
            album = QString(mpegFile->tag()->album().toCString(true));
            TagLib::AudioProperties *audioProperties = mpegFile->audioProperties();
            duration = audioProperties->lengthInSeconds();
            auto tag = mpegFile->ID3v2Tag(false);
            auto list = tag->frameListMap()["APIC"];
            if (!list.isEmpty()) {
                auto frame = list.front();
                auto pic = reinterpret_cast<TagLib::ID3v2::AttachedPictureFrame *>(frame);

                if (pic && !pic->picture().isNull()) {
                    QByteArray coverData(reinterpret_cast<const char *>(pic->picture().data()), pic->picture().size());

                    if (covpix.loadFromData(coverData)) {
                        qDebug() << "读取MP3封面信息成功";
                    }
                }
            } else {
                covpix.load(":/asset/image/logo.png");
                qDebug() << "读取音乐封面信息失败";
            }
        }
    }
}
