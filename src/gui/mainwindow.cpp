#include "mainwindow.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<DPushButton>
#include<DLabel>
#include<DScrollBar>
#include<DTitlebar>
#include <DWidgetUtil>
#include<DPaletteHelper>
#include<DScrollArea>
MainWindow::~MainWindow() {
    delete cw;
    delete Navw;
    delete MainVLayout;
    delete UpHLayout;
    delete DownHLayout;
    delete RightHLayout;
}
MainWindow::MainWindow()

{
    this->titlebar()->setSeparatorVisible(false);
    this->titlebar()->setAutoHideOnFullscreen(true);
    this->titlebar()->setIcon(QIcon(":asset/image/logo.png"));
    this->titlebar()->setTitle("Muiltimedia Player");
    this->titlebar()->setFixedHeight(60);
    this->setWindowRadius (10);
    this->setMinimumSize(QSize(900, 600));
    Navw->setAutoFillBackground(true);
    cbar->setAutoFillBackground(true);

    moveToCenter(this); //把窗口移动到屏幕中间
    //把主窗口分为上下两个垂直布局

    ;

    cw->setLayout(MainVLayout);

    MainVLayout->setContentsMargins(0, 0, 0, 0);
    MainVLayout->addSpacing(5);
    MainVLayout->addLayout(UpHLayout);
    MainVLayout->addLayout(DownHLayout);
    UpHLayout->addWidget(Navw);
    UpHLayout->addLayout(RightHLayout);



    DownHLayout->addWidget(cbar);

    UpHLayout->setStretch(0, 2);
    UpHLayout->setStretch(1, 7);
    MainVLayout->setStretch(0, 9);
    MainVLayout->setStretch(1, 1);
    this->setCentralWidget(cw);
    //切换主题
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged,this,&MainWindow::setTheme);
    //对应左侧导航栏
    connect(Navw->ListView1->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::currentchange);
    Navw->ListView1->setCurrentIndex(Navw->ListView1->model()->index(0, 0));
    this->setTheme(DGuiApplicationHelper::instance()->themeType());
}

 ///深色浅色两套主题的颜色/图标设置
void MainWindow::setTheme(DGuiApplicationHelper::ColorType theme)
{

    if(theme==DGuiApplicationHelper::LightType){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background,Qt::white);
        Navw->setPalette(palette);
        palette.setColor(QPalette::Base,Qt::white);
        cbar->setPalette(palette);
    }else {
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background,Qt::black);
        Navw->setPalette(palette);
        cbar->setPalette(palette);
    }
}
void MainWindow::currentchange(const QModelIndex &current,const QModelIndex &previous)
{
    int row=current.row();
    int rowp=previous.row();
    if(rowp!=-1){
        while (QLayoutItem *item = RightHLayout->takeAt(0)){
            QWidget *widget = item->widget();
                   if (widget) {
                       widget->deleteLater();
                   }
        }
    }
    if (row==0)
    {

        MusicTable *mediatable = new MusicTable(this);
        RightHLayout->addWidget(mediatable);
    }
    else if(row==1){
        //todo scrollarea
        DPushButton *ts2=new DPushButton(this);
        ts2->setText("视频");
        RightHLayout->addWidget(ts2);
    }
}
