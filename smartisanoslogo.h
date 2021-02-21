#include <QWidget>
#include <DMainWindow>
#include <DGuiApplicationHelper>
#include <DLabel>
#include <DPushButton>
#include <DTextEdit>
#include <DGroupBox>
#include <DComboBox>
#include <DCheckBox>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <DDialog>
#include <QDateTime>
DWIDGET_USE_NAMESPACE
#ifndef DTKSERIALPORT_H
#define DTKSERIALPORT_H



class SmartisanOsLogo : public DMainWindow
{
    Q_OBJECT
public:

    SmartisanOsLogo(DMainWindow *parent = nullptr);
    ~SmartisanOsLogo();
private:
    QWidget *w=new QWidget;
    void setTheme(DGuiApplicationHelper::ColorType);
};

#endif // SMARTISANOSLOGO_H
