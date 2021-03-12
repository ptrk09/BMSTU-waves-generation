#ifndef HANDLER_TRANSFORM_H
#define HANDLER_TRANSFORM_H

#include <memory>

#include "waves.h"

using namespace std;

enum RotateType {
    ROTATE_OX,
    ROTATE_OY,
    ROTATE_OZ
};

enum MoveType {
    MOVE_OX,
    MOVE_OY,
    MOVE_OZ
};

class HandlerTransform {
public:
    HandlerTransform();
    double rotate_wave(shared_ptr<GerstWave> wave, const RotateType type, const double alpha=0);
    double move_wave(shared_ptr<GerstWave> wave, const MoveType type, const double dt=0);
    void set_data_move_dialog(const double _dx_move, const double _dy_move, const double _dz_move);
    void set_data_rotate_dialog(const double _dx_rotate, const double _dy_rotate, const double _dz_rotate);

private:
    double dx_move, dy_move, dz_move;
    double dx_rotate, dy_rotate, dz_rotate;
    double get_need_value(const double new_param, const double std_param);
    double get_radians(int degree);
    void rotate_dx(shared_ptr<GerstWave> wave, const double angle);
    void rotate_dy(shared_ptr<GerstWave> wave, const double angle);
    void rotate_dz(shared_ptr<GerstWave> wave, const double angle);
    void move_dx(shared_ptr<GerstWave> wave, const double dx);
    void move_dy(shared_ptr<GerstWave> wave, const double dy);
    void move_dz(shared_ptr<GerstWave> wave, const double dz);
    Point3D mult_matr(vector<vector<double>> coords, vector<vector<double>> transfer_matrix, double offset_x, double offset_y);
    double get_offset_x(shared_ptr<GerstWave> wave);
    double get_offset_y(shared_ptr<GerstWave> wave);

private slots:
    void get_data_dialog();
};

#endif // HANDLER_TRANSFORM_H
