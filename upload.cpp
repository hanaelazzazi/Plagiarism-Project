#include "upload.h"
#include "ui_upload.h"
#include <QFileDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "choose.h"
#include "aidetection.h"
#include "plagirism.h"

upload::upload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::upload),
    m_checkbox3Selected(false),
    m_checkboxSelected(false)// Initialize the variable to false
{
    ui->setupUi(this);
    // Create a new button group and add the checkboxes to it
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->checkBox);
    m_buttonGroup->addButton(ui->checkBox_3);

    // Set the exclusive property to true, to ensure only one checkbox can be checked at a time
    m_buttonGroup->setExclusive(true);

    // Hide the checkboxes and the label
    ui->checkBox->setVisible(false);
    ui->checkBox_3->setVisible(false);
    ui->option->setVisible(false);

    connect(ui->checkBox, &QCheckBox::clicked, this, &upload::showLabel);
    connect(ui->checkBox_3, &QCheckBox::clicked, this, &upload::showLabel);
}


void upload::showLabel()
{
    ui->result->setText("Selected option: " + m_buttonGroup->checkedButton()->text());
}


upload::~upload()
{
    delete ui;
}

void upload::on_Back_clicked()
{
    ch = new Choose();
    ch->show();
    this->hide();
}


void upload::on_uploadbutton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Real Text File"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty())
        filePathWriting = fileName;
    qDebug() << "Real file path: " << filePathWriting;

    // Show the checkboxes
    ui->checkBox->setVisible(true);
    ui->checkBox_3->setVisible(true);
    ui->option->setVisible(true);

}

void upload::on_next_clicked()
{
    plagirism p;
    if(m_checkbox3Selected)
    {// If the third checkbox is selected
        QString h, z;
        //qDebug()<<"last1";
        p.aiDetection(filePathWriting);
        //qDebug()<<filePathWriting;
        h = QString::number(p.getPercent()) + "% of this text is generated by AI.";
        z = p.getOutput();
        //qDebug()<<h;
        valueResult(h);
        valueSent(z);
        //qDebug()<<"last";
        this->hide();
        AIdetection ai;
        ai.setModal(true);
        connect(this, SIGNAL(valueResult(QString)), &ai, SLOT(setValue(QString)));
        connect(this, SIGNAL(valueSent(QString)), &ai, SLOT(setSent(QString)));
        //qDebug()<<"please work";
        emit valueResult(h);
        emit valueSent(z);// Connect the signal to the slot
        ai.exec();
    }
    else if(m_checkboxSelected) // If the third checkbox is not selected
    {
        QString w,q;
        qDebug()<<"CLICK 2 AND 1 ";
        p.prefered(fileName,filePathWriting);
        q = QString::number(p.getPercent());
        percentValue = QString::number(p.getPercent());
        qDebug()<<"Q: "<<p.getPercent();
        qDebug()<<"Q: "<<q;
        w = p.getOutput();
        qDebug()<<"CODE ANSWER"<<w<<" "<<q;
        v1(w); // Emit the QString
        v2(q);
        this->hide();
        detection d;
        connect(this, SIGNAL(v1(QString)), &d, SLOT(v11(QString)));
        connect(this, SIGNAL(v2(QString)), &d, SLOT(v22(QString)));
        d.setModal(true);
        emit v1(w);
        emit v2(q);
        d.exec();
    }
}

void upload::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        m_checkbox3Selected = true; // Set the variable to true when the checkbox is checked
    }
    else if(arg1 == Qt::Unchecked)
    {
        m_checkbox3Selected = false; // Set the variable to false when the checkbox is unchecked
    }
}



void upload::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        m_checkboxSelected = true; // Set the variable to true when the checkbox is checked
    }
    else if(arg1 == Qt::Unchecked)
    {
        m_checkboxSelected = false; // Set the variable to false when the checkbox is unchecked
    }
}

