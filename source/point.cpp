#include "point.h"


Point2D::Point2D() : x(0), y(0)
{

}

Point2D::Point2D(const double in_x, const double in_y) : x(in_x), y(in_y) {}


Point2D::Point2D(const Point2D &point) : x(point.x), y(point.y) {}


void Point2D::set_coords(const double x, const double y) {
    this->x = x;
    this->y = y;
}


double Point2D::get_x() const {
    return x;
}


double Point2D::get_y() const {
    return y;
}


std::ostream& operator<< (std::ostream &out, const Point2D &point) {
    out << "Point(" << point.x << ", " << point.y << ")";
    return out;
}


Point2D& Point2D::operator= (const Point2D &point) {
    x = point.x;
    y = point.y;
    return *this;
}


Point3D::Point3D() : Point2D(0, 0), z(0)
{
}

Point3D::Point3D(const double in_x, const double in_y, const double in_z) : Point2D(in_x, in_y), z(in_z) {}


Point3D::Point3D(const Point3D &point) : Point2D(point.get_x(), point.get_y()), z(point.z) {}


void Point3D::set_coords(const double x, const double y, const double z) {
    Point2D::set_coords(x, y);
    this->z = z;
}


double Point3D::get_z() const {
    return z;
}


std::ostream& operator<< (std::ostream &out, const Point3D &point3D) {
    out << "Point(" << point3D.get_x() << ", " << point3D.get_y() << ", " << point3D.get_z() << ")";
    return out;
}


Point3D& Point3D::operator= (const Point3D &point) {
    set_coords(point.get_x(), point.get_y(), point.get_z());
    return *this;
}
