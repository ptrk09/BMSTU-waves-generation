#ifndef SURFACE_H
#define SURFACE_H

#include <vector>

#include "point.h"
#include "math_vectors_operation.h"

// typedef for matrix of points
using MatrixPoints = vector<vector<Point3D>>;


/*
Class for Surface
*/
class Surface {
private:
    MatrixPoints matrix_points;
    Point2D _start_point;
    Point2D _fin_point;
    int len = 0;

public:
    Surface(const Point2D start_point, const Point2D fin_point, const int parts_ver);
    Point3D get_point(const int index_row, const int index_column) const;
    void set_point(const int index_row, const int index_column, Point3D point);
    int get_len() const;
    double center_x, center_y, center_z;
    virtual ~Surface() = default;
protected:
    void init_matrix_point();
};

#endif // SURFACE_H
