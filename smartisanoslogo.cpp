#include "smartisanoslogo.h"
#include <DWidgetUtil> //加入此头文件方可使用moveToCenter
#include <DSearchEdit>
#include <DTitlebar>

SmartisanOsLogo::SmartisanOsLogo(DMainWindow *parent)
    : DMainWindow(parent)
{
    //初始化主窗口 Initialize the main window
    setCentralWidget(w);//将w作为窗口的用户部分（整个窗口除了标题栏的部分）
    moveToCenter(this); //把窗口移动到屏幕中间
    SmartisanOsLogo::resize(1000,900); //改变窗口大小应当改变MainWindow的大小
    SmartisanOsLogo::setMinimumSize(1000,900);
}
SmartisanOsLogo::~SmartisanOsLogo()
{
    delete w;
}
