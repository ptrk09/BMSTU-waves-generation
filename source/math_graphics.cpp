#include "math_graphics.h"
#include <QDebug>

ProjectionWave::ProjectionWave(GerstWave &wave) {
    this->len = wave.get_len();
    copy_matrix_wave(wave);
}


void ProjectionWave::copy_matrix_wave(const GerstWave &wave) {
    for (int i = 0; i < len + 1; ++i) {
        vector<Point2D> temp_vect;
        for (int j = 0; j < len + 1; ++j) {
            Point2D temp_point(0, 0);
            temp_point.set_coords(wave.get_point(i, j).get_x() + wave.center_x, wave.get_point(i, j).get_y() + wave.center_x);
            //qDebug() << "point proj: " << temp_point.get_x() << " " << temp_point.get_y() << "\n";
            temp_vect.push_back(temp_point);
        }
        matrix_points2D.push_back(temp_vect);
    }
    qDebug() << "----------------------------------------------\n";
}


Point2D ProjectionWave::get_point(const int index_row, const int index_column) const {
    if (index_row < 0 || index_row > len + 1 || index_column < 0 || index_column > len + 1) {
        throw IndexException("Invalid index in Surface::get_point");
    }
    return matrix_points2D[index_row][index_column];
}


void ProjectionWave::set_point(const int index_row, const int index_column, Point2D point) {
    if (index_row < 0 || index_row > len + 1 || index_column < 0 || index_column > len + 1) {
        throw IndexException("Invalid index in Surface::set_point");
    }
    matrix_points2D[index_row][index_column] = point;
}


int ProjectionWave::get_len() const {
    return len;
}
