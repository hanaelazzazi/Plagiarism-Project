#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "upload.h"
#include "choose.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!connOpen())
    {
        ui->dbstatus->setText("Failed to open database.");
    }
    else
    {
        ui->dbstatus->setText(" ");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Signin_clicked()
{
    QString Username, Password;
    Username=ui->username->text();
    Password=ui->passwordlogin->text();
    if(!connOpen())
    {
        qDebug()<<"Failed to open database.";
        return;
    }
    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT *FROM clients WHERE Username='"+Username +"' AND Password = '"+Password +"'" );


    if(qry.exec())
    {
        int count=0;
        while(qry.next())
        {
            count++;
        }
        qDebug() << "Number of matching users: " << count;

        if(count==1)
        {
            ui->message->setText("Username and Password are correct.");
            connClose();
            this->hide();
            Choose ch;
            ch.setModal(true);
            ch.exec();

        }
        if(count<1)
        {
            ui->message->setText("Username and Password are incorrect.");
        }
        if(count>1)
        {
            ui->message->setText("Username and Password are duplicate.");
        }
    }
}

void MainWindow::on_Signup_clicked()
{
    this->hide();
    Signup signup;
    signup.setModal(true);
    signup.exec();

}

