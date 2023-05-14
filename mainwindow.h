#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMainWindow>
#include "signup.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase signup;
    void connClose()
    {
      signup.close();
      signup.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        signup = QSqlDatabase::addDatabase("QSQLITE");
        signup.setDatabaseName("/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Database/signup.db");
        if(!signup.open())
        {
            qDebug()<<("Failed to open database.");
            return false;
        }
        else
        {
            qDebug()<<("Database successfully opened.");
            return true;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Signin_clicked();

    void on_Signup_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
