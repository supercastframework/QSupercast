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
#include "supercastsignal.h"

SupercastSignal::SupercastSignal(QObject* parent) : QObject(parent) {}

void SupercastSignal::emitServerMessage(int integer) {
    emit this->serverMessage(integer);
}

void SupercastSignal::emitServerMessage(QString string) {
    emit this->serverMessage(string);
}

void SupercastSignal::emitServerMessage(QVariant json) {
    emit this->serverMessage(json);
}
