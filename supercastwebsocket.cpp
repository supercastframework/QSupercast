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
#include "supercastwebsocket.h"

SupercastWebSocket::SupercastWebSocket(QHostAddress host, qint16 port) : QObject()
{
    this->socket = new QWebSocket();
    this->socket->setParent(this);
    this->host = host;
    this->port = port;

    this->timer = new QTimer(this);
    this->timer->setSingleShot(true);
    int socket_timeout = 1000;
    this->timer->setInterval(socket_timeout);

    QObject::connect(
                this->timer, SIGNAL(timeout()),
                this, SLOT(timerTimeout()),
                Qt::QueuedConnection);
    qRegisterMetaType<QAbstractSocket::SocketError>();
    qRegisterMetaType<QAbstractSocket::SocketState>();
    QObject::connect(
                this->socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(handleSocketError(QAbstractSocket::SocketError)));

    QObject::connect(
                this->socket, SIGNAL(textMessageReceived(QString)),
                this,         SLOT(handleTextMessage(QString)));
}

void SupercastWebSocket::threadStarted()
{
    QString urlStr = "ws://%1:%2/websocket";
    QUrl url(urlStr.arg(this->host.toString()).arg(this->port));
    this->timer->start();
    qDebug() << "will open " << url.toString();
    this->socket->open(url);

}

SupercastWebSocket::~SupercastWebSocket()
{
    this->socket->close();
}

void SupercastWebSocket::timerTimeout()
{
    if (this->socket->state() == QAbstractSocket::UnconnectedState) return;
    if (this->socket->state() != QAbstractSocket::ConnectedState) {
        emit this->waitTimeout(QAbstractSocket::NetworkError);
        this->socket->abort();
    }
}

void SupercastWebSocket::handleTextMessage(const QString &message)
{
    QVariant json_obj = QJson::decode(message);
    emit this->serverMessage(json_obj);
}


void SupercastWebSocket::handleClientMessage(QVariant msg)
{
    //QByteArray json_array = QJson::encode(msg).toLatin1();
    this->socket->sendTextMessage(QJson::encode(msg));
}

qint32 SupercastWebSocket::arrayToInt32(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

QByteArray SupercastWebSocket::int32ToArray(qint32 source)
{
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

void SupercastWebSocket::handleSocketError(QAbstractSocket::SocketError error) {
    emit this->socketError((int) error);
}


