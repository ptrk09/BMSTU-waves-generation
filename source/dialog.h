#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <memory>
#include "handler.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    double get_dx_move();
    double get_dy_move();
    double get_dz_move();
    double get_dx_rotate();
    double get_dy_rotate();
    double get_dz_rotate();
    ~Dialog();

private slots:
    void on_pushButton_clicked();


signals:
    void send_data();


private:
    Ui::Dialog *ui;
    shared_ptr<Handler> main_handler;
    double dx_move, dy_move, dz_move;
    double dx_rotate, dy_rotate, dz_rotate;
};

#endif // DIALOG_H
