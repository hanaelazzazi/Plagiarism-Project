#include "detection.h"
#include "ui_detection.h"
#include "upload.h"


detection::detection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detection)
{
    ui->setupUi(this);
}

detection::~detection()
{
    delete ui;
}


void detection::on_Back_clicked()
{
    c =new Choose();
    c->show();
    this->close();
}

void detection::v11(QString q)
{
    qDebug()<<q;
    ui->ps->setText("The name of the file that is plagirised from: ");
    ui->sentpl->setText(q);
}

void detection::v22(QString w)
{
    qDebug()<<w;
    ui->playgirismdisplay->setText(w + "%");
}



