#include "math_vectors_operation.h"

#include <math.h>
#include <QDebug>


double get_vector_len(MathVector3D vector) {
    return sqrt(
        vector.get_x_coord() * vector.get_x_coord() +
        vector.get_y_coord() * vector.get_y_coord() +
        vector.get_z_coord()*vector.get_z_coord()
    );
}


MathVector2D::MathVector2D(const double coord_x, const double coord_y): x(coord_x), y(coord_y), _is_exist_start_point(false) {}


MathVector2D::MathVector2D(const Point2D start_point, const Point2D fin_point) {
    this->start_point = start_point;
    this->fin_point = fin_point;
    _is_exist_start_point = true;
    x = fin_point.get_x() - start_point.get_x();
    y = fin_point.get_y() - start_point.get_y();
}


MathVector2D::MathVector2D(const MathVector2D &math_vect) : x(math_vect.x), y(math_vect.y) {}


double MathVector2D::get_len() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}


bool MathVector2D::is_exist_start_point() const {
    return _is_exist_start_point;
}


double MathVector2D::get_x_coord() const {
    return x;
}


double MathVector2D::get_y_coord() const {
    return y;
}


double get_scal_mult(const MathVector2D vect1, const MathVector2D vect2) {
    return (
        vect1.get_x_coord() * vect2.get_x_coord() +
        vect1.get_y_coord() * vect2.get_y_coord()
    );
}


std::ostream& operator<< (std::ostream &out, const MathVector2D &vect) {
    out << "MathVector2D(x: " << vect.x << ", y: " << vect.y;
    if (vect._is_exist_start_point) {
        out << ", 1st_point: " << vect.start_point << ", 2nd_point: " << vect.fin_point;
    }
    out << ")";

    return out;
}


MathVector2D& MathVector2D::operator= (const MathVector2D &vect) {
    x = vect.x;
    y = vect.y;
    _is_exist_start_point = vect._is_exist_start_point;
    start_point = vect.start_point;
    fin_point = vect.fin_point;
    return *this;
}


MathVector3D::MathVector3D(const double coord_x, const double coord_y, const double coord_z): MathVector2D(coord_x, coord_y), z(coord_z) {}


MathVector3D::MathVector3D(const Point3D start_point, const Point3D fin_point):
            MathVector2D(Point2D(start_point.get_x(), start_point.get_y()), Point2D(fin_point.get_x(), fin_point.get_y())) {
    start_z = start_point.get_z();
    fin_z = fin_point.get_z();
    z = fin_point.get_z() - start_point.get_z();
}


double MathVector3D::get_z_coord() const {
    return z;
}


double MathVector3D::get_len() const {
    return sqrt(pow(get_x_coord(), 2) + pow(get_y_coord(), 2) + pow(z, 2));
}


MathVector3D MathVector3D::crossProduct(const MathVector3D v1, const MathVector3D v2) {
    return MathVector3D(v1.get_y_coord() * v2.get_z_coord() - v1.get_z_coord() * v2.get_y_coord(),
                     v1.get_z_coord() * v2.get_x_coord() - v1.get_x_coord() * v2.get_z_coord(),
                     v1.get_x_coord() * v2.get_y_coord() - v1.get_y_coord() * v2.get_x_coord());
}


Normal::Normal() : MathVector3D(0, 0, 0) {}


Normal::Normal(const double coord_x, const double coord_y, const double coord_z) : MathVector3D(coord_x, coord_y, coord_z) {}


void Normal::normalize() {
    double inv_length = 1.0 / sqrt(get_x_coord() * get_x_coord() + get_y_coord() * get_y_coord() + get_z_coord() * get_z_coord());
    set_x_coord(get_x_coord() * inv_length);
    set_y_coord(get_y_coord() * inv_length);
    set_z_coord(get_z_coord() * inv_length);
}


MathVector3D Normal::get_normalize()
{
    double inv_length = 1.0 / sqrt(get_x_coord() * get_x_coord() + get_y_coord() * get_y_coord() + get_z_coord() * get_z_coord());
    MathVector3D m(0, 0, 0);
    m.set_x_coord(get_x_coord() * inv_length);
    m.set_y_coord(get_y_coord() * inv_length);
    m.set_z_coord(get_z_coord() * inv_length);
    return m;
}


Normal &Normal::operator=(const Normal &point)
{
    set_x_coord(point.get_x_coord());
    set_y_coord(point.get_y_coord());
    set_z_coord(point.get_z_coord());
    return *this;
}


Triangle &Triangle::operator=(const Triangle &triangle) {
    p1 = triangle.p1;
    p2 = triangle.p2;
    p3 = triangle.p3;
    normal = triangle.normal;
    return *this;
}


Triangle::Triangle() : p1(Point3D(0, 0, 0)), p2(Point3D(0, 0, 0)), p3(Point3D(0, 0, 0)) {}


Triangle::Triangle(const Point3D _p1, const Point3D _p2, const Point3D _p3) : p1(_p1), p2(_p2), p3(_p3) {}


void Triangle::set_points(const Point3D _p1, const Point3D _p2, const Point3D _p3)
{
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
}
