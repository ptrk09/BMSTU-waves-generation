#ifndef DIALOG_SET_WAVE_H
#define DIALOG_SET_WAVE_H

#include <QDialog>
#include "handler.h"
#include <QMessageBox>

namespace Ui {
class dialog_set_wave;
}

class dialog_set_wave : public QDialog {
    Q_OBJECT

public:
    explicit dialog_set_wave(QWidget *parent = nullptr);
    ~dialog_set_wave();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialog_set_wave *ui;
    shared_ptr<Handler> main_handler;
    bool check_steep(double steep, double amplitude, double omega);
};

#endif // DIALOG_SET_WAVE_H
