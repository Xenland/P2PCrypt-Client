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
     if(encrypt_lock_type == "AES256/SHA256"){
        //Lock identity with AES256 and SHA256 the password

            //Generate a Key and IV for the AES256 password
            const EVP_CIPHER *cipher;
            const EVP_MD *dgst = NULL;
            unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
            const char *password = (const char *) password_to_lock.toStdString().c_str();

            const unsigned char *salt = NULL;
            int i;

            OpenSSL_add_all_algorithms();

            cipher = EVP_get_cipherbyname("aes-256-cbc");
            if(!cipher) {
                qDebug() << "Cipher not found and/or not supported";
            }

            dgst=EVP_get_digestbyname("md5"); //TO DO: CHANGE THIS TO SHA256 if possible....
            if(!dgst) {
                qDebug() << "Digest not found or not support";
            }

            if(!EVP_BytesToKey(cipher, dgst, salt,(unsigned char *) password,strlen(password), 1, key, iv))
            {
                qDebug() << "BYTES TO KEY FAILED";

            }

            EVP_CIPHER_CTX e_ctx, d_ctx;
            EVP_CIPHER_CTX_init(&e_ctx);
            EVP_EncryptInit_ex(&e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
            EVP_CIPHER_CTX_init(&d_ctx);
            EVP_DecryptInit_ex(&d_ctx, EVP_aes_256_cbc(), NULL, key, iv);

            //Begin Encrypt....
            /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
            const char * plaintext = "HELLO WORLD";
            int  len = sizeof(plaintext);
            int c_len = len + 256, f_len = 0;
            unsigned char *ciphertext = (unsigned char *)malloc(c_len);

            /* allows reusing of 'e' for multiple encryption cycles */
            EVP_EncryptInit_ex(&e_ctx, NULL, NULL, NULL, NULL);

            /* update ciphertext, c_len is filled with the length of ciphertext generated,
            *len is the size of plaintext in bytes */
            EVP_EncryptUpdate(&e_ctx, ciphertext, &c_len, (const unsigned char *)plaintext, len);

            /* update ciphertext with the final remaining bytes */
            EVP_EncryptFinal_ex(&e_ctx, ciphertext+c_len, &f_len);

            len = c_len + f_len;

            QByteArray cipher_text_string_base64 = QByteArray((const char *)ciphertext);
            qDebug () << cipher_text_string_base64.toBase64();
     }
 }
