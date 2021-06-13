#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    dx_move = 0;
    dy_move = 0;
    dz_move = 0;

    dx_rotate = 0;
    dy_rotate = 0;
    dz_rotate = 0;

    main_handler = Handler::instance();
}


double Dialog::get_dx_move() {
    return dx_move;
}


double Dialog::get_dy_move() {
    return dy_move;
}


double Dialog::get_dz_move() {
    return dz_move;
}


double Dialog::get_dx_rotate() {
    return dx_rotate;
}


double Dialog::get_dy_rotate() {
    return dy_rotate;
}


double Dialog::get_dz_rotate() {
    return dz_rotate;
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked() {
    dx_move = ui->spinBox_move_dx->text().toDouble();
    dy_move = ui->spinBox_move_dy->text().toDouble();
    dz_move = 0;//ui->spinBox_move_dz->text().toDouble();

    dx_rotate = ui->spinBox_rotate_dx->text().toDouble();
    dy_rotate = ui->spinBox_rotate_dy->text().toDouble();
    dz_rotate = ui->spinBox_rotate_dz->text().toDouble();

    main_handler->set_data_move_dialog(dx_move, dy_move, dz_move);
    main_handler->set_data_rotate_dialog(dx_rotate, dy_rotate, dz_rotate);
}
