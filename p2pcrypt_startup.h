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
#include <QCryptographicHash>

#include "p2pcrypt_startup.h"
#include "p2pcrypt_algo.h"


class p2pcrypt_startup : public QObject
{
    Q_OBJECT

public:
    p2pcrypt_startup();
    void setBootFrame(QFrame &boot_frame);

    /* Main Methods */
    void loadBootScreen();
    void showBootScreen();

    /* Backend Functions */
    void setMainWindow(QWidget * local_main_window);

signals:
    
private slots:

    /* General GUI Slots */
    void showGenerateIdentity();
    void showGenerateIdentityFinished();
    void showBootScreen_slot();
    void showSetPasswordIdentity_slot();

    /* Backend Slots */
    void generateNewIdentityThread(QString algo_type, int keybit);
    void generate_new_identity();

private:
    QWidget * main_window_handle; //Used for mostly controlling the main GUI window like resize,etc

    p2pcrypt_algo * generate_identity_object;
    QFuture<void> generate_identity_future;
    QFutureWatcher<void> generate_identity_future_watcher;

    /* General GUI Variables */
    QFrame * startup_frame;

        QWidget * main_boot_widget;
        QWidget * generate_identity_widget;
            QComboBox * identity_pick_algo;

        QWidget * generating_identity_working_widget;

        QWidget * generating_identity_finished_widget;
            QString * generating_identity_finished_information_string;
            QLabel * generating_identity_finished_information_label;

            int last_generated_identity_id;

        QWidget * generating_identity_set_pass_widget;


   /* General GUI Functions */
   void hideAllBootScreens();
};

#endif // P2PCRYPT_STARTUP_H
