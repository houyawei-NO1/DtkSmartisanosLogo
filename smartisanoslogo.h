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
#include <QNetworkReply>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QDateTime>
DWIDGET_USE_NAMESPACE
#ifndef DTKSERIALPORT_H
#define DTKSERIALPORT_H



class SmartisanOsLogo : public DMainWindow
{
    Q_OBJECT
public:

    SmartisanOsLogo(DMainWindow *parent = nullptr);
    QPixmap setpnglabel(const QString &szUrl);
     bool downIURL_to_picture(const QString &url, const QString &fileName);
    ~SmartisanOsLogo();
     DLabel *logoPng = new DLabel;
     DPushButton *filelocation = new DPushButton();
     QString PathName,current_File;
     QDateTime current_File_time;
private:
    QWidget *w=new QWidget;
    void setTheme(DGuiApplicationHelper::ColorType);
private slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // SMARTISANOSLOGO_H
