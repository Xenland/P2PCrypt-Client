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
    main_boot_widget = new QWidget;
    main_boot_widget->hide();

        //Add this main boot widget to the main boot layout
        main_boot_layout->addWidget(main_boot_widget);

        //Create layout to hold "multiple" QT objects to store in the main_boot_widget
        QVBoxLayout * main_boot_layout_contents = new QVBoxLayout;

            //Attach this layout to the "main_boot_widget"
            main_boot_widget->setLayout(main_boot_layout_contents);

        //Begin adding objects to the main_boot_layout_contents
            //Instructions/Logo Text
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
    generate_identity_widget = new QWidget;
    generate_identity_widget->hide();

        //Add this generate identity widget to the main boot layout
        generate_identity_layout->addWidget(generate_identity_widget);

        //Create layout to hold "multiple QT objects to store in the generate_identity_widget
        QVBoxLayout * generate_identity_layout_contents = new QVBoxLayout;

            //Attach this laytout the the "generate_identity_widget"
            generate_identity_widget->setLayout(generate_identity_layout_contents);

        //Begin adding objects to the generate_identity_layout_contents
            //Instructions on how to generate an identity
            QLabel * generate_identity_instructions = new QLabel("<p>Select the algo most feasable for your situation or if you are unsure just use the most secure solution which is set by default.</p>");
            generate_identity_instructions->setAlignment(Qt::AlignHCenter);
            generate_identity_instructions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            generate_identity_instructions->setWordWrap(1);
            generate_identity_layout_contents->addWidget(generate_identity_instructions, 0, 0);

            //Lists of algos for generating an identity
            identity_pick_algo = new QComboBox;
            identity_pick_algo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                //Add data to combo box
                identity_pick_algo->addItem("RSA");
                identity_pick_algo->addItem("Elliptical Curve");
                identity_pick_algo->addItem("AES (Not recommended)");

            generate_identity_layout_contents->addWidget(identity_pick_algo);


            //Create button to initiate the generation of an address
            QPushButton * identity_generate_btn = new QPushButton("Generate New Identity");
            identity_generate_btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            generate_identity_layout_contents->addWidget(identity_generate_btn);

                //Add slot to catch the "identity generate button" click
                    //Initiate Generation of Identity
                    connect(identity_generate_btn, SIGNAL(clicked()), SLOT(generate_new_identity()));




    //Create a "generating identity" working window to show that the program is "doing something"
    generating_identity_working_widget = new QWidget;
    generating_identity_working_widget->hide();

        //Add this "generating identity is working" widget to the main boot layout
        generate_identity_layout->addWidget(generating_identity_working_widget);

        //Create layout to hold "multiple QT objects to store in the generate_identity_widget
        QVBoxLayout * generating_identity_layout_contents = new QVBoxLayout;

            //Attach this laytout the the "generating_identity_working_widget"
            generating_identity_working_widget->setLayout(generating_identity_layout_contents);
}

void p2pcrypt_startup::hideAllBootScreens(){
    qDebug() << "Hide all boot screens";

    main_boot_widget->hide();
    generate_identity_widget->hide();
}

/**
 * @brief p2pcrypt_startup::showBootScreen
 **/
void p2pcrypt_startup::showBootScreen(){
    qDebug() << "Showing boot screen.";

    //Display startup_frame
    startup_frame->show();

        //Display boot screen from startup frame
        main_boot_widget->show();
}


/**
 * @brief showGenerateIdentity
 **/
 void p2pcrypt_startup::showGenerateIdentity(){
     hideAllBootScreens();

    qDebug() << "Showing generate identity page";

    //Show generate identity screen
    generate_identity_widget->show();
 }


/**
* @brief p2pcrypt_startup::generate_new_identity
*/
void p2pcrypt_startup::generate_new_identity(){
    qDebug() << "Generating";

    //Display "working" screen to signify we are generating a new identity window
    hideAllBootScreens();
    generating_identity_working_widget->show();

    //Check what the combo/dropdown box is currently selected as
    int currently_selected_algo_type = identity_pick_algo->currentIndex();
    QString algo_type;

    //Static keybit (for now)
    int keybit = 2048;

    if(currently_selected_algo_type == 0){
        algo_type = "RSA";
    }else if(currently_selected_algo_type == 1){
        algo_type = "ECC";
    }else if(currently_selected_algo_type == 2){
        algo_type = "AES";
    }else{
        //if none selected (somehow) default to RSA
        algo_type = "RSA";
    }

    QFuture<void> generate_identity_future = QtConcurrent::run(generate_identity_object, &p2pcrypt_algo::generateNewIdentity, algo_type, keybit);
}
