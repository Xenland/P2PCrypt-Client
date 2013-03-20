#include <QApplication>
#include <QDebug>
#include <QtDebug>
#include <QWidget>
#include <QFrame>

#include <memory>


#include "p2pcrypt_startup.h"


int main(int argc, char *argv[])
{
    //Start QT
    QApplication a(argc, argv);


    //Define Main() Variables
    QHBoxLayout * main_window_layout = new QHBoxLayout;
    QFrame * boot_frame = new QFrame;



    /*************************
     * Begin P2P Crypt Logic *
     *************************/

    //QT requires a qwidget centeral window or no windows will show so we use the main window as a place holder.
    QWidget main_window;
    main_window.setLayout(main_window_layout);
    main_window.setWindowTitle("P2P Crypt Client");
    main_window.setMinimumSize(400, 200);
    main_window.resize(400,200);
    main_window.show();


    //Program just started, Display the boot window
    main_window_layout->addWidget(boot_frame);
    boot_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Test
    p2pcrypt_startup * startup = new p2pcrypt_startup();
    startup->setBootFrame(*boot_frame);
    startup->loadBootScreen();

    //We want the boot screen to be the start up screen.
    startup->showBootScreen();

    return a.exec();
}
