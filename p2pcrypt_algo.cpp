#include "p2pcrypt_algo.h"

p2pcrypt_algo::p2pcrypt_algo(QObject *parent) :
    QObject(parent)
{
}


void p2pcrypt_algo::testFunc(){
    qDebug() << "STARTING THREAD FUNCTION!";

    for(int i = 0; i < 100; i++){
        qDebug() << QString::number(i);
        sleep(1);
    }
}
