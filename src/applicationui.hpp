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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include "settings.hpp"
#include "History.hpp"
#include "Send.hpp"
#include "generalUtilities.hpp"
#include <QObject>
#include <bb/network/PushService>
#include <bb/system/InvokeManager>
#include <bb/network/PushPayload>
#include <bb/cascades/NavigationPane>

namespace bb
{
    namespace cascades
    {
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI();
    virtual ~ApplicationUI() {}
    Q_INVOKABLE void createToast(QString msg);
    Q_INVOKABLE void login();
    Q_INVOKABLE void openHistoryPage();
    Q_INVOKABLE void getHistory();
    Q_INVOKABLE void copyItem(QString message);
    Q_INVOKABLE void getDevices();
    History *history;
    bb::cascades::NavigationPane *navPane;
    Send *send;
    Settings *settings;
    GeneralUtilities *generalUtilities;
Q_SIGNALS:
    void createSessionCompleted(const bb::network::PushStatus &status);
    void createChannelCompleted(const bb::network::PushStatus &status, const QString &token);
public Q_SLOTS:
    void onCreateSessionCompleted(const bb::network::PushStatus &status);
    void onCreateChannelCompleted(const bb::network::PushStatus &status, const QString &token);
    void onInvoked(const bb::system::InvokeRequest &request);
    void handleUserLoggedIn();
private slots:
    void onSystemLanguageChanged();
private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    bb::network::PushService *m_pushService;
    void startPushSession();
    void pushNotificationHandler(bb::network::PushPayload &pushPayload);
    bb::system::InvokeManager *m_invokeManager;


};

#endif /* ApplicationUI_HPP_ */
