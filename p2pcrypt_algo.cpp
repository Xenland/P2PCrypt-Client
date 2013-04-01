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
        identity_ring.connectToDatabase("identity_keyring.sqlite3", "add_newly_generated_keypair_identity_to_db");
        if(identity_ring.database_handle.open()){
            qDebug() << "OPENED";
            //Attempt to insert newly generated identity into the SQLite3 database.
            QSqlQuery * append_identity = new QSqlQuery(identity_ring.database_handle);
            append_identity->prepare("INSERT INTO `local_identities` (`public_key`, `private_key`) VALUES(:public_key, :private_key)");
            append_identity->bindValue(":public_key", pub_key);
            append_identity->bindValue(":private_key", pri_key);

            if(append_identity->exec()){
                qDebug() << "EXECUTING";
                //Attempt to get the last sql insert id
                QVariant last_id_variant = append_identity->lastInsertId();
                int last_id = last_id_variant.toInt();
                last_generated_identity_sql_id = last_id;
                qDebug() << "INSERTED INTO :" << last_generated_identity_sql_id;

            }else{
                qDebug() << "Failed to insert";
            }
        }else{
            qDebug() << "Failed to open";
        }

    }
}

int p2pcrypt_algo::getLastGeneratedIdValue(){
    int lastIdValue = 0;

    //Is initialized and set
    if(last_generated_identity_sql_id > 0){
        lastIdValue = last_generated_identity_sql_id;
    }

    return lastIdValue;
}


void p2pcrypt_algo::lockIdentity(int identity_sql_id, QString encrypt_lock_type, QString password_to_lock){
     if(encrypt_lock_type == "AES | SHA256"){
        //TEST AES-CTR
            /** Set variables **/
                //Track bytes read
                int bytes_read = 0;

                //encrypt/decrypt vars
                unsigned char * indata;
                unsigned char * outdata;

                //IV
                unsigned char iv[AES_BLOCK_SIZE];

                //AES: key format
                AES_KEY key;

                //Encrytion Key
                const unsigned char * enc_key;
                    //Set encryption key
                    enc_key = (unsigned const char*)"1234567812345678"; //Set encryption key

            /** Collect random bytes **/
            if(!RAND_bytes(iv, AES_BLOCK_SIZE)){
                //Collection of valid random bytes failed, return debug message
                qDebug() << "Failed collect randomness, The universe must be in tune right now";
            }

            /** allocate the password(enc_key) to an AES Key format(key)  **/
            if(AES_set_encrypt_key(enc_key, 128, &key) < 0)
            {
                qDebug() << "Set encryption key";
            }


            /** Now we are booted,
             *  initizalise the encryption stuff
             **/
            unsigned char ivec[AES_BLOCK_SIZE];
            unsigned int num;
            unsigned char ecount[AES_BLOCK_SIZE];

            num = 0;
            memset(ecount, 0, AES_BLOCK_SIZE);

            /* Initialise counter in 'ivec' to 0 */
            memset(ivec + 8, 0, 8);

            /* Copy IV into 'ivec' */
            memcpy(ivec, iv, 8);

                /** ENCRYPT
                        ((Yes we could be using a pointer below))
                **/
                int keep_encrypting = 1;
                int tracker_start = 0;

                QString plaintext_to_encrypt = "This is a very long long long long long string";
                QString encrypted_plaintext_as_bytes;
                while(keep_encrypting == 1){
                    //Check if we should continue encryption proccesses.
                    if((tracker_start + AES_BLOCK_SIZE) >= plaintext_to_encrypt.length()){
                        //Stop keep encrypting proccess.
                        keep_encrypting = 0;
                    }

                    //Convert QString(plaintext) to unsigned char (plaintext)
                    QString subString_of_plaintext = plaintext_to_encrypt.mid(tracker_start,AES_BLOCK_SIZE);
                    QByteArray subString_of_plaintext_bytearray = subString_of_plaintext.toLocal8Bit();
                    const char * subString_of_plaintext_char = subString_of_plaintext_bytearray.data();
                    unsigned char * subString_of_plaintext_unsignedChar;
                    subString_of_plaintext_unsignedChar = (unsigned char*)subString_of_plaintext_char;

                    //Set the next block to encrypt
                    indata = subString_of_plaintext_unsignedChar;

                    //Generate next AES encrypted block
                    AES_ctr128_encrypt(indata,
                                       outdata,
                                       bytes_read,
                                       &key,
                                       ivec,
                                       ecount,
                                       &num);


                    encrypted_plaintext_as_bytes.append(QString::fromLocal8Bit((char*)outdata));

                    //Increment tracker
                    tracker_start = tracker_start + AES_BLOCK_SIZE;

                }

                qDebug() << encrypted_plaintext_as_bytes;
     }
 }
