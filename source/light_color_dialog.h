#ifndef LIGHT_COLOR_DIALOG_H
#define LIGHT_COLOR_DIALOG_H

#include <QDialog>
#include <QPen>
#include <QPainter>
#include <QGraphicsScene>
#include <handler.h>
#include <QColorDialog>

namespace Ui {
class Light_Color_Dialog;
}

class Light_Color_Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Light_Color_Dialog(QWidget *parent = nullptr);
    ~Light_Color_Dialog();
    void set_color_light(QColor new_color_light);
    void set_color_wave(QColor new_color_wave);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void get_color_wave();
    void get_color_light();
    void init_defolt_view();
    void update_color_light_view();
    void update_color_wave_view();
    QColor color1;
    shared_ptr<Handler> main_handler;
    QGraphicsScene *scene;
    QPainter painter;
    QColor color_wave, color_light;
    Ui::Light_Color_Dialog *ui;
};

#endif // LIGHT_COLOR_DIALOG_H
