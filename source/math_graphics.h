#ifndef MATH_GRAPHICS_H
#define MATH_GRAPHICS_H

#include "waves.h"
#include "exception.h"

using MatrixPoints2D = vector<vector<Point2D>>;

class ProjectionWave {
private:
    MatrixPoints2D matrix_points2D;
    int len = 0;
    void copy_matrix_wave(const GerstWave &wave);
public:
    ProjectionWave(GerstWave &wave);
    Point2D get_point(const int index_row, const int index_column) const;
    void set_point(const int index_row, const int index_column, Point2D point);
    int get_len() const;
};

#endif // MATH_GRAPHICS_H
