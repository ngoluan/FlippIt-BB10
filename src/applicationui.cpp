/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"
#include "login.hpp"
#include "settings.hpp"
#include "generalUtilities.hpp"
#include <bb/system/SystemToast>
#include <bb/system/InvokeManager>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/TextField>
#include <bb/platform/Notification>
#include <bb/network/PushService>
#include <bb/network/PushStatus>
#include <bb/network/PushErrorCode>
#include <bb/system/Clipboard>
#include <QDebug>
#include <QUrl>
#include <QSettings>
#include <QString>
#include <QDeclarativeContext>
#include <typeinfo>

#define BB_OPEN_INVOCATION_ACTION "bb.action.OPEN"
#define NOTIFICATION_PREFIX "com.luan.FlippIt_"

using namespace bb::cascades;
using namespace bb::network;
using namespace bb::system;
using namespace bb::platform;

ApplicationUI::ApplicationUI() :
                QObject(), m_pushService(0)
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    QCoreApplication::setOrganizationName("Luan");
    QCoreApplication::setApplicationName("FlippIt");

    m_pushService = new PushService("5127-786B9ee598Bm5170406nc90278at5166rc0", "com.luan.FlippIt.invoke.push", this);
    res = QObject::connect(m_pushService, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)),
            this, SLOT(onCreateSessionCompleted(const bb::network::PushStatus&)));
    Q_ASSERT(res);
    Q_UNUSED(res);

    res =  QObject::connect(m_pushService, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)),
            this, SLOT(onCreateChannelCompleted(const bb::network::PushStatus&, const QString)));
    Q_ASSERT(res);
    Q_UNUSED(res);

    m_invokeManager = new InvokeManager();
    res =  QObject::connect(m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            SLOT(onInvoked(const bb::system::InvokeRequest&)));
    Q_ASSERT(res);
    Q_UNUSED(res);

    settings = new Settings();
    send = new Send();
    generalUtilities = new GeneralUtilities();
    history = new History();

    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);
    qml->setContextProperty("_history", history);
    qml->setContextProperty("_send", send);
    navPane = qml->createRootObject<NavigationPane>();

    send->setNavPane(navPane);

    Application::instance()->setScene(navPane);

    QString emailSetting = settings->getValueFor("email","");
    qDebug() << emailSetting;

    if(emailSetting.trimmed().isEmpty()){
        qml = QmlDocument::create("asset:///login.qml").parent(this);
        qml->setContextProperty("_app", this);
        Page *loginPage = qml->createRootObject<Page>();

        navPane->push(loginPage);
        navPane->setBackButtonsVisible(false);
        qDebug() << "Pushed loginpage";

        QString pimSetting = settings->getValueFor("pim","");
        if(pimSetting.trimmed().isEmpty()){
            //startPushSession();
        }
    }
    else{

    }
}
void ApplicationUI::startPushSession(){
    if (!m_pushService) {

        if (m_pushService) {

            // Disconnect the signals
            QObject::disconnect(m_pushService, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)),
                    this, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)));
            QObject::disconnect(m_pushService, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)),
                    this, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)));
            delete m_pushService;
            m_pushService = NULL;
        }

        m_pushService = new PushService("5127-786B9ee598Bm5170406nc90278at5166rc0", "com.luan.FlippIt.invoke.push", this);

        //Connect the signals
        QObject::connect(m_pushService, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)),
                this, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)));
        QObject::connect(m_pushService, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)),
                this, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)));
    }

    if (m_pushService->hasConnection()){
        qDebug() << "session creating";
        m_pushService->createSession();
    } else {

    }
}
void ApplicationUI::onCreateSessionCompleted(const bb::network::PushStatus &status)
{
    qDebug() << "session created";
    if (m_pushService->hasConnection()){

        QUrl url("http://cp5127.pushapi.eval.blackberry.com");
        m_pushService->createChannel(url);
    } else {
        //emit noPushServiceConnection();
    }
}
void ApplicationUI::onCreateChannelCompleted(const bb::network::PushStatus &status, const QString &token)
{
    qDebug()<< "creatChannelComplete status: " << status.code();
    qDebug()<< "createChannelComplete token: " << token;


    // Typically in your own application you wouldn't want to display this error to your users
    QString message = QString("Create channel failed with error code: %0").arg(status.code());

    switch(status.code()){
        case  PushErrorCode::NoError:
            settings->saveValueFor("pim",token);
            break;
        case  PushErrorCode::TransportFailure:
            message = tr("Create channel failed as the push transport is unavailable. "
                    "Verify your mobile network and/or Wi-Fi are turned on. "
                    "If they are on, you will be notified when the push transport is available again.");
            qDebug()<< message;
            break;
        case PushErrorCode::SubscriptionContentNotAvailable:
            message = tr("Create channel failed as the PPG is currently returning a server error. "
                    "You will be notified when the PPG is available again.");
            qDebug()<< message;
            break;
    }
}
void ApplicationUI::onInvoked(const InvokeRequest &request)
{

    qDebug() << "Received push action";

    if (request.action().compare(BB_PUSH_INVOCATION_ACTION) == 0) {

        // Received an incoming push
        // Extract it from the invoke request and then process it
        PushPayload payload(request);
        if (payload.isValid()) {
            //qDebug() << payload;
            pushNotificationHandler(payload);
        }
    } else if (request.action().compare(BB_OPEN_INVOCATION_ACTION) == 0){
        qDebug() << "Received open action";
        // Received an invoke request to open an existing push (ie. from a notification in the BlackBerry Hub)
        // The payload from the open invoke is the seqnum for the push in the database
        //openPush(request.data().toInt());
    }

}
void ApplicationUI::pushNotificationHandler(bb::network::PushPayload &pushPayload)
{
    qDebug() <<pushPayload.data();
    createToast(pushPayload.data());

    Notification *notification = new Notification(NOTIFICATION_PREFIX + QString::number(1),this);
    notification->setTitle("FlippIt");
    notification->setBody(pushPayload.data());

    InvokeRequest invokeRequest;
    invokeRequest.setTarget("com.luan.FlippIt.invoke.open");
    invokeRequest.setAction(BB_OPEN_INVOCATION_ACTION);
    invokeRequest.setMimeType("text/plain");
    invokeRequest.setData(pushPayload.data());
    notification->setInvokeRequest(invokeRequest);

    notification->notify();

}
void ApplicationUI::createToast(QString msg){
    SystemToast *toast = new SystemToast(this);

    toast->setBody(msg);
    toast->setPosition(SystemUiPosition::MiddleCenter);
    toast->show();
}
void ApplicationUI::login(){
    Login *login = new Login();

    TextField *emailText = navPane->findChild<TextField*>("emailText");
    TextField *passwordText = navPane->findChild<TextField*>("passwordText");

    bool res = QObject::connect(login, SIGNAL(userLoggedIn()), this,
            SLOT(handleUserLoggedIn()));
    Q_ASSERT(res);
    Q_UNUSED(res);

    login->loginUser(emailText->text(), passwordText->text());
}
void ApplicationUI::handleUserLoggedIn(){
    QmlDocument *qml = QmlDocument::create("asset:///welcome.qml").parent(this);
    Page *welcomePage = qml->createRootObject<Page>();
    qml->setContextProperty("_app", this);
    navPane->pop();
    navPane->push(welcomePage);
    navPane->setBackButtonsVisible(false);
    qDebug() << "Pushed welcomePage";
}
void ApplicationUI::openHistoryPage(){
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);
    Page *historyPage = navPane->top();
    navPane->pop();
    navPane->navigateTo (historyPage);
    navPane->setBackButtonsVisible(true);
    qDebug() << "Pushed historyPage";
}
void ApplicationUI::getHistory(){
    history->addData();
}
void ApplicationUI::getDevices(){
    send->addDevices();
}
void ApplicationUI::copyItem(){
    //String message = history
    Clipboard clipboard;
    clipboard.clear();
    clipboard.insert("text/plain", "test");
    generalUtilities->createToast("Copied to clipboard");
}
void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("FlippIt_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
