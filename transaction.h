#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QString>
#include <QVariant>


class Transactions
{
public:
    Transactions();
QString add_records(QString tablename,
                 QString attributes, QVariant parametrs[]);

QString update_records(QString tablename, QString attributes,
                    QVariant parametrs[], QString pk_name, int pk);

QString delete_records(QString tablename, QString pk_name, int pk);
};

#endif // TRANSACTIONS_H
