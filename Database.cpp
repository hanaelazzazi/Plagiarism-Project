#include "Database.h"


Database::Database(const QString& dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (QFileInfo::exists(dbName)) {
        if (!db.open()) {
            qDebug() << "Can't open database: " << db.lastError().text();
            exit(1);
        }
        else {
            qDebug() << "Opened database successfully.";
        }
    }
    else {
        if (!db.open()) {
            qDebug() << "Can't create database: " << db.lastError().text();
            exit(1);
        }
        else {
            qDebug() << "Created database successfully.";
        }
    }
}


Database::Database() {
    //no implementation i just created a default constructor because other wise it gives a complier error

}
