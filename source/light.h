#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include "math_vectors_operation.h"
#include <QRgba64>
#include <QColor>



class Light {
public:
    Light(Point3D _position, QColor _color);

    void set_pos(Point3D _position);
    void set_color(QColor _color);
    void set_color(const int r, const int g, const int b, const int a);
    void set_direction(MathVector3D& _direction);

    Point3D get_pos();
    QColor get_color();
    MathVector3D get_direction();
    Light& operator= (const Light &light);

    static int check_rgb_color(int color);

private:
    MathVector3D direction;
    Point3D position;
    QColor color;
};

#endif // LIGHT_H
