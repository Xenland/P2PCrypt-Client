#ifndef P2PCRYPT_ALGO_H
#define P2PCRYPT_ALGO_H

#include <QObject>
#include <QDebug>
#include <QtCore>
#include <QFuture>

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

private:
    QString * last_generated_identity_sql_id;

    QString * generated_public_key;
    QString * generated_private_key;

signals:
    
public slots:
    
};

#endif // P2PCRYPT_ALGO_H
