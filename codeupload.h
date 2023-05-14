#ifndef CODEUPLOAD_H
#define CODEUPLOAD_H

#include <QDialog>
#include "choose.h"
#include <QFileDialog>

namespace Ui {
class codeupload;
}

class codeupload : public QDialog
{
    Q_OBJECT

public:
    explicit codeupload(QWidget *parent = nullptr);
    ~codeupload();


private slots:
    void on_back_clicked();

    void on_uploadreal_clicked();

    void on_uploadfake_clicked();

    void on_check_clicked();

private:
    Ui::codeupload *ui;
    Choose *c;
    QString filePathReal =" ";
    QString filePathFake =" ";
};


#endif // CODEUPLOAD_H
