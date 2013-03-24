#include "p2pcrypt_sql.h"

p2pcrypt_sql::p2pcrypt_sql(QObject *parent) :
    QObject(parent)
{
}

void p2pcrypt_sql::connectToDatabase(QString sql_filename){
    database_handle = QSqlDatabase::addDatabase("QSQLITE");
    database_handle.setDatabaseName("./db/"+sql_filename);
}
