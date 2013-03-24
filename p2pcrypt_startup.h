#ifndef P2PCRYPT_STARTUP_H
#define P2PCRYPT_STARTUP_H

#include <QObject>
#include <QDebug>
#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QMovie>
#include <QLabel>
#include <QThread>
#include <QtCore>
#include <QFuture>
#include <QtConcurrentRun>

#include "p2pcrypt_startup.h"
#include "p2pcrypt_algo.h"


class p2pcrypt_startup : public QObject
{
    Q_OBJECT
public:
    p2pcrypt_startup(QObject *parent = 0);
    void setBootFrame(QFrame &boot_frame);

    /* Main Methods */
    void loadBootScreen();
    void showBootScreen();

signals:
    
private slots:
    void showGenerateIdentity();
    void generate_new_identity();

private:
    p2pcrypt_algo * generate_identity_object;

    /* General GUI Variables */
    QFrame * startup_frame;

        QWidget * main_boot_widget;
        QWidget * generate_identity_widget;
            QComboBox * identity_pick_algo;

        QWidget * generating_identity_working_widget;

   void hideAllBootScreens();
};

#endif // P2PCRYPT_STARTUP_H
