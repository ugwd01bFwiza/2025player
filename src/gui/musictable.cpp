#include "musictable.h"

#include<QVBoxLayout>
#include<DTableWidget>

#include <QHeaderView>
#include<QScrollBar>
#include<QMediaMetaData>
#include<QDebug>
#include<DStandardItem>
#include <QPainter>

MusicTable::MusicTable(QWidget *parent)
{
    QVBoxLayout *VLayout=new QVBoxLayout ();
    music_Table = new DTableWidget(this);
    QList <QString> tableList;//
    musicplayer = new MusicPlayer();
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


    VLayout->addWidget(music_Table);

    this->setLayout(VLayout);
    for (auto i:musicplayer->MMetalist)
        Addmusic(i);
    connect(music_Table, &QTableWidget::cellDoubleClicked, this, &MusicTable::play);

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



    int row = music_Table->rowCount();
    music_Table->insertRow(row);
    //music_Table->setRowHeight(row,200);
    // 设置每列的值;
    // 设置第一列（序号）
       QString rowNumber = (row + 1 >= 10) ? QString::number(row + 1) : "0" + QString::number(row + 1);
       music_Table->setItem(row, 0, new QTableWidgetItem(rowNumber));  // 第一列为序号

       // 设置第二列（标题）
       ListView *view = new ListView();
       view->setParent(music_Table);
       QStandardItemModel *model = new QStandardItemModel(view);
       view->setModel(model);
       DStandardItem *item = new DStandardItem(roundedPixmap.scaled(QSize(50,50)),music.sname);
       //item->setData(QColor(Qt::transparent), Qt::BackgroundRole);
       item->setEditable(false);
       view->tableWidget=music_Table;

       view->setBackgroundType(DStyledItemDelegate::BackgroundType::NoBackground);
       view->setSelectionMode(QAbstractItemView::NoSelection);
       view->setFixedSize(QSize(300,70));
       view->setIconSize(QSize(50,50));
       view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


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
void MusicTable::play(int row, int _column){

       this->musicplayer->locallist->setCurrentIndex(row);
       this->musicplayer->play();

}
QTableWidget *findTableWidgetParent(QWidget *widget) {
    while (widget) {
        QTableWidget *table = qobject_cast<QTableWidget *>(widget);
        if (table) return table;
        widget = widget->parentWidget();
    }
    return nullptr;
}
void ListView::mouseDoubleClickEvent(QMouseEvent *event) {

    // 计算当前 ListView 在 QTableWidget 中的位置
    QPoint globalPos = this->mapTo(tableWidget, QPoint(0, 0));
    QModelIndex index = tableWidget->indexAt(globalPos);

    if (index.isValid()) {
        emit tableWidget->cellDoubleClicked(index.row(), index.column());
    }

    QListView::mouseDoubleClickEvent(event);
}


