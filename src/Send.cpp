/*
 * Send.cpp
 *
 *  Created on: Dec 25, 2014
 *      Author: Luan
 */

#include <src/Send.hpp>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/Button>
#include <bb/cascades/ImageView>
#include <bb/cascades/TextArea>
#include <bb/cascades/Container>
#include <bb/cascades/StackLayout>
#include <bb/cascades/Label>
#include <bb/cascades/Color>
#include <bb/cascades/ColorPaint>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/TouchEvent>
#include <bb/cascades/VisualNode>
#include <bb/cascades/pickers/FilePicker>
#include <QVariantMap>
#include <QUrl>
#include <QStringList>
#include <QHttpPart>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QByteArray>

using namespace bb::cascades;

Send::Send(QObject *parent)
:QObject(parent)
, m_model(new GroupDataModel(this))
{
    generalUtilities = new GeneralUtilities();
    settings = new Settings();
    m_model->setGrouping(ItemGrouping::None);
    saveMessage="true";
}
void Send::addDevices(){
    QString devicesStr = settings->getValueFor("devices","");
    qDebug()<<"device string " + devicesStr;
    if(devicesStr.trimmed().isEmpty()){
        getDevices();
    }
    else{

        QVariantList response = generalUtilities->json2List(devicesStr);
        qDebug()<<"device string " + response.length();
        //test();
        drawDevices(response);
    }
}
void Send::getDevices(){
    QString email = settings->getValueFor("email","");

    qDebug() << "Getting devices: " + email;

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);

    QByteArray data;
    QUrl params;
    params.addQueryItem("email", email);
    data.append(params.toString());
    data.remove(0,1);

    QString requestUrl = generalUtilities->serverPath + "server/getDevices_v1.php";

    QNetworkRequest networkRequest= QNetworkRequest();
    networkRequest.setUrl(requestUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    reply = networkManager->post(networkRequest,data);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
GroupDataModel* Send::model() const
{
    return m_model;
}

void Send::finishedSlot()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 2: Reading bytes form the reply
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string
        qDebug() << "Server response: " + string;
        settings->saveValueFor("devices", string);
        QVariantList response = generalUtilities->json2List(string);
        drawDevices(response);
    }
    // Some http error received
    else
    {
        // handle errors here
    }
}
void Send::drawDevices(QVariantList devices){
    m_model->clear();
    QVariantMap map;
    foreach ( QVariant item , devices)
    {
        map["name"] = item.value<QVariantMap>().value("name").toString();
        map["type"] = item.value<QVariantMap>().value("type").toString();
        map["targetID"] = item.value<QVariantMap>().value("targetID").toString();
        m_model->insert(map);

        ImageView * imageView = new ImageView();
        if (map["type"].toString() == "android" || map["type"].toString() == "blackberry"){
            imageView->setImage(Image("asset:///images/phone_black.png"));
        }
        else if(map["type"].toString() == "chrome"){
            imageView->setImage(Image("asset:///images/computer_black.png"));
        }
        imageView->setObjectName(map["targetID"].toString()+"__FlippImg");
        imageView->setScalingMethod(ScalingMethod::AspectFill);
        imageView->setPreferredSize(144, 144);
        imageView->setHorizontalAlignment(HorizontalAlignment::Center);

        Container *outerContainer = new Container();
        outerContainer->setObjectName(map["targetID"].toString()+"_FlippCont");
        outerContainer->setBackground(ImagePaint("asset:///images/rounded_blue.amd", RepeatPattern::XY));
        outerContainer->setPreferredSize(196,196);
        outerContainer->setLeftMargin(20);
        outerContainer->setRightMargin(20);
        StackLayout * stackLayout = new StackLayout();
        stackLayout->setOrientation(LayoutOrientation::BottomToTop);
        outerContainer->setLayout(stackLayout);

        bool connectResult = QObject::connect(outerContainer,
                                SIGNAL(touch(bb::cascades::TouchEvent*)),
                                this,
                                SLOT(handleTouch(bb::cascades::TouchEvent*)));

        // This is only available in Debug builds.
        Q_ASSERT(connectResult);

        Q_UNUSED(connectResult);

        Container *textContainer = new Container();
        textContainer->setBackground(Color::fromARGB(0xa2181818));
        textContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
        textContainer->setVerticalAlignment(VerticalAlignment::Center);

        Label *label = new Label();
        QString name="";
        if(map["name"].toString()==""){
            name = map["type"].toString();
        }
        else{
            name =map["name"].toString();
        }
        label->setText(name);
        label->setHorizontalAlignment(HorizontalAlignment::Center);
        label->textStyle()->setColor(Color::fromARGB(0xffffffff));

        textContainer->add(label);
        outerContainer->add(textContainer);
        outerContainer->add(imageView);

        Container *deviceContainer = nav->findChild<Container*>("deviceContainer");
        deviceContainer->add(outerContainer);
        //break;
    }

}
void Send::setNavPane(NavigationPane * navPane){
    nav = navPane;
}
void Send::handleTouch(bb::cascades::TouchEvent* event)
{
    if(event->touchType() == TouchType::Up){
        VisualNode* targetDevice = event->target();

        QString name = targetDevice->objectName();
        QString targetID = name.left(name.indexOf("__Flipp"));

        QList<QVariantMap> list = m_model->toListOfMaps();
        foreach(QVariantMap item, list){

            if (item["targetID"].toString() == targetID){
                qDebug()<<item["type"];
                qDebug()<<fileName;
                if(fileName==""){
                    sendText(item);
                }
                else{
                    sendFile(item);
                }
            }
        }
    }
}

void Send::sendFile(QVariantMap device){
QString targetType = device["type"].toString();
    QString targetID = device["targetID"].toString();

    QUrl url(generalUtilities->serverPath+"server/uploadTest.php");
    TextArea *messageText = nav->findChild<TextArea*>("messageText");

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QByteArray emailData;
    emailData.append(settings->getValueFor("email",""));
    QHttpPart emailPart;
    emailPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"email\""));
    emailPart.setBody(emailData);

    QByteArray targetTypeData;
    targetTypeData.append(targetType);
    QHttpPart targetTypePart;
    targetTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"targetType\""));
    targetTypePart.setBody(targetTypeData);

    QByteArray targetIDData;
    targetIDData.append(targetID);
    QHttpPart targetIDPart;
    emailPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"targetID\""));
    emailPart.setBody(targetIDData);

    QByteArray saveMessageData;
    saveMessageData.append(saveMessage);
    QHttpPart saveMessagePart;
    saveMessagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"saveMessage\""));
    saveMessagePart.setBody(saveMessageData);

    QByteArray messageTextData;
    messageTextData.append(messageText->text());
    QHttpPart messagePart;
    messagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"message\""));
    messagePart.setBody(messageTextData);

    QHttpPart filePart;
    QFileInfo fileInfo(fileName);
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(fileName);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime.name()));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"file\"; filename=\""+ fileInfo.baseName() + "\""));
    QFile *file = new QFile(fileName);
    if ( !file->exists() )
     {
         qDebug() << "File Does not exist";
     }
    file->open(QIODevice::ReadOnly);
    qDebug()<<file->size();
    qDebug()<<"Filename " + file->fileName();
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(emailPart);
    multiPart->append(targetIDPart);
    multiPart->append(targetTypePart);
    multiPart->append(saveMessagePart);
    multiPart->append(messagePart);
    multiPart->append(filePart);

    QNetworkRequest request(url);

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    reply = networkManager->post(request, multiPart);

    bool ok = connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(SlotSetProgressLevel(qint64, qint64)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    ok = connect(reply, SIGNAL(finished()), this, SLOT(sendFinish()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
void Send::SlotSetProgressLevel(qint64 bytesSent, qint64 bytesTotal) {
    qDebug() << "Uploaded" << bytesSent << "of" << bytesTotal;
}
void Send::sendText(QVariantMap device){
    QString targetType = device["type"].toString();
    QString targetID = device["targetID"].toString();
    TextArea *messageText = nav->findChild<TextArea*>("messageText");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QString email = settings->getValueFor("email","");
    QByteArray data;

    QUrl params;
    params.addQueryItem("email", email);
    params.addQueryItem("targetType", targetType);
    params.addQueryItem("targetID",targetID);
    params.addQueryItem("saveMessage",saveMessage);
    params.addQueryItem("message",messageText->text());
    data.append(params.toString());
    data.remove(0,1);

    QString requestUrl = generalUtilities->serverPath + "server/send_v2.php";

    QNetworkRequest networkRequest= QNetworkRequest();
    networkRequest.setUrl(requestUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    reply = networkManager->post(networkRequest,data);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(sendFinish()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
void Send::sendFinish()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 2: Reading bytes form the reply
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string
        qDebug() << "Server response: " + string;
    }
    // Some http error received
    else
    {
        // handle errors here
    }
}
void Send::test(){
            ImageView * imageView = new ImageView();
            imageView->setImage(Image("asset:///images/computer_black.png"));
            imageView->setScalingMethod(ScalingMethod::AspectFill);
            imageView->setPreferredSize(144, 144);
            imageView->setHorizontalAlignment(HorizontalAlignment::Center);

            Container *outerContainer = new Container();
            outerContainer->setObjectName("test device");
            outerContainer->setBackground(ImagePaint("asset:///images/rounded_blue.amd", RepeatPattern::XY));
            outerContainer->setPreferredSize(196,196);
            outerContainer->setLeftMargin(20);
            outerContainer->setRightMargin(20);
            StackLayout * stackLayout = new StackLayout();
            stackLayout->setOrientation(LayoutOrientation::BottomToTop);
            outerContainer->setLayout(stackLayout);

            Container *textContainer = new Container();
            textContainer->setBackground(Color::fromARGB(0xa2181818));
            textContainer->setHorizontalAlignment(HorizontalAlignment::Fill);
            textContainer->setVerticalAlignment(VerticalAlignment::Center);

            Label *label = new Label();
            QString name="test";

            label->setText(name);
            label->setHorizontalAlignment(HorizontalAlignment::Center);
            label->textStyle()->setColor(Color::fromARGB(0xffffffff));

            textContainer->add(label);
            outerContainer->add(textContainer);
            outerContainer->add(imageView);

            Container *deviceContainer = nav->findChild<Container*>("deviceContainer");
            deviceContainer->add(imageView);
}
void Send::filePicker(QString chosenFile){

    Image image = Image(QUrl("file://"+chosenFile));
    ImageView* imageView = nav->findChild<ImageView*>("fileImage");
    imageView->setImage(image);


    fileName = chosenFile;
    generalUtilities->createToast(fileName);
    QFile newFile(fileName);

    if (newFile.exists()) {

        newFile.open(QIODevice::ReadOnly);
            qDebug()<<newFile.size();
            qDebug()<<newFile.fileName();

    }
    else{
        qDebug()<<"no file" << fileName + " " + QDir::currentPath();
    }
}

void Send::setSaveMessage(){
    Button *saveButton = nav->findChild<Button*>("saveButton");
    if(saveMessage=="false"){
        saveMessage="true";
        QUrl image("asset:///images/history_blue.png");
        saveButton->setImageSource(image);
    }
    else{
        saveMessage="true";
        QUrl image("asset:///images/onetime_blue.png");
        saveButton->setImageSource(image);
    }
}
Send::~Send()
{
    // TODO Auto-generated destructor stub
}

