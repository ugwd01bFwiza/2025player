#include "musictable.h"
#include<QVBoxLayout>
#include<DTableWidget>
#include<DListView>
#include <QHeaderView>
#include<QScrollBar>
#include<QMediaMetaData>
#include<QDir>
#include<QDebug>
#include<DStandardItem>
#include <fileref.h>
#include<tag.h>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include <mpegfile.h>
#include <mp4file.h>
#include <QPainter>
MusicTable::MusicTable(QWidget *parent)
{
    QVBoxLayout *VLayout=new QVBoxLayout ();
    music_Table = new DTableWidget(this);
    QList <QString> tableList;//

    //QStandardItemModel* headmodel = new QStandardItemModel;


    music_Table->setSortingEnabled(false);
    music_Table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableList << "#" << "音乐标题"  << "专辑" << "时长" ;
    music_Table->setColumnCount(4);
    music_Table->setHorizontalHeaderLabels(tableList);
    music_Table->setColumnWidth(0,20);
    music_Table->setColumnWidth(1,300);
    music_Table->setColumnWidth(2,200);
    music_Table->setColumnWidth(3,70);
    music_Table->verticalHeader()->setVisible(false);
    //行高
    music_Table->verticalHeader()->setDefaultSectionSize(70);
    music_Table->setIconSize(QSize(50,50));
    music_Table->verticalHeader()->setHighlightSections(false);
    //设置垂直标题布局
    music_Table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

    music_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //设置表头字体向左靠齐
    music_Table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    music_Table->verticalHeader()->setAlternatingRowColors(false);
    //设置标题行行高
    music_Table->setRowHeight(0,30);
    //打开右键菜单属性
    music_Table->setContextMenuPolicy(Qt::CustomContextMenu);

    music_Table->setAlternatingRowColors(false);
    //设置表格内容不可编辑
    music_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置为行选择
    music_Table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置最后一栏自适应长度
    music_Table->horizontalHeader()->setStretchLastSection(true);
    //删除网格表
    music_Table->setShowGrid(false);
    //去除边框线
    music_Table->setFrameShape(QFrame::NoFrame);
    //去除选中虚线框
    music_Table->setFocusPolicy(Qt::NoFocus);

    //设置点击单元格时，表头项不高亮
    music_Table->horizontalHeader()->setHighlightSections(false);
    music_Table->verticalHeader()->setHighlightSections(false);
    //设置只能选中一个目标
    music_Table->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置垂直滚动条最小宽度
    music_Table->verticalScrollBar()->setMaximumWidth(7);

    music_Table->verticalHeader()->setObjectName("music_verticalHeader");



   // music_Table->setStyleSheet("QTableView::item { padding-top: 20px; }");

    ReadMediaFile();
    VLayout->addWidget(music_Table);

    this->setLayout(VLayout);
}

///读取本地媒体文件

void MusicTable::ReadMediaFile() {
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
            // qDebug() << "Processing file: " << filePath;
            TagLib::FileRef f(filePath.toStdString().c_str());
            if (!f.isNull() && f.tag()) {


                MMeta music(filePath);
                MMetalist.append(music);
                int minutes = music.duration / 60;
                int seconds = music.duration % 60;
                QPixmap roundedPixmap(music.covpix.size());
                roundedPixmap.fill(Qt::transparent);  // 设置透明背景

                   // 绘制圆角矩形
                   QPainter painter(&roundedPixmap);
                   painter.setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
                   painter.setBrush(QBrush(music.covpix));
                   painter.setPen(Qt::NoPen);  // 不需要边框
                   painter.drawRoundedRect(0, 0, music.covpix.width(), music.covpix.height(), 100, 100);  // 绘制圆角矩形
                   painter.end();



                int row = music_Table->rowCount();
                music_Table->insertRow(row);
                //music_Table->setRowHeight(row,200);
                // 设置每列的值;
                // 设置第一列（序号）
                   QString rowNumber = (row + 1 >= 10) ? QString::number(row + 1) : "0" + QString::number(row + 1);
                   music_Table->setItem(row, 0, new QTableWidgetItem(rowNumber));  // 第一列为序号

                   // 设置第二列（标题）
                   DListView *view = new DListView();
                   QStandardItemModel *model = new QStandardItemModel(view);
                   view->setModel(model);
                   DStandardItem *item = new DStandardItem(roundedPixmap.scaled(QSize(50,50)),music.sname);
                  item->setData(QColor(Qt::transparent), Qt::BackgroundRole);

                   //item->setData(QColor(Qt::transparent), Qt::DecorationRole);
                  view->setStyleSheet("QListView::item {"
                                      "  margin: 0px;"  // 移除内边距
                                      "  padding: 0px;" // 移除外边距
                                      "  border: none;"
                                      "}");

                   view->setFixedSize(QSize(300,70));
                   view->setIconSize(QSize(50,50));
                   view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
                   view->setEnabled(false);


                   //view->setAutoFillBackground(true);
                   DViewItemAction *act = new DViewItemAction;
                   item->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
                   act->setText(music.artist);
                   act->setFontSize(DFontSizeManager::T8);
                   act->setTextColorRole(DPalette::TextTips);
                   act->setParent(this);
                   item->setTextActionList({act});
                   model->appendRow(item);
                   music_Table->setCellWidget(row,1,view);

                   // 设置第三列（专辑）
                   music_Table->setItem(row, 2, new QTableWidgetItem(music.album));  // Album

                   // 设置第四列（时长）
                   QString duration = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
                   music_Table->setItem(row, 3, new QTableWidgetItem(duration));  // Duration



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


        covpix.loadFromData((const uchar *)albumArt.data().data(), albumArt.data().size());

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

