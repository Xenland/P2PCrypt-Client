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

private:
    QFrame * startup_frame;

        QWidget * main_boot_widget;
        QWidget * generate_identity_widget;

        /*Generate Identity Global Private*/
        QWidget * generate_identity_movie_contents;
        QLabel * generate_identity_movie_label;
        QMovie * generate_identity_movie;



   void hideAllBootScreens();
};

#endif // P2PCRYPT_STARTUP_H
