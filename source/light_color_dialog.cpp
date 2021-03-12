#include "light_color_dialog.h"
#include "ui_light_color_dialog.h"

Light_Color_Dialog::Light_Color_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Light_Color_Dialog) {
    ui->setupUi(this);
    main_handler = Handler::instance();
    scene = new QGraphicsScene(0, 0, 300, 230, this);
    init_defolt_view();
}


Light_Color_Dialog::~Light_Color_Dialog() {
    delete ui;
}


void Light_Color_Dialog::set_color_light(QColor new_color_light) {
    color_light = new_color_light;
}


void Light_Color_Dialog::set_color_wave(QColor new_color_wave) {
    color_wave = new_color_wave;
}


void Light_Color_Dialog::on_pushButton_clicked() {
    get_color_light();
}


void Light_Color_Dialog::update_color_light_view() {
    QPolygonF poly;
    poly << QPointF(200, 25) << QPointF(200, 95) << QPointF(270, 95)<< QPointF(270, 25);
    QBrush brush(color_light);
    QPen pen(color_light);
    scene->addPolygon(poly, pen, brush);
}


void Light_Color_Dialog::update_color_wave_view()
{
    QPolygonF poly;
    poly << QPointF(200, 125) << QPointF(200, 195) << QPointF(270, 195)<< QPointF(270, 125);
    QBrush brush(color_wave);
    QPen pen(color_wave);
    scene->addPolygon(poly, pen, brush);
}


void Light_Color_Dialog::on_pushButton_2_clicked() {
    get_color_wave();
}


void Light_Color_Dialog::on_pushButton_3_clicked()
{
    double temp_x = ui->spinBox->text().toDouble();
    double temp_y = ui->spinBox_2->text().toDouble();
    double temp_z = ui->spinBox_3->text().toDouble();
    main_handler->set_light(Light(Point3D(temp_x, temp_y, temp_z), color_light));
    main_handler->set_wave_color(color_wave);
}

void Light_Color_Dialog::get_color_light() {
    color_light = QColorDialog::getColor(color1, parentWidget());
    update_color_light_view();
    update_color_wave_view();
    ui->graphicsView->setScene(scene);
}


void Light_Color_Dialog::get_color_wave() {
    color_wave = QColorDialog::getColor(color1, parentWidget());
    update_color_light_view();
    update_color_wave_view();
    ui->graphicsView->setScene(scene);
}



void Light_Color_Dialog::init_defolt_view() {
    color_light = main_handler->get_light_color();
    update_color_light_view();
    color_wave = main_handler->get_wave_color();
    update_color_wave_view();
    ui->graphicsView->setScene(scene);
}
