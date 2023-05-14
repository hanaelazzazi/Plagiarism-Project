#include "aidetection.h"
#include "ui_aidetection.h"
#include "upload.h"


AIdetection::AIdetection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AIdetection)
{
    ui->setupUi(this);
}

AIdetection::~AIdetection()
{
    delete ui;
}

void AIdetection::on_back_clicked()
{
    u = new upload();
    u->show();
    this->hide();
}

void AIdetection::setValue(QString value)
{
    ui->humanORai->setText(value);// Set the value to the QLabel object
}

