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
