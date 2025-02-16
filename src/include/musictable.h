#ifndef MEDIATABLE_H
#define MEDIATABLE_H
#include"musicplayer.h"
#include<QDir>
#include<DTableWidget>
#include<QStandardItemModel>
#include<QWidget>
#include<DListView>
#include<DPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<DGuiApplicationHelper>
#include<QFrame>
#include<DLabel>

#include<QListWidget>
 DWIDGET_USE_NAMESPACE

class MusicTable : public QFrame
{
Q_OBJECT
public:
    MusicTable( );

    QListWidget *title_table;
    DPushButton *playAll;
    DPushButton *selectDir;
    DLabel *displayLabel[2];
    QVBoxLayout *local_VBoxLayout;
    QHBoxLayout *display_HBoxLayout;
    QStackedWidget * page;
    QFrame *qf;
    void Addmusic(const MMeta&music);

public slots:
    void play(int index);
    void setTheme(DGuiApplicationHelper::ColorType);
private slots:
     void bt_playAll();
   // void bt_selectDir();
private:
    void LoadStyleSheet();
    void localMusicLayout();
    void initLayout();
    void initItem();
signals:
    void temp(int index);
};




class CustomListView : public DListView{
Q_OBJECT
public:
    MusicTable *tableWidget;
    int number;
    void mouseDoubleClickEvent(QMouseEvent *event) ;

};

#endif // MEDIATABLE_H
