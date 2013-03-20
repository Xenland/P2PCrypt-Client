#include "p2pcrypt_startup.h"

/*
 *  Initializers
 */
p2pcrypt_startup::p2pcrypt_startup(QObject *parent) :
    QObject(parent)
{
    qDebug() << "startup\n";
}


/**
 * @brief p2pcrypt_startup::setBootFrame
 * @param boot_frame
 */
void p2pcrypt_startup::setBootFrame(QFrame &boot_frame){
    startup_frame = &boot_frame;
}



/*************************************************************************************************************
 * Main Methods
 */

/**
 * @brief p2pcrypt_startup::loadBootScreen
 */
void p2pcrypt_startup::loadBootScreen(){
    qDebug() << "print\n";

    //Create a grid for the "Boot Screen" frame
     QGridLayout * boot_grid;
     boot_grid = new QGridLayout(startup_frame);

     //Add contents to the grid
         //Tell the operator what this page does
         QLabel * boot_screen_instructions;
         boot_screen_instructions = new QLabel("<span style='text-align:center;font-size:15pt'>P2P Crypt</span>");
         boot_screen_instructions->setAlignment(Qt::AlignHCenter);
         boot_screen_instructions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
         boot_grid->addWidget(boot_screen_instructions, 0, 0);

         //Add a "Generate Identity" button that will triger a menu to open
         QPushButton * generate_identity_btn;
         generate_identity_btn = new QPushButton("Generate Identity");
         generate_identity_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
         boot_grid->addWidget(generate_identity_btn,1,0);

         //Add a "Load Identity" button that will trigger a menu to open
         QPushButton * load_identity_btn;
         load_identity_btn = new QPushButton("Load Identity");
         load_identity_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
         boot_grid->addWidget(load_identity_btn,2,0);

}

/**
 * @brief p2pcrypt_startup::showBootScreen
 */
void p2pcrypt_startup::showBootScreen(){
    qDebug() << "Showing boot screen.";

    startup_frame->show();
}
