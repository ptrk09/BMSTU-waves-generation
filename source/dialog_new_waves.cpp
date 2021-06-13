#include "dialog_new_waves.h"
#include "ui_dialog_new_waves.h"

dialog_new_waves::dialog_new_waves(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_new_waves) {
    ui->setupUi(this);
    main_handler = Handler::instance();
}

dialog_new_waves::~dialog_new_waves() {
    delete ui;
}

void dialog_new_waves::on_pushButton_clicked() {
    double speed = ui->spinBox_wave_speed->text().toDouble();
    double amplitude = ui->spinBox_amplitude->text().toDouble();
    double len = ui->spinBox_len_wave->text().toDouble();

    double steep = ui->doubleSpinBox_steep->value();
    double dir_x = ui->doubleSpinBox_dir_x->value();
    double dir_y = ui->doubleSpinBox_dir_y->value();

    QString valueAsString = "ampl:" + QString::number(amplitude) +
            " len wave:" + QString::number(len) + " speed wave:" + QString::number(speed)
            + " dir x:" + QString::number(dir_x,'f', 2) + " dir y:" + QString::number(dir_y,'f', 2)
            + " steep:" + QString::number(steep,'f', 6);

    double omega = 2 / len;
    if (check_steep(steep, amplitude, omega)) {
        QString valueAsString = QString::number(1 / (amplitude * omega));
        QMessageBox::warning(this, "Внимание","Кривизна должна быть в диапозоне: \n(0; " + valueAsString + ")");
        return;
    }

    ui->listWidget->addItem(valueAsString);
    main_handler->append_from_dsw(amplitude, len, speed, MathVector2D(dir_x, dir_y), steep);
}

void dialog_new_waves::on_pushButton_2_clicked() {
    delete_wave();
}

void dialog_new_waves::delete_wave() {
    if (ui->listWidget->currentIndex().row() != -1) {
        main_handler->delete_wave(ui->listWidget->currentIndex().row());
        ui->listWidget->takeItem(ui->listWidget->currentIndex().row());
    }
}

void dialog_new_waves::update_list_waves(vector<QString> disc) {
    ui->listWidget->clear();
    for (int i = 0; i < disc.size(); i++) {
        ui->listWidget->addItem(disc[i]);
    }

}

bool dialog_new_waves::check_steep(double steep, double amplitude, double omega) {
    if (steep < 0 || steep > 1 / (amplitude * omega)) {
        return true;
    }
    return false;
}
