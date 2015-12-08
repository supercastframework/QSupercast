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
#ifndef SUPERCASTSIGNAL_H
#define SUPERCASTSIGNAL_H

#include <QObject>
#include <QVariant>
#include <QString>

class SupercastSignal : public QObject
{
    Q_OBJECT

public:
    explicit SupercastSignal(QObject* parent = 0);
    void emitServerMessage(QVariant json);
    void emitServerMessage(QString string);
    void emitServerMessage(int integer);

signals:
    void serverMessage(QVariant json);
    void serverMessage(QString  string);
    void serverMessage(int      integer);
};

#endif // SUPERCASTSIGNAL_H
