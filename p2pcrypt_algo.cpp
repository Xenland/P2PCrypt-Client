#include "p2pcrypt_algo.h"

p2pcrypt_algo::p2pcrypt_algo(QObject *parent) :
    QObject(parent)
{
}


void p2pcrypt_algo::generateNewIdentity(QString identity_algo_type){
    qDebug() << identity_algo_type;
}
