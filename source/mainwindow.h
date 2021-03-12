#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


#include "dialog.h"
#include "light_color_dialog.h"
#include "dialog_set_wave.h"
#include "dialog_new_waves.h"

#include "math_graphics.h"
#include "handler.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *tmr;
    double msec;

private slots:
    void update_wave();
    void get_data_dialog();
    void on_button_transform_value_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_button_transform_value_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapitem;
    QPixmap pixmap;
    Dialog *d;
    Light_Color_Dialog *lcd;
    dialog_set_wave *dsw;
    dialog_new_waves *dnw;
    shared_ptr<Handler> main_handler;
    bool is_run_timer;
    void run_timer();
    void stop_timer();
    void render_frame();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
