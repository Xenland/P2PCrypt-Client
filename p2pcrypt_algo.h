#ifndef P2PCRYPT_ALGO_H
#define P2PCRYPT_ALGO_H

#include <QObject>
#include <QDebug>
#include <QtCore>
#include <QFuture>

class p2pcrypt_algo : public QObject
{
    Q_OBJECT
public:
    explicit p2pcrypt_algo(QObject *parent = 0);
    void testFunc();

private:


signals:
    
public slots:
    
};

#endif // P2PCRYPT_ALGO_H