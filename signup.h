#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Signup;
}
class MainWindow;
class Signup : public QDialog
{
    Q_OBJECT

public:

    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:

    void on_back_clicked();

    void on_createaccount_clicked();


private:
    Ui::Signup *ui;
    MainWindow* main;

};

#endif // SIGNUP_H
