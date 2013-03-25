#ifndef P2PCRYPT_SQL_H
#define P2PCRYPT_SQL_H

#include <QObject>
#include <QSql>
#include <QtSql/QtSql>

class p2pcrypt_sql : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase database_handle;

    explicit p2pcrypt_sql(QObject *parent = 0);
    void connectToDatabase(QString sql_filename);


signals:
    
public slots:

};

#endif // P2PCRYPT_SQL_H
