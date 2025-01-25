#include "musictable.h"
#include<QVBoxLayout>
#include<DTableWidget>
#include <QHeaderView>
#include<QScrollBar>
MusicTable::MusicTable(QWidget *parent)
{
   QVBoxLayout *VLayout=new QVBoxLayout ();
   DTableWidget *music_Table = new DTableWidget(this);
   QList <QString> tableList;
   tableList << "#" << "音乐标题"  << "专辑" << "时长" ;
   music_Table->setColumnCount(4);
   music_Table->setHorizontalHeaderLabels(tableList);
   music_Table->setColumnWidth(0,10);
   music_Table->setColumnWidth(1,300);
   music_Table->setColumnWidth(2,200);
   music_Table->setColumnWidth(4,70);
   //打开右键菜单属性
   music_Table->setContextMenuPolicy(Qt::CustomContextMenu);
   //开启交替行背景色
   music_Table->setAlternatingRowColors(true);
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
   //设置点击表头进行排序
   music_Table->setSortingEnabled(true);
   //设置表头字体向左靠齐
   music_Table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
   //设置点击单元格时，表头项不高亮
   music_Table->horizontalHeader()->setHighlightSections(false);
   music_Table->verticalHeader()->setHighlightSections(false);
   //设置只能选中一个目标
   music_Table->setSelectionMode(QAbstractItemView::SingleSelection);
   //设置垂直滚动条最小宽度
   music_Table->verticalScrollBar()->setMaximumWidth(7);

   music_Table->verticalHeader()->setAlternatingRowColors(true);
   music_Table->verticalHeader()->setObjectName("music_verticalHeader");
   music_Table->verticalHeader()->setDefaultSectionSize(30);
   music_Table->verticalHeader()->setVisible(false);



   VLayout->addWidget(music_Table);

   this->setLayout(VLayout);
}
