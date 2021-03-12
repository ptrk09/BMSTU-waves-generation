#include "surface.h"
#include <math.h>
#include "exception.h"
#include <QDebug>


Surface::Surface(const Point2D start_point, const Point2D fin_point, const int parts_ver):
                                _start_point(start_point), _fin_point(fin_point), len(parts_ver)
{
    init_matrix_point();
};


void Surface::init_matrix_point() {
    double dx = fabs(_fin_point.get_x() - _start_point.get_x()) / (len);
    double dy = fabs(_fin_point.get_y() - _start_point.get_y()) / (len);
    double start_x = _start_point.get_x(), start_y = _start_point.get_y();

    center_x = fabs(_fin_point.get_x() - _start_point.get_x()) / 2;
    center_y = fabs(_fin_point.get_y() - _start_point.get_y()) / 2;
    center_z = 0;

    for (int i = 0; i < len + 1; ++i) {
        vector<Point3D> temp_vector;
        double cur_y = start_y + dy * i;
        for (int j = 0; j < len + 1; ++j) {
            double cur_x = start_x + dx * j;
            temp_vector.push_back(Point3D(cur_x, cur_y, 0.0));
        }
        matrix_points.push_back(temp_vector);
    }
}


Point3D Surface::get_point(const int index_row, const int index_column) const {
    if (index_row < 0 || index_row > len + 1 || index_column < 0 || index_column > len + 1) {
        throw IndexException("Invalid index in Surface::get_point");
    }
    return matrix_points[index_row][index_column];
}


void Surface::set_point(const int index_row, const int index_column, Point3D point) {
    if (index_row < 0 || index_row > len + 1 || index_column < 0 || index_column > len + 1) {
        throw IndexException("Invalid index in Surface::set_point");
    }
    matrix_points[index_row][index_column] = point;
}


int Surface::get_len() const {
    return len;
}
