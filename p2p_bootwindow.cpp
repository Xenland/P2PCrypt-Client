/*
#include <QGridLayout>
#include <QLayout>
#include <QFrame>
#include <QLabel>

#include "p2p_bootwindow.h"

p2p_bootwindow::p2p_bootwindow(QObject *parent) :
    QObject(parent)
{

}


void p2p_bootwindow::loadBootScreen(QFrame &boot_frame){

    //Greate a grid for the "Boot Screen" frame
    QGridLayout * boot_grid;
    boot_grid = new QGridLayout(&boot_frame);
    //Add contents to the grid

        //Tell the operator what this page does
        QLabel * boot_screen_instructions;
        boot_screen_instructions = new QLabel("<span style='text-align:center;font-size:15pt'>P2P Crypt</span>");
        boot_screen_instructions->setAlignment(Qt::AlignHCenter);
        boot_screen_instructions->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        boot_grid->addWidget(boot_screen_instructions, 0, 0);

        //Add a "Generate Identity" button that will triger a menu to open
        QPushButton * generate_identity_btn;
        generate_identity_btn = new QPushButton("Generate Identity");
        generate_identity_btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        boot_grid->addWidget(generate_identity_btn,1,0);

        //Add a "Load Identity" button that will trigger a menu to open
        QPushButton * load_identity_btn;
        load_identity_btn = new QPushButton("Load Identity");
        boot_grid->addWidget(load_identity_btn,2,0);
}


void showBootScreen(QFrame &boot_frame){
    boot_frame.show();
}
*/
