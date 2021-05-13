#include "smartisanoslogo.h"
#include <DWidgetUtil>
#include <DSearchEdit>
#include <DTitlebar>
#include <QNetworkAccessManager>
static int num=0;
SmartisanOsLogo::SmartisanOsLogo(DMainWindow *parent)
    : DMainWindow(parent)
{

    setCentralWidget(w);
    moveToCenter(this);
    SmartisanOsLogo::resize(900,700);
    SmartisanOsLogo::setMinimumSize(900,700);
    static bool Is_Cancel=false;

    QDir currDir = QCoreApplication::applicationDirPath();
    //currDir.cdUp();
    QString m_savePath = currDir.path();
    QString filenameText = m_savePath;
    filenameText.append("/allapp.json");


    QHBoxLayout *hlayout =new QHBoxLayout(w);
    QVBoxLayout *v1layout = new QVBoxLayout(w);
    QHBoxLayout *modelayout = new QHBoxLayout(w);
    DLabel *mode = new DLabel;
    mode->setText("①下载模式:");
    mode->setAlignment(Qt::AlignCenter);
    DComboBox *modecombobox= new DComboBox;
    modecombobox->addItem("单应用图标下载");
    modecombobox->addItem("常见应用图标批量下载");
    modecombobox->addItem("系统应用图标下载");
    QHBoxLayout *namelayout = new QHBoxLayout(w);
    DLabel *name = new DLabel;
    name->setText("②应用名称：");
    name->setAlignment(Qt::AlignCenter);
    DLineEdit *nameLineEdit = new DLineEdit;
    QHBoxLayout *locationlayout = new QHBoxLayout(w);
    DLabel *location = new DLabel;
    location->setText("③下载位置：");
    location->setAlignment(Qt::AlignCenter);
    DLineEdit *locationLineEdit = new DLineEdit;
    filelocation->setText("选择");
    QHBoxLayout *logolayout = new QHBoxLayout(w);
    DLabel *logo = new DLabel;
    logo->setText("图标预览：");
    logo->setAlignment(Qt::AlignCenter);
    titlebar()->setIcon(QIcon(":/images/iconfinder-icon.svg"));




    //logoPng->setPixmap(setpnglabel("http://icon.smartisan.com/drawable/com.sina.weibo/logo.png"));


    QVBoxLayout *v2layout = new QVBoxLayout(w);
    DLabel *Smartisan = new DLabel();
    Smartisan->setAlignment(Qt::AlignHCenter);
   // Smartisan ->setText("Smartisan");
    QImage *img=new QImage;
    img->load(":/images/smartisanos.png");
    Smartisan->setPixmap(QPixmap::fromImage(*img));
    DPushButton *Download = new DPushButton();
    Download->setText("预览并下载");
    DPushButton *Cancel = new DPushButton();
    Cancel->setText("取消下载");
    Cancel->setDisabled(true);

    //DTextEdit *messageBox2 = new DTextEdit;

    hlayout->addLayout(v1layout,6);
    v1layout->addStretch(1);
    v1layout->addLayout(modelayout);
    modelayout->addWidget(mode,2);
    modelayout->addWidget(modecombobox,6);
    modelayout->addStretch(1);
    v1layout->addStretch(1);
    v1layout->addLayout(namelayout);
    namelayout->addWidget(name,2);
    namelayout->addWidget(nameLineEdit,6);
    namelayout->addStretch(1);
    v1layout->addStretch(1);
    v1layout->addLayout(locationlayout);
    locationlayout->addWidget(location,2);
    locationlayout->addWidget(locationLineEdit,5);
    locationlayout->addWidget(filelocation,1);
    locationlayout->addStretch(1);
    v1layout->addStretch(1);
    v1layout->addLayout(logolayout);
    logolayout->addWidget(logo,2);
    logolayout->addWidget(logoPng,6);
    logolayout->addStretch(1);
    v1layout->addStretch(5);
    hlayout->addLayout(v2layout,5);
   //
    v2layout->addWidget(Smartisan,1);
    v2layout->addStretch(1);
    v2layout->addWidget(Download,3);
    v2layout->addWidget(Cancel,3);
    v2layout->addStretch(2);

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl("http://setting.smartisan.com/app/icon/"));
    request.setRawHeader("Content-Type", "application/json;charset=utf8");



     connect(modecombobox, &DComboBox::currentTextChanged, this, [ = ] {
         switch (modecombobox->currentIndex()) {

             case 0:
             {
               mode->setText("①下载模式:");
               nameLineEdit->show();
               name->setText("②应用名称：");
               location->setText("③下载位置：");

             }
             break;

             case 1:
            {
             name->setText(" ");
             nameLineEdit->hide();
             location->setText("②下载位置：");

            }
             break;

             case 2:
            {
             name->setText(" ");
             nameLineEdit->hide();
             location->setText("②下载位置：");
             Download->setText("打包下载");
             logo->setText("");
            }
              break;

         }
     });

        //download button
        connect(Download, &DPushButton::clicked, this, [ = ] {


            switch (modecombobox->currentIndex()) {

                case 0:
                {
                    QString packagename = nameLineEdit->text();
                    PKG_NAME = packagename;
                    //"com.sina.weibo" ;
                    QJsonObject obj;
                    obj.insert("package",packagename);
                    QJsonDocument jsonDoc(obj);
                    QNetworkReply* reply = accessManager->post(request, '[' + jsonDoc.toJson(QJsonDocument::Compact) + ']');
                    if (reply->isFinished())
                        reply->deleteLater();
                }
                break;

                case 1:
               {
                Cancel->setEnabled(true);
                Is_Cancel=false;
                QFile file(filenameText);
                if(file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                    QString value = file.readAll();
                    file.close();
                    QJsonParseError parseJsonErr;
                    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);

                    if (! (parseJsonErr.error == QJsonParseError::NoError)) {
                        //QMessageBox::about(NULL, "提示", "配置文件错误！");
                        DDialog dlg("提示", "配置文件错误！");
                        dlg.addButton("好的", true, DDialog::ButtonWarning);
                        dlg.setIcon(QIcon(":/images/hyw.ico"));
                        dlg.exec();
                        return;
                    }


                    QJsonObject jsonObject = document.object();
                    QJsonObject::Iterator it;
                    QString keyString="";
                    QString valueString="";

                    for(it=jsonObject.begin();it!=jsonObject.end();it++)
                       {
//                           QString value=it.value().toString();
//                           keyString=it.key()+","+keyString;
//                           valueString="'"+value+"',"+valueString;
                             qDebug()<<"======================================"<<it.key()<<endl;
                             QString packagename = it.key();
//                             QString packagename = "com.sina.weibo" ;
                             PKG_NAME = packagename;
                             QJsonObject obj;
                             obj.insert("package",packagename);
                             QJsonDocument jsonDoc(obj);
                             QNetworkReply* reply = accessManager->post(request, '[' + jsonDoc.toJson(QJsonDocument::Compact) + ']');
                             name->setText("已下载图片"+QString::number(num)+"张");
                             if (reply->isFinished())
                                 reply->deleteLater();
                             QEventLoop loop;
                             QTimer::singleShot(150,&loop,SLOT(quit()));
                             loop.exec();
                             if(Is_Cancel==true)return;

                       }
                    num=0;
//                       keyString=keyString.left(keyString.length()-1);
//                       valueString=valueString.left(valueString.length()-1);

                }
                else {
                    //QMessageBox::about(NULL, "提示", "未找到文件allapp.json");
                    DDialog dlg("提示", "未找到文件allapp.json");
                    dlg.addButton("好的", true, DDialog::ButtonWarning);
                    dlg.setIcon(QIcon(":/images/hyw.ico"));
                    dlg.exec();
                    return;
                }

               }
                break;

                case 2:
               {
//                QString url= "https://raw.fastgit.org/houyawei-NO1/DtkSmartisanosLogo/main/DT2002C_%E5%9D%9A%E6%9E%9CR2/CloudSyncShare_8.1.3.png";
                QString url="https://raw.fastgit.org/houyawei-NO1/DtkSmartisanosLogo/main/DT2002C_%E5%9D%9A%E6%9E%9CR2.zip";
                QString name = PathName + '/' + "SmartianOS系统应用图标" + ".zip";
                downIURL_to_picture(url,name);
               }
                break;

            }


        });


        //file location choose button
        connect(filelocation, &DPushButton::clicked, this, [ = ] {
               QDir dir= QCoreApplication::applicationDirPath();
               dir.cdUp();
               PathName = dir.path();
               dir.mkdir("png");
               PathName = QFileDialog::getExistingDirectory(this, tr("选择下载路径"),
                                                            PathName+"/png/",
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);
               locationLineEdit->setText(PathName);
        });

        //cancel download status
        connect(Cancel,&DPushButton::clicked,this,[ = ]{
            if(Is_Cancel==false)
            {
                Is_Cancel=true;
                Cancel->setDisabled(true);
            }
//            if(Is_Cancel==false)
//            {
//                Is_Cancel=true;
//            }
        });


}
SmartisanOsLogo::~SmartisanOsLogo()
{
    delete w;
}
void SmartisanOsLogo::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
         {
             QByteArray bytes = reply->readAll();
//             QString urlpng = QString(bytes);
//             QStringList urlpngList=urlpng.split(QRegExp("[\"]"));
//             qDebug()<<"urlpngList"<<urlpngList[9];
//             logoPng->setPixmap(setpnglabel(urlpngList[9]));
//             if(urlpngList[9].size()>20 ) num++;
//             QString fileName = /*"/home/houyawei/Pictures/"*/PathName + '/' + urlpngList[5] + ".png";
//             QString url_name= urlpngList[9];	//ui->url_text为Qline edit控件
//             downIURL_to_picture(url_name,fileName);//将URL地址和要保存的文件名字传给函数调用

             QJsonParseError e;
             QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &e);
             if (e.error == QJsonParseError::NoError && !jsonDoc.isNull())
             {

                 if((!jsonDoc.isNull()) || (!jsonDoc.isEmpty()))
                 {

                     if(jsonDoc.isObject())
                     {
                         QJsonObject obj = jsonDoc.object();
                         if(obj.contains("body"))
                         {
                             QJsonValue body = obj.value("body");
                             if(body.isObject())
                             {
                                 QJsonObject bodyobj  = body.toObject();
                                 if(bodyobj.contains("app_icon"))
                                 {
                                      QJsonValue bodyvalue = bodyobj.value("app_icon");
                                     if(bodyvalue.isObject())
                                     {
                                         QJsonObject app_icon = bodyvalue.toObject();
                                         QJsonValue  app_iconvalue =  app_icon.value(PKG_NAME);
                                         if(app_iconvalue.isArray())
                                         {
                                             QJsonArray array = app_iconvalue.toArray();
                                             int nSize = array.size();
                                             for (int i = 0; i < nSize; ++i)
                                             {
                                                     QJsonValue arrayvalue = array.at(i);
                                                     QString fileName;
                                                     if(arrayvalue.isObject())
                                                     {
                                                         QJsonObject arrayobject  = arrayvalue.toObject();
                                                         QJsonValue logovalue = arrayobject.value("logo");
                                                         num++;

                                                         if(i==0)
                                                                 fileName = PathName + '/' + PKG_NAME + ".png";
                                                         else
                                                                 fileName = PathName + '/' + PKG_NAME +  QString::number(i)+".png";
                                                         if(logovalue.isString())
                                                         {
                                                             QString url_name= logovalue.toString();
                                                            logoPng->setPixmap(setpnglabel(url_name));
                                                             downIURL_to_picture(url_name,fileName);
                                                           }
                                                      }

                                                }
                                     }
                                 }
                             }

                          }
                     }
                  }
             }
             //qDebug() << bytes;
         }
         else
         {
             qDebug() << "finishedSlot errors here";
             qDebug( "found error .... code: %d\n", (int)reply->error());
             qDebug(qPrintable(reply->errorString()));
         }
             if (reply->isFinished())
                 reply->deleteLater();
}}

QPixmap SmartisanOsLogo::setpnglabel(const QString &szUrl)
{
    //QString szUrl="http://icon.smartisan.com/drawable/com.sina.weibo/logo.png";
    QUrl url(szUrl);
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *replypng = manager.get(QNetworkRequest(url));
    QObject::connect(replypng, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QByteArray jpegData = replypng->readAll();
    QPixmap pix;
    pix.loadFromData(jpegData);
    return pix;
//    logoPng->setPixmap(pix);
}
bool SmartisanOsLogo::downIURL_to_picture(const QString &url, const QString &fileName)
{

    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->error() != QNetworkReply::NoError)
    {
        return false;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    file.write(reply->readAll());
    file.close();
    if (reply->isFinished())
        reply->deleteLater();
    return true;
 }
