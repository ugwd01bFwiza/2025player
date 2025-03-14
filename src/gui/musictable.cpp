#include<QFileIconProvider>
#include"pathselector.h"
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
#include<QStringListModel>
MusicTable::MusicTable()
{
    this->setObjectName("localmusic");
    LoadStyleSheet();
    localMusicLayout();
    initItem();
    initLayout();



    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&MusicTable::setTheme);
    connect(playAll,&DPushButton::clicked,this, &MusicTable::onBtPlayAll);
    //connect(selectDir,&DPushButton::clicked,this, &MusicTable::bt_selectDir);
    connect(searchEdit,&DLineEdit::textChanged, this, &MusicTable::onSearchTextChange);

    connect(&MusicPlayer::instance(),&MusicPlayer::playListChanged,this,&MusicTable::resetMusicTable);
}

void MusicTable::initItem(){

    music_table = new QListWidget(this);


    music_table->setObjectName("table_music");
    QList <QString> tableList;//
    //QStandardItemModel* headmodel = new QStandardItemModel;
    music_table->setSortingEnabled(false);

    tableList << "#" << "音乐标题"  << "专辑" << "时长" ;
    music_table->setIconSize(QSize(50,50));

    //打开右键菜单属性
    music_table->setContextMenuPolicy(Qt::CustomContextMenu);

    music_table->setAlternatingRowColors(false);
    //设置表格内容不可编辑
    music_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置为行选择
    music_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置最后一栏自适应长度
    //    title_table->horizontalHeader()->setStretchLastSection(true);
    //删除网格表
    //    title_table->setShowGrid(false);
    //去除边框线
    music_table->setFrameShape(QFrame::NoFrame);
    //去除选中虚线框
    music_table->setFocusPolicy(Qt::NoFocus);

    //设置点击单元格时，表头项不高亮
    //    title_table->horizontalHeader()->setHighlightSections(false);
    //    title_table->verticalHeader()->setHighlightSections(false);
    //设置只能选中一个目标
    music_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置垂直滚动条最小宽度
    music_table->verticalScrollBar()->setMaximumWidth(7);
    music_table->setResizeMode(QListView::Adjust);
    //    title_table->verticalHeader()->setObjectName("music_verticalHeader");
    loadMusicTable();
    
    video_table = new DListView(this);
    video_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    video_table-> setViewMode(QListView::IconMode);
    video_table->   setIconSize(QSize(140, 140));
    video_table->  setGridSize(QSize(200, 200));
    video_table->   setSpacing(10);
    video_table->  setResizeMode(QListView::Adjust);
    video_table->  setMovement(QListView::Static);
    //           video_table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //            video_table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    video_table->setSpacing(30);
videoListModel = new QStandardItemModel(this);
    loadVideoTable(); 

    video_table->setModel(videoListModel);

    playAll = new DPushButton(this);
    playAll->setText("播放全部");
    playAll->setMaximumSize(100,40);
    playAll->setMinimumSize(100,40);
    playAll->setObjectName("playallBtn");
    playAll->setIcon(QIcon(":/images/stackWidget/localMusic/btn_playall.png"));




}
void MusicTable::loadMusicTable(){

    for(auto &i : MusicPlayer::instance().MMetalist){
        Addmusic(i);
    }
}
void MusicTable::loadVideoTable(){
 QString homePath = QDir::homePath();
    QString mediaPath = homePath + "/Desktop/media/";  // 拼接桌面路径和 media 文件夹

    QDir dir(mediaPath);
    if (!dir.exists()) return;

    // 只匹配常见视频格式
    QStringList filters = {"*.mp4", "*.avi", "*.mkv", "*.mov", "*.flv", "*.wmv"};
    QFileInfoList fileList = dir.entryInfoList(filters, QDir::Files);

    // 使用 Lambda 读取文件并添加到 video_table
    auto addVideoItems = [&](QFileInfoList files) {
        for (const QFileInfo &fileInfo : files) {
            // 获取文件图标
            QFileIconProvider iconProvider;
            QIcon icon = iconProvider.icon(fileInfo); // 获取文件图标

            // 检查是否获取到图标，如果没有则使用默认图标
            if (icon.isNull()) {
                icon = QIcon(":/asset/image/video2.PNG");  // 使用默认图标路径
            }

            // 创建 QStandardItem 并设置图标和名称
            QStandardItem *item = new QStandardItem(icon, fileInfo.fileName());
            //                   item->setSizeHint(QSize(160, 160)); // 设置图标大小

            // 将 item 添加到 videoListModel 中
            videoListModel->appendRow(item);
        }
    };


    // 调用 Lambda 处理文件列表
    addVideoItems(fileList);

}
void MusicTable::clearMusicTable(){
    music_table->clear();
    listDlistView.clear();
}
void MusicTable::clearVideoTable(){
    videoListModel->clear();
}

void MusicTable::localMusicLayout()
{
    //    display_HBoxLayout = new QHBoxLayout();

    //    displayLabel[0] = new DLabel(this);
    //    displayLabel[0]->setText("本地音乐");
    //    displayLabel[0]->setObjectName("localLabel");
    //    displayLabel[1] = new DLabel(this);
    //    displayLabel[1]->setText("共0首");
    //    displayLabel[1]->setObjectName("numberlabel");


    //    QSpacerItem *display_hSpacer = new QSpacerItem(200,10,
    //                                                   QSizePolicy::Expanding,
    //                                                   QSizePolicy::Expanding);

    //    display_HBoxLayout->addWidget(displayLabel[0]);
    //    display_HBoxLayout->addWidget(displayLabel[1]);
    //    display_HBoxLayout->addSpacerItem(display_hSpacer);
    //    display_HBoxLayout->addWidget(selectDir);
    //    display_HBoxLayout->addSpacing(30);
}
void MusicTable::initLayout(){

    QVBoxLayout *VLayout=new QVBoxLayout ();




    QSpacerItem *Button_HSpacer = new QSpacerItem(200,20,
                                                  QSizePolicy::Expanding,
                                                  QSizePolicy::Expanding);
    //从左到右 存储table上方控件的布局
    QHBoxLayout *button_HBoxLayout = new QHBoxLayout();
    searchEdit = new DLineEdit();
    searchEdit->setPlaceholderText("搜索本地音乐");
    searchEdit->setObjectName("localSearch");
    searchEdit->setMaximumSize(200,25);
    QAction *searchAction = new QAction(searchEdit);
    searchAction->setIcon(QIcon(":/images/stackWidget/localMusic/icon_search.png"));
    //设置ICON在搜索框右边
    searchEdit->addAction(searchAction);
    button_HBoxLayout->addWidget(playAll);
    //右边存储搜索栏和selectdir的布局

    pathSelector = new PathSelector (this);
    QVBoxLayout * right_VBoxLayout = new QVBoxLayout();

    right_VBoxLayout->addWidget(searchEdit);
    right_VBoxLayout->addWidget(pathSelector);

    button_HBoxLayout->addSpacerItem(Button_HSpacer);
    button_HBoxLayout->addLayout(right_VBoxLayout);
    qf= new QFrame();
    qf->setObjectName("tableqf");
    QVBoxLayout *temp = new QVBoxLayout();
    //temp->addLayout(display_HBoxLayout);
    //temp->addSpacing(10);
    temp->addLayout(button_HBoxLayout);
    temp->addSpacing(10);
    qf->setLayout(temp);
    //temp->setContentsMargins(10,10,0,0);
    VLayout->addWidget(qf);
    page = new QStackedWidget(this);
    page->addWidget(music_table);
    page->addWidget(video_table);
    VLayout->addWidget(page);
    //VLayout->setContentsMargins(0,0,0,0);
    VLayout->setStretch(0,1);
    VLayout->setStretch(1,8);
    this->setLayout(VLayout);
    music_table->setBackgroundRole(QPalette::NoRole);
    music_table->setSpacing(10);
}

void MusicTable::Addmusic(const MetaData&music){

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



    int row = music_table->count();

    //music_Table->setRowHeight(row,200);
    // 设置每列的值;
    // 设置第一列（序号）
    QString rowNumber = (row + 1 >= 10) ? QString::number(row + 1) : "0" + QString::number(row + 1);

    QString duration = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    // 设置第二列（标题）
    CustomListView *view = new CustomListView();
    view->tableWidget=this;
    view->number=row;
    view->url=music.url;
    QStandardItemModel *model = new QStandardItemModel(view);


    view->setModel(model);
    DStandardItem *item0 = new DStandardItem(rowNumber);
    DStandardItem *item11 = new DStandardItem();
    item11->setIcon(roundedPixmap.scaled(QSize(50,50)));
    DStandardItem *item1 = new DStandardItem(music.title);


    DStandardItem *item2 = new DStandardItem(music.album);
    DStandardItem *item3 = new DStandardItem(duration);
    view->setBackgroundType(DStyledItemDelegate::BackgroundType::NoBackground);
    view->setSelectionMode(QAbstractItemView::NoSelection);
    view->setIconSize(QSize(50,50));
    view->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    // view->setViewMode(QListView::IconMode);
    view->setOrientation(QListView::LeftToRight,false);
    view->setResizeMode(QListView::Adjust);

    view->itemdelegate = new CustomItemDelegate(view);
    view->setItemDelegate(view->itemdelegate);
    DViewItemAction *act = new DViewItemAction;

    act->setText(music.artist);
    act->setFontSize(DFontSizeManager::T8);
    act->setTextColorRole(DPalette::TextTitle );
    act->setParent(view);

    item1->setTextAlignment(Qt::AlignTop | Qt::AlignLeft);
    item1->setTextActionList({act});
    item0->setTextAlignment(Qt::AlignCenter);
    item11->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
    item0->setSizeHint(QSize(40,70));
    item11->setSizeHint(QSize(90,70));
    item1->setSizeHint(QSize(150,70));
    item2->setSizeHint(QSize(300,70));
    item3->setSizeHint(QSize(100,70));
    item0->setEditable(false);
    item11->setEditable(false);
    item1->setEditable(false);
    item2->setEditable(false);
    item3->setEditable(false);
    view->addItem(rowNumber);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model->appendRow(item0);
    model->appendRow(item11);
    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);


    QListWidgetItem* item02 = new QListWidgetItem(music_table);

    item02->setSizeHint(QSize(70,70));

    music_table->setItemWidget(item02,view);
    music_table->addItem(item02);
    listDlistView.append(view);

}void MusicTable::onBtPlayAll(){


}
QString MusicTable::getUrlFromListView(int index){
    QListWidgetItem *item = music_table->item( index);
    if (item) {

        QWidget *widget = music_table->itemWidget(item);
        if (widget) {

            CustomListView *listView = qobject_cast<CustomListView*>(widget);
            return listView->url;

        }
    }
    qDebug()<<"Can't get information from CustomListView[0]";
    return QString();
}

void MusicTable::playFromListView(int index){
    QListWidgetItem *item = music_table->item( index);
    if (item) {

        QWidget *widget = music_table->itemWidget(item);
        if (widget) {

            CustomListView *listView = qobject_cast<CustomListView*>(widget);

            listView->play();

            music_table->setCurrentRow(index);
            return ;
        }
    }
    qDebug()<<"Can't get information from CustomListView[0]";

}

void CustomListView::mouseDoubleClickEvent(QMouseEvent *event) {

    this->play();
}
void CustomListView::play(){
    MusicPlayer::instance().play(url);
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

    //    if(theme==DGuiApplicationHelper::LightType){
    //        QPalette palette = this->palette();
    //        palette.setColor(QPalette::Background, Qt::white);

    //    }else {
    //        QPalette palette = this->palette();
    //        palette.setColor(QPalette::Background,Qt::black);

    //    }
}
void MusicTable::onResetWindowSize(int width){
    windowsWidth=width;
    for(auto i : listDlistView){
        i->itemdelegate->factor=((width-900)*5/18);
        //qDebug()<<"factor:"<<i->itemdelegate->factor;
    }
}

void MusicTable::onSearchTextChange(QString text){
    for (int i = 0; i <music_table->count(); ++i) {
        bool matchFound = false;
        QListWidgetItem *item = music_table->item(i);
        if (item) {
            QWidget *widget = music_table->itemWidget(item);
            if (widget) {
                QListView *listView = qobject_cast<QListView *>(widget);
                if (listView) {
                    QModelIndex index = listView->model()->index(3, 0);
                    QString text1 = listView->model()->data(index).toString();

                    if ( text1.contains(text, Qt::CaseInsensitive)) {
                        matchFound = true;
                    }

                }
            }


        }
        music_table->setRowHidden(i, !matchFound);
    }

}
void MusicTable::resetMusicTable(){
    clearMusicTable();
    loadMusicTable();
    if (windowsWidth!=0)
    onResetWindowSize(windowsWidth);
}
void MusicTable::resetVideoTable(){
    clearVideoTable();
    loadVideoTable();
}
