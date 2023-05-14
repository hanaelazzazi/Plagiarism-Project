#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>

namespace Ui {
class Choose;
}

class Choose : public QDialog
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr);
    ~Choose();

private slots:


    void on_code_clicked();

    void on_writing_clicked();

private:
    Ui::Choose *ui;
};

#endif // CHOOSE_H
