#include "smartisanoslogo.h"
#include <DWidgetUtil>
#include <DSearchEdit>
#include <DTitlebar>
#include <QNetworkAccessManager>
SmartisanOsLogo::SmartisanOsLogo(DMainWindow *parent)
    : DMainWindow(parent)
{

    setCentralWidget(w);
    moveToCenter(this);
    SmartisanOsLogo::resize(900,700);
    SmartisanOsLogo::setMinimumSize(900,700);
    QHBoxLayout *hlayout =new QHBoxLayout(w);
    QVBoxLayout *v1layout = new QVBoxLayout(w);
    QHBoxLayout *modelayout = new QHBoxLayout(w);
    DLabel *mode = new DLabel;
    mode->setText("①下载模式:");
    mode->setAlignment(Qt::AlignCenter);
    DComboBox *modecombobox= new DComboBox;
    modecombobox->addItem("单应用图标下载");
    //modecombobox->addItem("系统应用图标下载");
    modecombobox->addItem("常见应用图标批量下载");
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
    v2layout->addStretch(2);

    QNetworkAccessManager *accessManager = new QNetworkAccessManager(this);
    connect(accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl("http://setting.smartisan.com/app/icon/"));
    request.setRawHeader("Content-Type", "application/json;charset=utf8");




        //download button
        connect(Download, &DPushButton::clicked, this, [ = ] {


            switch (modecombobox->currentIndex()) {

                case 0:
                {
                    QString packagename = nameLineEdit->text();
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

                QFile file("allapp.json");
                if(file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                    QString value = file.readAll();
                    file.close();
                    QJsonParseError parseJsonErr;
                    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);

                    if (! (parseJsonErr.error == QJsonParseError::NoError)) {
                        QMessageBox::about(NULL, "提示", "配置文件错误！");
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
                             //"com.sina.weibo" ;
                             QJsonObject obj;
                             obj.insert("package",packagename);
                             QJsonDocument jsonDoc(obj);
                             QNetworkReply* reply = accessManager->post(request, '[' + jsonDoc.toJson(QJsonDocument::Compact) + ']');
                             if (reply->isFinished())
                                 reply->deleteLater();

                       }
//                       keyString=keyString.left(keyString.length()-1);
//                       valueString=valueString.left(valueString.length()-1);

                }



               }
                break;

                case 2:
               {
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
             QString urlpng = QString(bytes);
             QStringList urlpngList=urlpng.split(QRegExp("[\"]"));
             qDebug()<<"urlpngList"<<urlpngList[9];
             logoPng->setPixmap(setpnglabel(urlpngList[9]));

             QString fileName = /*"/home/houyawei/Pictures/"*/PathName + '/' + urlpngList[5] + ".png";
             QString url_name= urlpngList[9];	//ui->url_text为Qline edit控件
             downIURL_to_picture(url_name,fileName);//将URL地址和要保存的文件名字传给函数调用

//             QJsonParseError e;
//             QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes, &e);
//             if (e.error == QJsonParseError::NoError && !jsonDoc.isNull())
//             {

//                 if((!jsonDoc.isNull()) || (!jsonDoc.isEmpty()))
//                 {

//                     if(jsonDoc.isObject())
//                     {
//                         QJsonObject obj = jsonDoc.object();
//                         qDebug()<<"obj"<<obj;
//                         if(obj.contains(QString("logo")))
//                         {
//                             QString body = obj.value("head").toString();
//                             qDebug()<<"body"<<body;
//                          }
//                     }
//                  }
//             }
             //qDebug() << bytes;
         }
         else
         {
             qDebug() << "finishedSlot errors here";
             qDebug( "found error .... code: %d\n", (int)reply->error());
             qDebug(qPrintable(reply->errorString()));
         }
         reply->deleteLater();
}

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
    //logoPng->setPixmap(pix);
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
    delete reply;
 }
