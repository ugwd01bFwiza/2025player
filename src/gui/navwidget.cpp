#include "navwidget.h"
#include<DLabel>
#include<QVBoxLayout>
///左侧导航栏
NavWidget::NavWidget()
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->stackUnder(this);
    auto VLayoutLeft = new QVBoxLayout(this);
    DLabel *label1 = new DLabel(this);
    label1->setText("多媒体库");
    label1->setAlignment(Qt::AlignCenter);

    QStandardItemModel *model = new QStandardItemModel();

    auto AddItems = [&model](QIcon icon, QString name){
        DStandardItem *item = new DStandardItem(icon, name);
        item->setEditable(false);
        model->appendRow(item);
        return item;

    };

    AddItems( QIcon(":asset/image/music.png"),"Local Music");
    AddItems(QIcon(":asset/image/video.png"),"Video");
    ListView1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ListView1->setModel(model);

    VLayoutLeft->addSpacing(5);
    VLayoutLeft->addWidget(label1);
    VLayoutLeft->addSpacing(10);
    VLayoutLeft->addWidget(ListView1);

    ListView1->setItemSpacing(0);

    VLayoutLeft->addStretch(100);
     VLayoutLeft->setContentsMargins(0,0,0,0);
}
