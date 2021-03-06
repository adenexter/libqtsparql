/****************************************************************************
**
** Copyright (C) 2010-2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (ivan.frade@nokia.com)
**
** This file is part of the examples of the QtSparql module (not yet part of the Qt Toolkit).
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at ivan.frade@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QDebug>
#include <QtSparql>
#include <QCoreApplication>

void printPosition(const QSparqlResult* q)
{
    int i = q->pos();
    switch (i) {
    case QSparql::BeforeFirstRow:
        qDebug() << "Position: Before first";
        break;
    case QSparql::AfterLastRow:
        qDebug() << "Position: After last";
        break;
    default:
        qDebug() << "Position:" << i;
        break;
    }
}

void printResultRow(const QSparqlResultRow& rr)
{
    qDebug() << "Result row:";
    if (rr.isEmpty()) {
        qDebug() << "Empty";
        return;
    }
    qDebug() << "Column count:" << rr.count();
    for (int i = 0; i < rr.count(); ++i)
        qDebug() << "\t" << i << rr.binding(i).value().toString();
}

void iterateForward(QSparqlConnection* conn)
{
    QSparqlQuery query("select ?u ?p { ?u a nco:Contact ; nco:hasPhoneNumber ?pn . "
                       "?pn a nco:PhoneNumber ; nco:phoneNumber ?p }");

    QSparqlResult* r = conn->exec(query);
    r->waitForFinished();

    qDebug() << "---- Iterating forward ----";
    // First the query is positioned "before the first row"
    printPosition(r);
    printResultRow(r->current());

    while (r->next()) {
        printPosition(r);
        printResultRow(r->current());
    }
    // Then the query is positioned "after the last row"
    printPosition(r);
    printResultRow(r->current());
    delete r;
}

void iterateBackward(QSparqlConnection* conn)
{
    QSparqlQuery query("select ?u ?p { ?u a nco:Contact ; nco:hasPhoneNumber ?pn . "
                       "?pn a nco:PhoneNumber ; nco:phoneNumber ?p }");

    QSparqlResult* r = conn->exec(query);
    r->waitForFinished();

    r->last();
    r->next();

    qDebug() << "---- Iterating backwards ----";
    printPosition(r);
    printResultRow(r->current());

    while (r->previous()) {
        printPosition(r);
        printResultRow(r->current());
    }

    printPosition(r);
    printResultRow(r->current());
    delete r;
}

void insertData(QSparqlConnection* conn)
{
    QSparqlQuery insert("insert { _:u a nco:Contact . "
                        "_:pn a nco:PhoneNumber ; "
                        "nco:phoneNumber 12345 . "
                        "_:u nco:hasPhoneNumber _:pn . }",
                        QSparqlQuery::InsertStatement);
    QSparqlResult* r = conn->exec(insert);
    r->waitForFinished();
    delete r;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSparqlConnection conn("QTRACKER");

    insertData(&conn);

    iterateForward(&conn);
    iterateBackward(&conn);

    return 0;
}
