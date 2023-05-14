#include "choose.h"
#include "ui_choose.h"
#include "codeupload.h"
#include "upload.h"

Choose::Choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
}

Choose::~Choose()
{
    delete ui;
}

void Choose::on_code_clicked()
{
    this->hide();
    codeupload code;
    code.setModal(true);
    code.exec();
}


void Choose::on_writing_clicked()
{
    this->hide();
    upload up;
    up.setModal(true);
    up.exec();
}

