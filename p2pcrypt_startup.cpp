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

        //Add this generate identity widget to the generate identity layout
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

        //Add this "generating identity is working" widget to the generate identity layout
        generate_identity_layout->addWidget(generating_identity_working_widget);

        //Create layout to hold "multiple QT objects to store in the generate_identity_widget
        QVBoxLayout * generating_identity_layout_contents = new QVBoxLayout;

            //Attach this laytout the the "generating_identity_working_widget"
            generating_identity_working_widget->setLayout(generating_identity_layout_contents);

        //Begin adding objects to the generating_identity_layout_contents
            //Add text alerting the user that we are generating an identity
            QLabel * generating_identity_label = new QLabel("Generating an identity");
            generating_identity_label->setAlignment(Qt::AlignHCenter);
            generating_identity_layout_contents->addWidget(generating_identity_label);

    /*Create a "finished generating identity" window to show the user/operator the details on the identity just created
      aswell as display a "Finished" button*/
    generating_identity_finished_widget = new QWidget;
    generating_identity_finished_widget->hide();

        //Add this "generating_identity_finished" widget to the generate identity layout
        generate_identity_layout->addWidget(generating_identity_finished_widget);

        //Create layout to hold "multiple QT objects to store in the generate_identity_widget
        QVBoxLayout * generating_identity_finished_layout_contents = new QVBoxLayout;

            //Attach this layout the the "generating_identity_working_widget"
            generating_identity_finished_widget->setLayout(generating_identity_finished_layout_contents);

        //Begin adding objects to the generating_identity_finished_layout_contents
            //Add text about keypair information
            generating_identity_finished_information_label = new QLabel("");
            generating_identity_finished_information_label->setAlignment(Qt::AlignHCenter);
            generating_identity_finished_information_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
            generating_identity_finished_layout_contents->addWidget(generating_identity_finished_information_label);

            //Create HBox to hold group of buttons
                //Create widget to house layout which the widge twill be added to layout contents
                QWidget * generating_identity_finished_vbox_widget_buttons = new QWidget;

                    //Attach new horizonal layout to the widget for grouping buttons
                    QVBoxLayout * generating_identity_finished_vbox_buttons = new QVBoxLayout;
                    generating_identity_finished_vbox_widget_buttons->setLayout(generating_identity_finished_vbox_buttons);

                        //Add buttons to layout
                            //Back to main menu button
                            QPushButton * generating_identity_finished_goback = new QPushButton("<= Back to Main Menu");
                            generating_identity_finished_vbox_buttons->addWidget(generating_identity_finished_goback);
                            connect(generating_identity_finished_goback, SIGNAL(clicked()), SLOT(showBootScreen_slot()));

                            //Attach password to this identityu button
                            QPushButton * generating_identity_finished_lock_with_pass = new QPushButton("Set Password for new Identity");
                            generating_identity_finished_vbox_buttons->addWidget(generating_identity_finished_lock_with_pass);

                            //Connect to network with identity
                            QPushButton * generating_identity_finished_continue = new QPushButton("Connect to P2P Network");
                            generating_identity_finished_vbox_buttons->addWidget(generating_identity_finished_continue);

                //Attach to gen identity finished layout
                generating_identity_finished_layout_contents->addWidget(generating_identity_finished_vbox_widget_buttons);
}

void p2pcrypt_startup::hideAllBootScreens(){
    qDebug() << "Hide all boot screens";

    main_boot_widget->hide();
    generate_identity_widget->hide();
    generating_identity_working_widget->hide();
    generating_identity_finished_widget->hide();
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

void p2pcrypt_startup::showBootScreen_slot(){
    hideAllBootScreens();
    showBootScreen();
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

    //Hide all screens
    hideAllBootScreens();

    //Display "working" screen to signify we are generating a new identity window
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

    generate_identity_future = QtConcurrent::run(this, &p2pcrypt_startup::generateNewIdentityThread, algo_type, keybit);
    generate_identity_future_watcher.setFuture(generate_identity_future);
    connect(&generate_identity_future_watcher, SIGNAL(finished()), SLOT(showGenerateIdentityFinished()));
}


/**
 * Used to generate a new identity in the gui "generate identity" menu
 * @brief p2pcrypt_startup::generateNewIdentityThread
 * @param algo_type
 * @param keybit
 */
void p2pcrypt_startup::generateNewIdentityThread(QString algo_type, int keybit){
    //Create the "Algo" object so we can generate a new address.
    p2pcrypt_algo * algo_object = new p2pcrypt_algo;
    algo_object->generateNewIdentity(algo_type, keybit);
    last_generated_identity_id = algo_object->getLastGeneratedIdValue();
}


/**
 * @brief p2pcrypt_startup::showGenerateIdentityFinished
 */
void p2pcrypt_startup::showGenerateIdentityFinished(){
    qDebug() << "generate identity finished";

    //Hide all screens
    hideAllBootScreens();

    //Local variables
    QString * public_key_plain_text;

    //Local Flags
    int finished_success = 0; //if zero: Display a "failed to retrieve identity" info; if (1)one Display "identity information"

    //Enforce variable limits
    int generated_sql_id = last_generated_identity_id;
    if(generated_sql_id < 1){
        generated_sql_id = 0;
    }

    //Display information on the identity just created
        //Query SQL for the information on the identity just created
        p2pcrypt_sql * identity_ring = new p2pcrypt_sql;
        identity_ring->connectToDatabase("identity_keyring.sqlite3", "select_recently_generated_identity");
        if(identity_ring->database_handle.open()){

            //Attempt to select identity information recently created
            QString generated_id_string = QString::number(generated_sql_id);
            QString select_identity_sql_string = QString("SELECT `public_key` FROM `local_identities` WHERE `id` = %1 LIMIT 0,1").arg(generated_id_string);
            qDebug() << select_identity_sql_string;
            QSqlQuery select_identity = QSqlQuery(select_identity_sql_string, identity_ring->database_handle);

            if(select_identity.exec()){
                while(select_identity.next()){
                    finished_success = 1;
                    public_key_plain_text = new QString(select_identity.value(0).toString());
                }
            }
        }else{
            qDebug() << "failed to open keyring";
        }

        //Now display failed or success message
        if(finished_success == 1){
            //Strip newlines/return carriages from identity
            public_key_plain_text->simplified();

                //Convert simpilifed identity into a "handle" (Sha512) -> (md5)
                QCryptographicHash * sha512_handle = new QCryptographicHash(QCryptographicHash::Sha512);
                sha512_handle->addData((const char *)public_key_plain_text, public_key_plain_text->size());

                    //Convert Sha512 handle to a shorter Md5 handle
                    QCryptographicHash * md5_handle = new QCryptographicHash(QCryptographicHash::Md5);
                    md5_handle->addData((const char*) sha512_handle->result().toHex(), sha512_handle->result().toHex().size());
                    qDebug() << md5_handle->result().toHex();


                    //Set the md5 handle into the "finished" page
                    QString generating_identity_finished_information_string = QString("Your identity information<br/><br/> <b>%1</b> <br/><br/> What would you like to do next? ").arg(QString(md5_handle->result().toHex()));
                    generating_identity_finished_information_label->setText(generating_identity_finished_information_string);

            //We are ready to display the information we just compiled
            generating_identity_finished_widget->show();

        }else{
            //Failed to get information display error/alert

            //We are ready to display the information we just compiled
            generating_identity_finished_widget->show();
        }

    qDebug() << "showgenerate identity finished";
}
