#include "navwidget.h"
#include<DLabel>
#include<QVBoxLayout>
#include<QFile>
///左侧导航栏
NavWidget::NavWidget()
{

    QFont chineseFont("Noto Sans CJK SC");
    this->stackUnder(this);
    this->setObjectName("navigate_frame");
    this->LoadStyleSheet(":/asset/qss/navwidget_dark.qss");

    auto VLayoutLeft = new QVBoxLayout(this);
    //VLayoutLeft->setContentsMargins(10,10,10,10);

    DLabel *label1 = new DLabel(this);

    label1->setAlignment(Qt::AlignCenter);

    QStandardItemModel *model = new QStandardItemModel();

    auto AddItems = [&model](QIcon icon, QString name){
        DStandardItem *item = new DStandardItem(icon, name);
        item->setEditable(false);
        model->appendRow(item);
        return item;

    };

    AddItems( QIcon(":asset/image/music2.png"),"Local Music");
    AddItems(QIcon(":asset/image/video2.png"),"Video");
    AddItems(QIcon(":asset/image/video2.png"),"Play History");
   // ListView1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ListView1->setModel(model);

    VLayoutLeft->addSpacing(5);
    VLayoutLeft->addWidget(label1);
    VLayoutLeft->addSpacing(10);
    VLayoutLeft->addWidget(ListView1);
    ListView1->setItemSpacing(5);

    VLayoutLeft->addStretch(100);

}
void NavWidget::LoadStyleSheet( QString url)
{
    QFile file(url);
    file.open(QIODevice::ReadOnly);

    if (file.isOpen())
    {
        QString style = this->styleSheet();
        style += QLatin1String(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}

