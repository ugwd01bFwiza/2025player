#ifndef MEDIATABLE_H
#define MEDIATABLE_H
#include<DWidget>
 DWIDGET_USE_NAMESPACE

class MusicTable : public QWidget
{
Q_OBJECT
public:
    MusicTable(QWidget *parent );
    QWidget *music = new QWidget(this);
    QWidget *video = new QWidget (this);

};

#endif // MEDIATABLE_H
