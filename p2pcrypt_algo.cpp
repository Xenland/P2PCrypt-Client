#include "p2pcrypt_algo.h"

p2pcrypt_algo::p2pcrypt_algo(QObject *parent) :
    QObject(parent)
{

}


void p2pcrypt_algo::generateNewIdentity(QString identity_algo_type, int keybit){
    qDebug() << identity_algo_type;


    //If RSA is selected then...
    if(identity_algo_type == "RSA"){
        //Sanataize and enforce restrictions
            //Restrict keys to a 2048 minimum
            if(keybit < 2048){
                keybit = 2048;
            }

        //Begin generation logic

        //Generate RSA key pair
        RSA *keypair = RSA_generate_key(keybit, 37, NULL, NULL);

        //RSA vars
            BIO *pri = BIO_new(BIO_s_mem());
            BIO *pub = BIO_new(BIO_s_mem());

            //RSA:
            PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
            PEM_write_bio_RSAPublicKey(pub, keypair);

            //RSA: get size
            size_t pri_len = BIO_pending(pri);
            size_t pub_len = BIO_pending(pub);

            //Memory: Allocate
            char *pri_key = (char*)malloc(pri_len + 1);
            char *pub_key = (char*)malloc(pub_len + 1);

            //Memory: Write
            BIO_read(pri, pri_key, pri_len);
            BIO_read(pub, pub_key, pub_len);

            //Memory: Set end of string
            pri_key[pri_len] = '\0';
            pub_key[pub_len] = '\0';

        /* SQL
         *Add newly generated keypair to the DB and return the integer of the newly inserted id #
         */
        p2pcrypt_sql identity_ring;
        identity_ring.connectToDatabase("identity_keyring.sqlite3");
        if(identity_ring.database_handle.open()){
            qDebug() << "Successfully Opened!";
        }else{
            qDebug() << "Failed to open";
        }

    }
}
