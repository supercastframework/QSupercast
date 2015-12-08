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
#ifndef SUPERCASTHTTPREQUEST_H
#define SUPERCASTHTTPREQUEST_H

#include <QUrl>

class SupercastHttpRequest
{
public:
    /*
     * Default constructor for qRegisterMetaType?
     */
    SupercastHttpRequest();
    SupercastHttpRequest(
            int  request_id,
            QUrl request_url);
    SupercastHttpRequest(
            int     request_id,
            QString dst_file,
            QUrl    request_url);
    SupercastHttpRequest(
            int     request_id,
            QString dst_file,
            QUrl    request_url,
            QString opaque);

    int     id;
    QUrl    url;
    QString dst_file;
    QString   opaque;
};

#endif // SUPERCASTHTTPREQUEST_H
