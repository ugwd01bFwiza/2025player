#ifndef MEDIATABLE_H
#define MEDIATABLE_H
#include"musicplayer.h"
#include<QDir>
#include<DTableWidget>
#include<QStandardItemModel>
#include<QWidget>
#include<DListView>
 DWIDGET_USE_NAMESPACE

class MusicTable : public QWidget
{
Q_OBJECT
public:
    MusicTable(QWidget *parent );
    DTableWidget *music_Table;
    MusicPlayer *musicplayer;
    void Addmusic(const MMeta&music);
public slots:
    void play(int row, int column);

};
class ListView : public DListView{
Q_OBJECT
public:
    QTableWidget *tableWidget;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // MEDIATABLE_H
