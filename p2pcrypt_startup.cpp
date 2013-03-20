#include "p2pcrypt_startup.h"

/*
 *  Initializers
 */
p2pcrypt_startup::p2pcrypt_startup(QObject *parent) :
    QObject(parent)
{
    qDebug() << "startup\n";
}


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

    //Create a grid object for the "Boot Screen"
    QGridLayout * boot_grid = new QGridLayout(startup_frame);

        //Attach sub grid objects to the main boot grid object.
            //Attach to main boot object
            QVBoxLayout * main_boot_layout = new QVBoxLayout;
            boot_grid->addLayout(main_boot_layout, 0, 0);

            //Attach to main boot object
            QVBoxLayout * generate_identity_layout = new QVBoxLayout;
            boot_grid->addLayout(generate_identity_layout, 1, 0);

            //Attach to main boot object
            QVBoxLayout * load_identity_layout = new QVBoxLayout;
            boot_grid->addLayout(load_identity_layout, 2, 0);



    //Create "main_boot_widget" which holds the content for "main_boot_layout"
    QWidget * main_boot_widget = new QWidget;
    main_boot_widget->hide();

        //Add this main boot widget to the main boot layout
        main_boot_layout->addWidget(main_boot_widget);

        //Create layout to hold "multiple" QT objects to store in the main_boot_widget
        QVBoxLayout * main_boot_layout_contents = new QVBoxLayout;

            //Attach this layout to the "main_boot_widget"
            main_boot_widget->setLayout(main_boot_layout_contents);

        //Begin adding objects to the main_boot_layout_contents
        QLabel * boot_screen_instructions = new QLabel("<span style='text-align:center;font-size:15pt'>P2P Crypt</span>");
        boot_screen_instructions->setAlignment(Qt::AlignHCenter);
        boot_screen_instructions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        main_boot_layout_contents->addWidget(boot_screen_instructions, 0, 0);

        //Add a "Generate Identity" button that will triger a menu to open
        QPushButton * generate_identity_btn = new QPushButton("Generate Identity");
        generate_identity_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        main_boot_layout_contents->addWidget(generate_identity_btn, 1, 0);

            //Add slot to catch the Generate Identity btn click
            connect(generate_identity_btn, SIGNAL(clicked()), SLOT(showGenerateIdentity()));

        //Add a "Load Identity" button that will trigger a menu to open
        QPushButton * load_identity_btn = new QPushButton("Load Identity");
        load_identity_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        main_boot_layout_contents->addWidget(load_identity_btn, 2, 0);



    //Create "generate_identity_widget" which holds the content for "generate_identity_layout"
    QWidget * generate_identity_widget = new QWidget;
    generate_identity_widget->hide();

        //Add this generate identity widget to the main boot layout
        main_boot_layout->addWidget(generate_identity_widget);

        //Create layout to hold "multiple QT objects to store in the generate_identity_widget
        QVBoxLayout * generate_identity_layout_contents = new QVBoxLayout;

            //Attach this laytout the the "generate_identity_widget"
            generate_identity_widget->setLayout(generate_identity_layout_contents);

}

/**
 * @brief p2pcrypt_startup::showBootScreen
 **/
void p2pcrypt_startup::showBootScreen(){
    qDebug() << "Showing boot screen.";

    startup_frame->show();
}


/**
 * @brief showGenerateIdentity
 **/
 void p2pcrypt_startup::showGenerateIdentity(){
     qDebug() << "Showing generate identity page";

 }
