#ifndef UPLOAD_H
#define UPLOAD_H

#include <QDialog>
#include "mainwindow.h"
#include "detection.h"
#include "choose.h"
#include <QButtonGroup>
#include <QLabel>


namespace Ui {
class upload;
}

class upload : public QDialog
{
    Q_OBJECT

public:
    explicit upload(QWidget *parent = nullptr);
    ~upload();


signals:
    QString valueResult(QString y);
    QString valueSent(QString z);
    void v1(QString q);
    void v2(QString w);

private slots:
    void on_uploadbutton_clicked();

    void on_next_clicked();

    void showLabel();

    void on_Back_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);


private:
    Ui::upload *ui;
    Choose *ch;
    QString fileName=" ";
    QString filePathWriting ="";
    QButtonGroup *m_buttonGroup;
    bool m_checkbox3Selected,m_checkboxSelected; //, m_checkbox2Selected, m_checkboxSelected;
    QString percentValue;
    QLabel *humanORai;
    QLabel *m_humanORaiLabel;
    QLabel *m_aisentLabel;
    QLabel *m_playgirismdisplay;
    QLabel *m_sentpl;
    QLabel *m_ps;


};

#endif // UPLOAD_H
