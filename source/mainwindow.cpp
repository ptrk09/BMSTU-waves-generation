#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include "waves.h"
#include "debuger.h"

#include <thread>
#include <chrono>
#include <QPen>
#include <QColor>
#include <QtCore>
#include <time.h>
#include <memory>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    dsw = new dialog_set_wave(this);
    dnw = new dialog_new_waves(this);
    dminf = new Dialog_menu_info(this);

    msec = 0;
    is_run_timer = false;

    scene = new QGraphicsScene(this);
    pixmapitem = scene->addPixmap(pixmap);
    ui->graph_view->setScene(scene);

    main_handler = Handler::instance();
    render_frame();
}


MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}


float VectorLength(MathVector3D vector) {
    return sqrt(
        vector.get_x_coord() * vector.get_x_coord() +
        vector.get_y_coord() * vector.get_y_coord() +
        vector.get_z_coord()*vector.get_z_coord()
    );
}


void MainWindow::render_frame() {
    QImage image(1280, 720, QImage::Format_RGBX64);
    QColor c(51, 51, 51);
    image.fill(c);
    main_handler->fill_scene(&image);
    pixmapitem->setPixmap(QPixmap::fromImage(image));
    ui->graph_view->update();
}


void MainWindow::get_data_dialog() {

    main_handler->set_data_move_dialog(
        d->get_dx_move(),
        d->get_dy_move(),
        d->get_dz_move()
    );

    main_handler->set_data_rotate_dialog(
        d->get_dx_rotate(),
        d->get_dy_rotate(),
        d->get_dz_rotate()
    );
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_X:
            main_handler->rotate_wave(ROTATE_OX);
            break;
        case Qt::Key_C:
            main_handler->rotate_wave(ROTATE_OY);
            break;
        case Qt::Key_D:
            main_handler->move_wave(MOVE_OX);
            break;
        case Qt::Key_S:
            main_handler->move_wave(MOVE_OY);
            break;
        case Qt::Key_Z:
            main_handler->rotate_wave(ROTATE_OZ);
            break;
    }
    render_frame();
}


void MainWindow::on_button_transform_value_clicked() {
    d = new Dialog(this);
    d->setWindowFlags(d->windowFlags() | Qt::WindowStaysOnTopHint);
    d->show();
}


void MainWindow::on_pushButton_clicked() {
    run_timer();
}


void MainWindow::update_wave() {

    msec += 0.2;
    main_handler->simulation_by_time(msec);
    render_frame();

}


void MainWindow::on_pushButton_2_clicked() {
    lcd = new Light_Color_Dialog(this);
    lcd->setWindowFlags(lcd->windowFlags() | Qt::WindowStaysOnTopHint);
    lcd->show();
}

void MainWindow::on_button_transform_value_2_clicked() {
    dsw->setWindowFlags(dsw->windowFlags() | Qt::WindowStaysOnTopHint);
    dsw->show();
}

void MainWindow::on_pushButton_3_clicked() {
    stop_timer();
}

void MainWindow::on_pushButton_4_clicked() {
    dnw->update_list_waves(main_handler->get_disc_waves());
    dnw->setWindowFlags(dnw->windowFlags() | Qt::WindowStaysOnTopHint);
    dnw->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    stop_timer();
    main_handler->reset_wave();
    render_frame();
}

void MainWindow::run_timer() {
    if (!is_run_timer) {
        is_run_timer = true;
        tmr = new QTimer();
        tmr->setInterval(40);
        connect(tmr, SIGNAL(timeout()), this, SLOT(update_wave()));
        tmr->start();
    }
}

void MainWindow::stop_timer() {
    if (is_run_timer) {
        tmr->stop();
        delete tmr;
        is_run_timer = false;
    }

}

void MainWindow::on_pushButton_7_clicked() {
    dminf->setWindowFlags(dminf->windowFlags() | Qt::WindowStaysOnTopHint);
    dminf->show();
}
