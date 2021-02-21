#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <smartisanoslogo.h>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
   // DApplication::loadDXcbPlugin();
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("dtk串口助手");
    a.setApplicationVersion("0.5");
    a.setProductIcon(QIcon(":/images/hyw.ico"));
    a.setProductName("DTK串口助手");
    a.setApplicationDescription("这是一个DTK串口助手应用");

    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DtkSerialport"));

    // 保存程序的窗口主题设置
    DApplicationSettings as;
    Q_UNUSED(as)

//    DMainWindow w;
//   w.show();


//    DtkSerialport d;
//    d.show();
SmartisanOsLogo S;
S.show();

   // Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
