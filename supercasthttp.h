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
#ifndef SUPERCASTHTTP_H
#define SUPERCASTHTTP_H

#include "supercasthttpreply.h"
#include "supercasthttprequest.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHostAddress>
#include <QUrl>
#include <QString>
#include <QVariant>
#include <QHash>
#include <QFile>
#include <QMetaType>

#include <QDebug>

class SupercastHTTP : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit SupercastHTTP(QObject* parent = 0);
    ~SupercastHTTP();

public slots:
    void handleClientRequest(SupercastHttpRequest request);

private slots:
    void handleNetworkReply(QNetworkReply* reply);

private:
    static QNetworkRequest::Attribute att_request;
    static QNetworkRequest::Attribute att_opaque;
    static QNetworkRequest::Attribute att_dstfile;

signals:
    void serverReply(SupercastHttpReply reply);
};

#endif // SUPERCASTHTTP_H
