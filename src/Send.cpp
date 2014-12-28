/*
 * Send.cpp
 *
 *  Created on: Dec 25, 2014
 *      Author: Luan
 */

#include <src/Send.hpp>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/ImageView>
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

using namespace bb::cascades;

Send::Send(QObject *parent)
:QObject(parent)
, m_model(new GroupDataModel(this))
{
    generalUtilities = new GeneralUtilities();
    settings = new Settings();
    m_model->setGrouping(ItemGrouping::None);
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
        imageView->setObjectName(map["targetID"].toString()+"_img");
        imageView->setScalingMethod(ScalingMethod::AspectFill);
        imageView->setPreferredSize(144, 144);
        imageView->setHorizontalAlignment(HorizontalAlignment::Center);

        Container *outerContainer = new Container();
        outerContainer->setObjectName(map["targetID"].toString()+"_cont");
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
        generalUtilities->createToast("touch up");
        qDebug()<<"eventoutput"+event->toDebugString();
        VisualNode* targetDevice = event->target();
        qDebug()<< "target output" +targetDevice->toDebugString();
        qDebug()<< "target outputname" +targetDevice->objectName();
        if(fileName==""){
            sendText();
        }
    }
}
void Send::sendText(){

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
void Send::filePicker(){
    FilePicker* filePicker = new FilePicker();
    filePicker->setType(FileType::Picture);
    filePicker->setTitle("Select file");
    //filePicker->setMode(FilePickerMode::Picker);
    filePicker->open();

    // Connect the fileSelected() signal with the slot.
    QObject::connect(filePicker,
        SIGNAL(fileSelected(const QStringList&)),
        this,
        SLOT(onFileSelected(const QStringList&)));

}
void Send::onFileSelected(const QStringList& files){
    fileName = files.at(0);
    qDebug()<<"Filename " + fileName;
}
void Send::setSaveMessage(){
    if(saveMessage=="false"){
        saveMessage=true;

    }
}
Send::~Send()
{
    // TODO Auto-generated destructor stub
}

