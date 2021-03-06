#include "p2pcrypt_sql.h"

p2pcrypt_sql::p2pcrypt_sql(QObject *parent) :
    QObject(parent)
{
}

void p2pcrypt_sql::connectToDatabase(QString sql_filename, QString connection_name){
    database_handle = QSqlDatabase::addDatabase("QSQLITE", connection_name);

    QString sql_dir =  QCoreApplication::applicationDirPath() + QDir::separator()+"db" + QDir::separator() + sql_filename;
    qDebug() << sql_dir;
    database_handle.setDatabaseName(sql_dir);
}
