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
    a.setApplicationName("dtk_Smartisanos图标下载助手");
    a.setApplicationVersion("0.01");
    a.setProductIcon(QIcon(":/images/hyw.ico"));
    a.setProductName("DTK_Smartisanos图标下载助手");
    a.setApplicationDescription("这是一个DTK_Smartisanos图标下载助手应用");

    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DtkSerialport"));


    DApplicationSettings as;
    Q_UNUSED(as)

    SmartisanOsLogo S;
    S.show();

    Dtk::Widget::moveToCenter(&S);

    return a.exec();
}
