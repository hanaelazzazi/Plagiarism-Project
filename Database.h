#ifndef Database_H
#define Database_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <sqlite3.h>
#include <QtSql>
#include <QString>

class Database
{
protected:
    QSqlDatabase db;
    // QSqlDatabase is a Qt class for managing database connections
    // It will be used to control the database

public:
    Database();
    // Default constructor

    Database(const QString&);
    // Constructor that takes the name of the database then opens it


};


#endif
