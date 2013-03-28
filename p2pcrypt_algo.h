#ifndef P2PCRYPT_ALGO_H
#define P2PCRYPT_ALGO_H

#include <QObject>
#include <QDebug>
#include <QtCore>
#include <QFuture>
#include <QSql>
#include <QtSql/QtSql>
#include <QVariant>

//OpenSSL
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>


//p2pcrypt
#include "p2pcrypt_sql.h"


class p2pcrypt_algo : public QObject
{
    Q_OBJECT
public:
    explicit p2pcrypt_algo(QObject *parent = 0);
    void generateNewIdentity(QString identity_algo_type, int keybit);
    int getLastGeneratedIdValue();

    void lockIdentity(int identity_sql_id, QString encrypt_lock_type, QString password);

private:
    int last_generated_identity_sql_id;

signals:
    
public slots:
    
};

#endif // P2PCRYPT_ALGO_H
