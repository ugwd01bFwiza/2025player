#ifndef NAVWIDGET_H
#define NAVWIDGET_H

#include<DListView>
 DWIDGET_USE_NAMESPACE
 ///最左边导航栏
class NavWidget : public QFrame
{
    Q_OBJECT
public:
    NavWidget();
    DListView *ListView1=new DListView();

private:
    void LoadStyleSheet(QString url);
};

#endif // NAVWIDGET_H
