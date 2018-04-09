#include "transaction.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <windows.h>


Transactions::Transactions()
{
}

QString Transactions::add_records(QString tablename,
                               QString attributes, QVariant parametrs[])
{
    QSqlQuery *query = new QSqlQuery;
    int kol_vo_attributes = 0;
    int size = attributes.size();

    for (int i = 0; i < size; i ++)
    {
        if (attributes.data()[i] == ',')
        {
            kol_vo_attributes ++;
        }
    }

    QString sqlquery;
    sqlquery = "insert into "+tablename+" ";
    sqlquery += "(" + attributes + ")" + " values ";
    sqlquery += "(";

    for (int i = 0; i < kol_vo_attributes; i ++)
    {
        sqlquery += "?,";
    }
    sqlquery += "?)";

    query->prepare(sqlquery);

    for (int i = 0; i < kol_vo_attributes + 1; i ++)
    {
        qDebug() << QString::number(i);
        qDebug() << parametrs[i].toString();
        query->addBindValue(parametrs[i]);
    }

    if (!query->exec()) {
        return  query->lastError().text();

    }
    qDebug()<< "query errors: " <<query->lastError().text();
    qDebug()<< "sql: " <<query->lastQuery();
    return QString();
}

QString Transactions::update_records(QString tablename, QString attributes,
                            QVariant parametrs[], QString pk_name, int pk)
{
    QSqlQuery *query = new QSqlQuery;
    int kol_vo_attributes = 1;
    int size = attributes.size();

    for (int i = 0; i < size; i ++)
    {
        if (attributes.data()[i] == ',')
        {
            kol_vo_attributes ++;
        }
    }

    QString sqlquery;
    sqlquery = "update "+tablename+" set ";
    sqlquery +=  attributes;
    sqlquery +=" where "+pk_name+" = "+QString::number(pk)+"";
    query->prepare(sqlquery);

    for (int i = 0; i < kol_vo_attributes; i ++)
    {
        query->addBindValue(parametrs[i]);
    }

    if (!query->exec()) {
        return query->lastError().text();
    }
    return QString();
}

QString Transactions::delete_records(QString tablename,
                                  QString pk_name, int pk)
{
    QSqlQuery *query = new QSqlQuery;

    if (!query->exec("delete from "+tablename+""
                     " where "+pk_name+" = "+QString::number(pk)+""))
    {
        return query->lastError().text();
    }
    return QString();
}



