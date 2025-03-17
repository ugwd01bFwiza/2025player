///所有的多媒体文件都在这里展示,page目前存储了音视频页面
#ifndef MEDIATABLE_H
#define MEDIATABLE_H
#include"musicplayer.h"
#include"pathselector.h"
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
#include<QItemDelegate>
#include<QListWidget>
#include<DLineEdit>
#include<QStackedWidget>
 DWIDGET_USE_NAMESPACE
 class CustomListView;  
 class MusicTable : public QFrame {
     Q_OBJECT
 public:
     MusicTable();

     DListWidget *music_table;
     DListView *video_table;


     DListView *historyTable;
     DPushButton *playAll;
     DLineEdit *searchEdit ;
//     DLabel *displayLabel[2];
//     QVBoxLayout *local_VBoxLayout;
     PathSelector*pathSelector;
     QHBoxLayout *display_HBoxLayout;
     QStackedWidget *page;
     QList<CustomListView*> listDlistView;
     QFrame *qf;
     QStandardItemModel*videoListModel;
     QStandardItemModel*historyListModel;
     int windowsWidth=0;


       void addmusic(const MetaData& music);
     void onResetWindowSize(int width);
  QString getUrlFromListView(int index);
///Controlbar的上一曲下一曲会经过这里
  void playFromListView(int index);
 public slots:
         void setTheme(DGuiApplicationHelper::ColorType);
         void clearMusicTable();
         void loadMusicTable();
         void clearVideoTable();
         void loadVideoTable();
         void loadHistoryTable();
         void resetMusicTable();
         void resetVideoTable();

         void onHistoryListRemove(int index);
       void addHistoryItem(const HistoryMData& item);

 private slots:
     void onBtPlayAll();
     // void bt_selectDir();
     void onSearchTextChange(QString text);

 private:

  const int MAX_HISTORY = 100; // 限制历史记录数量
     void LoadStyleSheet();
     void localMusicLayout();
     void initLayout();
     void initItem();
     void initSource();

    signals:
     void temp(int index);
 };

 ///调整Dlistview项间距
class CustomItemDelegate : public QItemDelegate {
public:
    int factor = 1;
    CustomItemDelegate(QObject *parent = nullptr) : QItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {

        QItemDelegate::paint(painter, option, index);
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QItemDelegate::sizeHint(option, index);
        if(size.width()>=100)
        size.setWidth(size.width() +factor);
        return size;
    }
};
class CustomListView : public DListView {
    Q_OBJECT
public:
    QString url;
    MusicTable *tableWidget;
    CustomItemDelegate *itemdelegate;
    int number;
    void mouseDoubleClickEvent(QMouseEvent *event);

    void play();
};
class HistoryTable : public DListView {
    Q_OBJECT
public:
    QString url;
    MusicTable *tableWidget;
    
    int number;
    void mouseDoubleClickEvent(QMouseEvent *event);

    void play();
};
#endif // MEDIATABLE_H
