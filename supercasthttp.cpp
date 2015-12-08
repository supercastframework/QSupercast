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
#include "supercasthttp.h"

QNetworkRequest::Attribute SupercastHTTP::att_request =
        static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 1);

QNetworkRequest::Attribute SupercastHTTP::att_opaque  =
        static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 2);

QNetworkRequest::Attribute SupercastHTTP::att_dstfile =
        static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 3);

SupercastHTTP::~SupercastHTTP() {}

SupercastHTTP::SupercastHTTP(QObject* parent)
    : QNetworkAccessManager(parent)
{
    QObject::connect(
                this, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(handleNetworkReply(QNetworkReply*)));
}

void SupercastHTTP::handleClientRequest(SupercastHttpRequest request)
{
    QNetworkRequest net_request = QNetworkRequest(request.url);
    net_request.setAttribute(
                SupercastHTTP::att_request,
                QVariant(request.id));
    net_request.setAttribute(
                SupercastHTTP::att_opaque,
                QVariant(request.opaque));
    net_request.setAttribute(
                SupercastHTTP::att_dstfile,
                QVariant(request.dst_file));
    net_request.setAttribute(
                QNetworkRequest::HttpPipeliningAllowedAttribute,
                QVariant(true));
    this->get(net_request);
}

void SupercastHTTP::handleNetworkReply(QNetworkReply* net_reply)
{
    int request_id = net_reply->request()
                         .attribute(SupercastHTTP::att_request)
                         .toInt();
    QString opaque = net_reply->request()
                         .attribute(SupercastHTTP::att_opaque)
                         .toString();
    QString dst_file = net_reply->request()
                         .attribute(SupercastHTTP::att_dstfile)
                         .toString();

    if (dst_file == "none")
    {
        QString            reply_body(net_reply->readAll());
        SupercastHttpReply reply(request_id, reply_body);
        emit this->serverReply(reply);
    }
    else
    {
        QFile file(dst_file);
        file.open(QIODevice::ReadWrite);
        file.write(net_reply->readAll());
        file.close();

        if (opaque == "undefined")
        {
            SupercastHttpReply reply(request_id, dst_file);
            emit this->serverReply(reply);
        }
        else
        {
            SupercastHttpReply reply(request_id, opaque);
            emit this->serverReply(reply);
        }
    }
    net_reply->deleteLater();
}
