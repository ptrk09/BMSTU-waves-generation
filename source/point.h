#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;


/*
Class point in 2D
*/
class Point2D {
private:
    double x, y;
public:
    Point2D();
    Point2D(const double in_x, const double in_y);
    Point2D(const Point2D &point);
    void set_coords(const double x, const double y);
    double get_x() const;
    double get_y() const;
    friend std::ostream& operator<< (std::ostream &out, const Point2D &point);
    Point2D& operator= (const Point2D &point);
};

std::ostream& operator<< (std::ostream &out, const Point2D &point);


/*
Class point in 3D
*/
class Point3D: public Point2D {
private:
    double z;
public:
    Point3D();
    Point3D(const double in_x, const double in_y, const double in_z);
    Point3D(const Point3D &point);
    void set_coords(const double x, const double y, const double z);
    double get_z() const;
    friend std::ostream& operator<< (std::ostream &out, const Point3D &point3D);
    Point3D& operator= (const Point3D &point);
};

std::ostream& operator<< (std::ostream &out, const Point3D &point3D);

#endif // POINT_H
