#include <QApplication>
#include <QDebug>
#include <QtDebug>
#include <QWidget>
#include <QFrame>

#include <memory>


#include "p2pcrypt_startup.h"

/** Global variables **/
QString current_version;

int main(int argc, char *argv[])
{
    //Start QT
    QApplication a(argc, argv);


    //Define Main() Variables
    current_version = QString("Dev Build v0.0.3");
    QHBoxLayout * main_window_layout = new QHBoxLayout;
    QFrame * boot_frame = new QFrame;



    /*************************
     * Begin P2P Crypt Logic *
     *************************/

    //QT requires a qwidget centeral window or no windows will show so we use the main window as a place holder.
    QWidget main_window;
    main_window.setLayout(main_window_layout);
    main_window.setWindowTitle("P2P Crypt Client | "+current_version);
    main_window.setMinimumSize(400, 200);
    main_window.resize(400,200);
    main_window.show();


    /** Define the boot/startup frame **/
    boot_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p2pcrypt_startup * startup = new p2pcrypt_startup();
    startup->setBootFrame(*boot_frame);
    startup->loadBootScreen();

        //Add boot/startup frame to the main window.
        main_window_layout->addWidget(boot_frame);



    /** Define the "Account Unlocked" frame **/
        //TO DO HERE...........


    /*************************
     *  END P2P Crypt Logic  *
     *************************/

    //Render only the boot screen at startup
    startup->showBootScreen();

    return a.exec();
}
