#include "filesDatabase.h"
#include "string"
#include <QtCore>
#include <QtSql>



int filesDatabase::getcount() {
    //returns the counter of how many files in the table
    return counter;
}

filesDatabase::filesDatabase() {
    // Connect to the database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Database/p.db");

    if (!db.open()) {
        qDebug() << "Can't open the files database:" << db.lastError().text();
        exit(1);
    } else {
        qDebug() << "Files database opened successfully.";
    }

    // Get the number of fields in the database
    counter = getNumFields();
}

void filesDatabase::insertfile(QString name, QString path) {
    QSqlQuery query;
    QString queryString;

    // Extract the filename from the path
    QString filename = QFileInfo(path).fileName();

    // Insert a new row into the FILES table
    queryString = "INSERT INTO FILES (NAME, PATH) VALUES (:name, :path)";
    query.prepare(queryString);
    query.bindValue(":name", filename);
    query.bindValue(":path", path);

    if (query.exec()) {
        qDebug() << "File inserted successfully.";
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
}

void filesDatabase::select(int id, QString& name, QString& path) {
    QSqlQuery query;
    QString queryString;

    // First query to retrieve the name
    // First query to retrieve the name
    queryString = "SELECT NAME FROM FILES WHERE ID = " + QString::number(id) + ";";
    if (query.exec(queryString)) {
        if (query.next()) {
            QVariant value = query.value(0); // Get the value of the first column
            if (!value.isNull() && value.isValid()) {
                name = value.toString().toUtf8().constData(); // Convert the value to a string and assign it to name
            } else {
                qDebug() << "Empty or invalid value returned for name.";
                return;
            }
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }


    // Second query to retrieve the path
    queryString = "SELECT PATH FROM FILES WHERE ID = " + QString::number(id) + ";";
    if (query.exec(queryString)) {
        if (query.next()) {
        path = query.value(0).toString().toUtf8().constData();// Get the path from the first column
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
}


int filesDatabase::getNumFields() {
    int numRows = 0;

    // Create a QSqlQuery object and execute the query
    QSqlQuery query("SELECT COUNT(*) FROM FILES");

    if (query.exec()) {
        // If the query executed successfully, get the result
        if (query.next()) {
            numRows = query.value(0).toInt(); // Get the count from the first column
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        return -1; // Error executing query
    }

    return numRows;
}
