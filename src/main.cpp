#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>
#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
#include <DApplicationHelper>
#include <QLoggingCategory>
//#include<QTextCodec>
#include "mainwindow.h"
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
    a.setOrganizationName("deepin");
    a.setApplicationName("dtk-application");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon(":/images/logo.png"));
    a.setProductName("Dtk Application");
    a.setApplicationDescription("This is a dtk template application.");
    //a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DTK Application"));
    DApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    // 保存程序的窗口主题设置
    DApplicationHelper *helper = DApplicationHelper::instance();
    Q_UNUSED(helper);

    MainWindow w;


    w.show();
    return a.exec();
}
