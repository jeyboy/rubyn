#include "web_connection.h"

#include "web_manager.h"

using namespace Web;

void WebConnection::checkConnection(QFutureWatcher<void> * checker) {
    Manager * manager = Manager::prepare();

    while(!checker -> isCanceled()) {
        QNetworkReply * reply = manager -> head(QNetworkRequest(USTR("http://google.com")));

        if (reply -> error() == QNetworkReply::NoError) {
            qDebug() << "~~~ CONNESTION RESTORED";
            emit connectionStatus(true);
            break;
        }

        QThread::msleep(250);
    }

    checker -> deleteLater();
    checker = 0;
}
