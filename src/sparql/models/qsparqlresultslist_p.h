/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (ivan.frade@nokia.com)
**
** This file is part of the QtSparql module (not yet part of the Qt Toolkit).
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at ivan.frade@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSPARQLRESULTSLIST_H
#define QSPARQLRESULTSLIST_H

#include <QAbstractListModel>

#include <QtSparql/QSparqlQuery>
#include <QtSparql/QSparqlResult>
#include <QtSparql/QSparqlBinding>
#include <QtSparql/QSparqlConnectionOptions>
#include <QtSparql/QSparqlConnection>

#include "qsparqlconnectionoptionswrapper_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Sparql)

class QSparqlResultsListPrivate;

class QSparqlResultsList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QSparqlConnectionOptionsWrapper * options READ options WRITE setOptions)
    Q_PROPERTY(QString query READ query WRITE setQuery)
    Q_CLASSINFO("DefaultProperty", "query")
public:
    QSparqlResultsList(QObject *parent = 0);
    ~QSparqlResultsList();

    void reload();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

    QSparqlConnectionOptionsWrapper * options() const;
    void setOptions(QSparqlConnectionOptionsWrapper *options);

    QString query() const;
    void setQuery(const QString &query);

Q_SIGNALS:
    void finished();

private slots:
    void queryFinished();

private:
    QSparqlResultsListPrivate* d;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QSPARQLRESULTSLIST_H