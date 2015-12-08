/*
Supercast Copyright (c) 2012-2015 Sebastien Serre <ssbx@sysmo.io>
All Rights Reserved.

This file is provided to you under the Apache License,
Version 2.0 (the "License"); you may not use this file
except in compliance with the License.  You may obtain
a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/
#ifndef SUPERCASTWEBSOCKET_H
#define SUPERCASTWEBSOCKET_H

#include "qjson.h"

#include <QObject>
#include <QStringList>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <Qt>
#include <QTimer>
#include <QVariant>
#include <QWebSocket>
#include <QUrl>

class SupercastWebSocket : public QObject
{
    Q_OBJECT

public:
    explicit SupercastWebSocket(QHostAddress host, qint16 port);
    ~SupercastWebSocket();
    QWebSocket* socket;

public slots:
    void handleClientMessage(QVariant msg);
    void timerTimeout();
    void handleSocketError(QAbstractSocket::SocketError error);
    void threadStarted();

private:
    static qint32     arrayToInt32(QByteArray source);
    static QByteArray int32ToArray(qint32 source);
    QHostAddress host;
    qint16 port;
    QTimer* timer;

private slots:
    void handleTextMessage(const QString &message);

signals:
    void serverMessage(QVariant msg);
    void waitTimeout(int error);
    void socketError(int error);
};

#endif // SUPERCASTWEBSOCKET_H
