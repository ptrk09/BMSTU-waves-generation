#include "light.h"

Light::Light(Point3D _position, QColor _color) :
                                                 direction(MathVector3D(
                                                               0 - _position.get_x(),
                                                               0 - _position.get_y(),
                                                               0 - _position.get_z()
                                                           )), position(_position),  color(_color){}

void Light::set_pos(Point3D _position) {
    position = _position;
}

void Light::set_color(QColor _color) {
    color = _color;
}

void Light::set_color(const int r, const int g, const int b, const int a) {
    int new_r = check_rgb_color(r), new_g = check_rgb_color(g), new_b = check_rgb_color(b), new_a = check_rgb_color(a);
    color = QColor(new_r, new_g, new_b, new_a);
}

void Light::set_direction(MathVector3D& _direction) {
    direction = _direction;
}

Point3D Light::get_pos() {
    return position;
}

QColor Light::get_color() {
    return color;
}

MathVector3D Light::get_direction() {
    return direction;
}


Light& Light::operator= (const Light &light) {
    this->direction = light.direction;
    this->color = light.color;
    this->position = light.position;
    return *this;
}


int Light::check_rgb_color(int color)
{
    if (color < 0)
        return 0;
    if (color > 255)
        return 255;
    return color;
}
