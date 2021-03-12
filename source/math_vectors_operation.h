#ifndef MATH_VECTORS_OPERATION_H
#define MATH_VECTORS_OPERATION_H

#include "point.h"
#include <QDebug>


/*
Math vector class in 2D
*/
class MathVector2D {
private:
    // x and y coords
    double x, y;
    Point2D start_point = Point2D(0, 0);
    Point2D fin_point = Point2D(0, 0);
public:
    MathVector2D(const double coord_x, const double coord_y);
    MathVector2D(const Point2D start_point, const Point2D fin_point);
    MathVector2D(const MathVector2D &math_vect);
    double get_x_coord() const;
    double get_y_coord() const;
    void set_x_coord(const double coord_x) { x = coord_x; }
    void set_y_coord(const double coord_y) { y = coord_y; }
    virtual double get_len() const;
    friend std::ostream& operator<< (std::ostream &out, const MathVector2D &point);
    MathVector2D& operator= (const MathVector2D &vect);
    bool is_exist_start_point() const;
protected:
    bool _is_exist_start_point = false;
};

std::ostream& operator<< (std::ostream &out, const MathVector2D &vect);


/*
Math vector class in 3D
*/
class MathVector3D: public MathVector2D {
private:
    // z coords
    double z, start_z, fin_z;
public:
    MathVector3D(const double coord_x, const double coord_y, const double coord_z);
    MathVector3D(const Point3D start_point, const Point3D fin_point);
    double get_z_coord() const;
    void set_z_coord(const double coord_z) { z = coord_z; }
    virtual double get_len() const;
    static MathVector3D crossProduct(const MathVector3D v1, const MathVector3D v2);
};

double get_scal_mult(const MathVector2D vect1, const MathVector2D vect2);

class Normal: public MathVector3D {
private:
public:
    Normal();
    Normal(const double coord_x, const double coord_y, const double coord_z);
    void normalize();
    MathVector3D get_normalize();
    Normal& operator=(const Normal &point);
};


class Triangle {
private:
    Point3D p1, p2, p3;
    Normal normal;
public:
    Triangle();
    Triangle(const Point3D _p1, const Point3D _p2, const Point3D _p3);
    void set_points(const Point3D _p1, const Point3D _p2, const Point3D _p3);

    Point3D get_p1() { return p1; }
    Point3D get_p2() { return p2; }
    Point3D get_p3() { return p3; }
    Triangle &operator= (const Triangle &triangle);
    void set_normal(const Normal _normal) {
        normal.set_x_coord(_normal.get_x_coord());
        normal.set_y_coord(_normal.get_y_coord());
        normal.set_z_coord(_normal.get_z_coord());
        //qDebug() << "set normal: " << normal.get_x_coord() << " " << normal.get_y_coord() << " " << normal.get_z_coord();
    }
    Normal get_normal() {return normal;}
};

#endif // MATH_VECTORS_OPERATION_H
