#include "dialog_set_wave.h"
#include "ui_dialog_set_wave.h"

dialog_set_wave::dialog_set_wave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_set_wave) {
    ui->setupUi(this);
    main_handler = Handler::instance();

    ui->spinBox_point1_x->setValue(main_handler->get_start_point().get_x());
    ui->spinBox_point1_y->setValue(main_handler->get_start_point().get_y());

    ui->spinBox_point2_x->setValue(main_handler->get_fin_point().get_x());
    ui->spinBox_point2_y->setValue(main_handler->get_fin_point().get_y());

    ui->spinBox_count->setValue(main_handler->get_count());

    ui->doubleSpinBox_dir_x->setValue(main_handler->get_direction().get_x_coord());
    ui->doubleSpinBox_dir_y->setValue(main_handler->get_direction().get_y_coord());

    ui->spinBox_amplitude->setValue(main_handler->get_amplitude());
    ui->spinBox_speed->setValue(main_handler->get_speed());
    ui->spinBox_wave_len->setValue(main_handler->get_wave_len());

    ui->doubleSpinBox_step->setValue(main_handler->get_steep());
}



dialog_set_wave::~dialog_set_wave() {
    delete ui;
}

void dialog_set_wave::on_pushButton_clicked() {

    double point1_x = ui->spinBox_point1_x->text().toDouble(), point1_y = ui->spinBox_point1_y->text().toDouble();
    double point2_x = ui->spinBox_point2_x->text().toDouble(), point2_y = ui->spinBox_point2_y->text().toDouble();
    int count = ui->spinBox_count->text().toInt();
    double amplitude = ui->spinBox_amplitude->text().toDouble();
    double len = ui->spinBox_wave_len->text().toDouble();
    double speed = ui->spinBox_speed->text().toDouble();
    double steep = ui->doubleSpinBox_step->value();
    double dir_x = ui->doubleSpinBox_dir_x->value();
    double dir_y = ui->doubleSpinBox_dir_y->value();

    main_handler->set_main_wave(Point2D(point1_x, point1_y), Point2D(point2_x, point2_y), count, MathVector2D(dir_x, dir_y), amplitude, len, speed, steep);
    main_handler->reset_wave();
}
