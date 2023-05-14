#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"
#include <QMessageBox>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    MainWindow conn;
    if(!conn.connOpen())
    {
        ui->connectioncheck->setText("Failed to open database.");
    }
    else
    {
        ui->connectioncheck->setText(" ");
    }
}

Signup::~Signup()
{
    delete ui;
}


void Signup::on_back_clicked()
{
    main =new MainWindow();
    main ->show();
    this->close();
}

bool isUsernameAvailable(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT Username FROM clients WHERE Username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()) {
        // if the query is successful and returns at least one row,
        // it means the username already exists in the database
        return false;
    } else {
        // if the query fails or returns no rows, the username is available
        return true;
    }
}

void Signup::on_createaccount_clicked()
{
    MainWindow conn;
    QString First, Last, Username, Password;

    First=ui->Firstname->text();
    Last=ui->Lastname->text();
    Username=ui->Usernamesignup->text();
    Password=ui->Passwordsignup->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open database.";
        return;
    }
    if(First==""||Last==""||Username==""||Password=="")
    {
        ui->connectioncheck->setText("Please add your information.");
        return;
    }
    else
    {
    conn.connOpen();

    QSqlQuery qry;
    qry.prepare("INSERT INTO clients (\"First Name\", \"Last Name\", Username, Password) values ('"+First+"','"+Last+"','"+Username+"','"+Password+"')");

    if(!isUsernameAvailable(Username))
    {
        ui->connectioncheck->setText("This username already exists.");
        return;
    }

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Create Account."),tr("Done."));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
    }
    }
}

