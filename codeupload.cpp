#include "codeupload.h"
#include "ui_codeupload.h"
#include "choose.h"
#include <QDebug>
#include <plagirism.h>


codeupload::codeupload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::codeupload)
{
    ui->setupUi(this);
}

codeupload::~codeupload()
{
    delete ui;
}

void codeupload::on_back_clicked()
{
    c =new Choose();
    c->show();
    this->close();
}



void codeupload::on_uploadreal_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Real Text File"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty())
    filePathReal = fileName;
    qDebug() << "Real file path: " << filePathReal;
}


void codeupload::on_uploadfake_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Fake Text File"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty())
    filePathFake = fileName;
    qDebug() << "Fake file path: " << filePathFake;

}


void codeupload::on_check_clicked()
{
    plagirism x;
    x.code(filePathReal, filePathFake);
    float plagirismPercent = x.getPercent();

    if(x.getPercent()>40)
    {
    ui->plg2->setText("The two codes are most likely copied from each other.");
    ui->plg->setText("The plagirism percent between the two codes are: " + QString::number(plagirismPercent) + "%.");
    }
    else
    {
    ui->plg2->setText("The two codes are most likely not copied from each other.");
    ui->plg->setText("The plagirism percent between the two codes are: " + QString::number(plagirismPercent) + "%.");
    }

}

