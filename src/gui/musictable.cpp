#include "musictable.h"
#include<QVBoxLayout>
#include<DTableWidget>
#include <QHeaderView>
#include<QScrollBar>
#include<QMediaMetaData>
#include<QDebug>
#include<DStandardItem>
#include <QPainter>
#include<DLineEdit>
#include<DFileDialog>
#include<QListWidget>
#include <QMouseEvent>

MusicTable::MusicTable()
{
    this->setObjectName("localmusic");
    LoadStyleSheet();
    localMusicLayout();
    initItem();
    initLayout();



   connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&MusicTable::setTheme);
   connect(title_table, &QListWidget::itemDoubleClicked, this, &MusicTable::play);
   connect(playAll,&DPushButton::clicked,this, &MusicTable::bt_playAll);
   //connect(selectDir,&DPushButton::clicked,this, &MusicTable::bt_selectDir);
}

void MusicTable::initItem(){

    title_table = new QListWidget(this);


    title_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    title_table->setObjectName("table_music");
    QList <QString> tableList;//
    //QStandardItemModel* headmodel = new QStandardItemModel;
    title_table->setSortingEnabled(false);
    title_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    tableList << "#" << "音乐标题"  << "专辑" << "时长" ;
    title_table->setIconSize(QSize(50,50));

    //打开右键菜单属性
    title_table->setContextMenuPolicy(Qt::CustomContextMenu);

    title_table->setAlternatingRowColors(false);
    //设置表格内容不可编辑
    title_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置为行选择
    title_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置最后一栏自适应长度
//    title_table->horizontalHeader()->setStretchLastSection(true);
    //删除网格表
//    title_table->setShowGrid(false);
    //去除边框线
    title_table->setFrameShape(QFrame::NoFrame);
    //去除选中虚线框
    title_table->setFocusPolicy(Qt::NoFocus);

    //设置点击单元格时，表头项不高亮
//    title_table->horizontalHeader()->setHighlightSections(false);
//    title_table->verticalHeader()->setHighlightSections(false);
    //设置只能选中一个目标
    title_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置垂直滚动条最小宽度
    title_table->verticalScrollBar()->setMaximumWidth(7);
     title_table->setResizeMode(QListView::Adjust);
//    title_table->verticalHeader()->setObjectName("music_verticalHeader");
    auto &musicplayer=MusicPlayer::instance();
    for (auto i:musicplayer.MMetalist)
        Addmusic(i);


    playAll = new DPushButton(this);
    playAll->setText("播放全部");
    playAll->setMaximumSize(100,40);
    playAll->setMinimumSize(100,40);
    playAll->setObjectName("playallBtn");
    playAll->setIcon(QIcon(":/images/stackWidget/localMusic/btn_playall.png"));




}
void MusicTable::localMusicLayout()
{
    display_HBoxLayout = new QHBoxLayout();

    displayLabel[0] = new DLabel(this);
    displayLabel[0]->setText("本地音乐");
    displayLabel[0]->setObjectName("localLabel");
    displayLabel[1] = new DLabel(this);
    displayLabel[1]->setText("共0首");
    displayLabel[1]->setObjectName("numberlabel");
    selectDir = new DPushButton(this);
    selectDir->setText("选择目录");
    selectDir->setObjectName("selectButton");
    selectDir->setCursor(Qt::PointingHandCursor);


    QSpacerItem *display_hSpacer = new QSpacerItem(200,10,
                                                   QSizePolicy::Expanding,
                                                   QSizePolicy::Expanding);

    display_HBoxLayout->addWidget(displayLabel[0]);
    display_HBoxLayout->addWidget(displayLabel[1]);
    display_HBoxLayout->addSpacerItem(display_hSpacer);
    display_HBoxLayout->addWidget(selectDir);
    display_HBoxLayout->addSpacing(30);
}
void MusicTable::initLayout(){
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout *VLayout=new QVBoxLayout ();




    QSpacerItem *Button_HSpacer = new QSpacerItem(200,20,
                                                  QSizePolicy::Expanding,
                                                  QSizePolicy::Expanding);
    QHBoxLayout *button_HBoxLayout = new QHBoxLayout();
     DLineEdit *searchEdit = new DLineEdit();
    searchEdit->setPlaceholderText("搜索本地音乐");
    searchEdit->setObjectName("localSearch");
    searchEdit->setMaximumSize(200,25);
    QAction *searchAction = new QAction(searchEdit);
    searchAction->setIcon(QIcon(":/images/stackWidget/localMusic/icon_search.png"));
    //设置ICON在搜索框右边
    searchEdit->addAction(searchAction);
    button_HBoxLayout->addWidget(playAll);

    button_HBoxLayout->addSpacerItem(Button_HSpacer);
    button_HBoxLayout->addWidget(searchEdit);
    qf= new QFrame();
    qf->setObjectName("tableqf");
    QVBoxLayout *temp = new QVBoxLayout();
    temp->addLayout(display_HBoxLayout);
    temp->addSpacing(10);
    temp->addLayout(button_HBoxLayout);
    temp->addSpacing(10);
    qf->setLayout(temp);
    temp->setContentsMargins(10,10,0,0);
    VLayout->addWidget(qf);
    VLayout->addWidget(title_table);
    VLayout->setContentsMargins(0,0,0,0);
    VLayout->setStretch(0,1);
    VLayout->setStretch(1,8);
    this->setLayout(VLayout);
    title_table->setBackgroundRole(QPalette::NoRole);
    title_table->setSpacing(10);
}

void MusicTable::Addmusic(const MMeta&music){

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



       int row = title_table->count();

     //music_Table->setRowHeight(row,200);
    // 设置每列的值;
    // 设置第一列（序号）
       QString rowNumber = (row + 1 >= 10) ? QString::number(row + 1) : "0" + QString::number(row + 1);

       QString duration = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
       // 设置第二列（标题）
       CustomListView *view = new CustomListView();
       view->tableWidget=title_table;
       QStandardItemModel *model = new QStandardItemModel(view);


       view->setModel(model);
       DStandardItem *item0 = new DStandardItem(rowNumber);
       DStandardItem *item11 = new DStandardItem();
       item11->setIcon(roundedPixmap.scaled(QSize(50,50)));
       DStandardItem *item1 = new DStandardItem(music.sname);


       DStandardItem *item2 = new DStandardItem(music.album);
       DStandardItem *item3 = new DStandardItem(duration);
       view->setBackgroundType(DStyledItemDelegate::BackgroundType::NoBackground);
       view->setSelectionMode(QAbstractItemView::NoSelection);
       view->setIconSize(QSize(50,50));
       view->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
      // view->setViewMode(QListView::IconMode);
       view->setOrientation(QListView::LeftToRight,false);
       view->setResizeMode(QListView::Adjust);

       DViewItemAction *act = new DViewItemAction;

       act->setText(music.artist);
       act->setFontSize(DFontSizeManager::T8);
       act->setTextColorRole(DPalette::TextTitle );
       act->setParent(this);
       item1->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
       item1->setTextActionList({act});
       item0->setTextAlignment(Qt::AlignCenter);
       item11->setTextAlignment(Qt::AlignCenter);
       item1->setTextAlignment(Qt::AlignCenter);
       item2->setTextAlignment(Qt::AlignCenter);
       item3->setTextAlignment(Qt::AlignCenter);
       item0->setSizeHint(QSize(40,70));
       item1->setSizeHint(QSize(150,70));
       item11->setSizeHint(QSize(90,70));
       item2->setSizeHint(QSize(300,70));
       item3->setSizeHint(QSize(70,70));
       item0->setEditable(false);
       item11->setEditable(false);
       item1->setEditable(false);
       item2->setEditable(false);
       item3->setEditable(false);
       view->addItem(rowNumber);

       model->appendRow(item0);
       model->appendRow(item11);
       model->appendRow(item1);
       model->appendRow(item2);
       model->appendRow(item3);


       QListWidgetItem* item02 = new QListWidgetItem(title_table);

       item02->setSizeHint(QSize(70,70));

       title_table->setItemWidget(item02,view);
       title_table->addItem(item02);
}
 void MusicTable::play(QListWidgetItem *item) {

        int row = title_table->row(item);

       auto &musicplayer=MusicPlayer::instance();
       musicplayer.locallist->setCurrentIndex(row);
       musicplayer.play();
}
void MusicTable::bt_playAll(){
    auto &musicplayer=MusicPlayer::instance();
    musicplayer.locallist->setCurrentIndex(0);
    musicplayer.play();
}


void CustomListView::mouseDoubleClickEvent(QMouseEvent *event) {

    //QPoint globalPos = this->mapTo(tableWidget, QPoint(0, 0));
    QPoint pos = event->pos();

    QListWidgetItem *item = tableWidget->itemAt(pos);

    if (item) {

        emit tableWidget->itemDoubleClicked(item);

    }

     QListView::mouseDoubleClickEvent(event);
}

void MusicTable::LoadStyleSheet()
{
    QFile file(":/asset/qss/musictb.qss");
    file.open(QIODevice::ReadOnly);

    if (file.isOpen())
    {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}

void MusicTable::setTheme(DGuiApplicationHelper::ColorType theme){

    if(theme==DGuiApplicationHelper::LightType){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background, Qt::white);

    }else {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background,Qt::black);
        this->setPalette(palette);
        this->setAutoFillBackground(true);
    }
}
//void MusicTable::bt_selectDir(){
//    //获取绝对位置x,y
//    int x = this->parentWidget()->parentWidget()->parentWidget()->mapToGlobal(QPoint(0,0)).rx() +
//            parentWidget()->parentWidget()->parentWidget()->width()/2 -
//            450/2;
//    int y = this->parentWidget()->parentWidget()->parentWidget()->mapToGlobal(QPoint(0,0)).ry() +
//            parentWidget()->parentWidget()->parentWidget()->height()/2 -
//            300/2;
//    DFileDialog * fileDialog=new DFileDialog(this,"选择本地音乐目录",MusicPlayer::instance();
//    fileDialog->move(x,y);
//    int ret = fileDialog->exec();


//    delete fileDialog;
//}

