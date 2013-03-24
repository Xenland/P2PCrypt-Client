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

        //Begin local logic
        RSA *keypair = RSA_generate_key(keybit, 37, NULL, NULL);
    }
}
