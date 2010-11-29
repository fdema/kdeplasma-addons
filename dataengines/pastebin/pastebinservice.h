/*
 *   Copyright 2009 Artur Duque de Souza <asouza@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef PASTEBIN_SERVICE_H
#define PASTEBIN_SERVICE_H

#include "pastebinengine.h"
#include "backends/backends.h"

#include <Plasma/Service>
#include <Plasma/ServiceJob>

class QNetworkAccessManager;
class QNetworkReply;

class PastebinService : public Plasma::Service
{
    Q_OBJECT

public:
    enum textServers { PASTEBINCA, PASTEBINCOM };
    enum imageServers { IMAGEBINCA, IMAGESHACK, SIMPLESTIMAGEHOSTING, IMGUR };

    PastebinService(PastebinEngine *engine);
    Plasma::ServiceJob *createJob(const QString &operation,
                                  QMap<QString, QVariant> &parameters);
};

class PastebinJob : public Plasma::ServiceJob
{
    Q_OBJECT
public:
    PastebinJob(const QString &destination, const QString &operation,
                QMap<QString, QVariant> &parameters, QObject *parent = 0);

    void start();

protected:
    void postText();
    void postImage();

protected slots:
    void processTinyUrl(QNetworkReply *reply);
    void showResults(const QString &url);
    void showErrors(const QString &url = "");

private:
    PastebinServer *m_server;
};

#endif // PASTEBIN_SERVICE