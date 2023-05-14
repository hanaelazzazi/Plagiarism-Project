#ifndef AIDETECTION_H
#define AIDETECTION_H

#include <QDialog>
#include "upload.h"
namespace Ui {
class AIdetection;
}

class AIdetection : public QDialog
{
    Q_OBJECT

public:
    explicit AIdetection(QWidget *parent = nullptr);
    ~AIdetection();
public slots:
    void setValue(QString value);

private slots:
    void on_back_clicked();


private:
    Ui::AIdetection *ui;
    upload *u;
};

#endif // AIDETECTION_H
