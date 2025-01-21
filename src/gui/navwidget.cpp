#include "navwidget.h"

#include<DLabel>
#include<QVBoxLayout>
NavWidget::NavWidget()
{

    this->setAutoFillBackground(true);
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

    AddItems( QIcon(":asset/image/music.png"),"Music");
    AddItems(QIcon(":asset/image/video.png"),"Video");
    ListView1->setModel(model);
    VLayoutLeft->addSpacing(5);
    VLayoutLeft->addWidget(label1);
    VLayoutLeft->addSpacing(10);
    VLayoutLeft->addWidget(ListView1);
    ListView1->setItemSpacing(0);



}
