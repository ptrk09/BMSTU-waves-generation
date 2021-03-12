#include "handler_transform.h"


HandlerTransform::HandlerTransform() {
    dx_move = 5; dy_move = 5; dz_move = 5;
    dx_rotate = 5; dy_rotate = 5; dz_rotate = 5;
}


double HandlerTransform::rotate_wave(shared_ptr<GerstWave> wave, const RotateType type, const double alpha) {
    double angle = 0;
    switch (type) {
    case ROTATE_OX:
        angle = get_need_value(alpha, dx_rotate * M_PI / 180);
        rotate_dx(wave, angle);
        break;
    case ROTATE_OY:
        angle = get_need_value(alpha, dy_rotate * M_PI / 180);
        rotate_dy(wave, angle);
        break;
    case ROTATE_OZ:
        angle = get_need_value(alpha, dz_rotate * M_PI / 180);
        rotate_dz(wave, angle);
        break;
    }

    return angle;
}


double HandlerTransform::move_wave(shared_ptr<GerstWave> wave, const MoveType type, const double dt) {
    double d = 0;
    switch (type) {
    case MOVE_OX:
        d = get_need_value(dt, dx_move);
        move_dx(wave, d);
        break;
    case MOVE_OY:
        d = get_need_value(dt, dy_move);
        move_dy(wave, d);
        break;
    case MOVE_OZ:
        d = get_need_value(dt, dz_move);
        move_dz(wave, d);
        break;
    }

    return d;
}


void HandlerTransform::set_data_move_dialog(const double _dx_move, const double _dy_move, const double _dz_move) {
    dx_move = _dx_move;
    dy_move = _dy_move;
    dz_move = _dz_move;
}


void HandlerTransform::set_data_rotate_dialog(const double _dx_rotate, const double _dy_rotate, const double _dz_rotate) {
    dx_rotate = _dx_rotate;
    dy_rotate = _dy_rotate;
    dz_rotate = _dz_rotate;
}


double HandlerTransform::get_need_value(const double new_param, const double std_param) {
    if (new_param) {
        return new_param;
    }

    return std_param;
}


void HandlerTransform::rotate_dx(shared_ptr<GerstWave> wave, const double angle) {
    double offset_x = get_offset_x(wave), offset_y = get_offset_y(wave);

    vector<vector<double>> transfer_matrix {
        {1, 0, 0, 0},
        {0, cos(angle), -sin(angle), 0},
        {0, sin(angle), cos(angle), 0},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            vector<vector<double>> coords{
                {
                    wave->get_point(i, j).get_x() - offset_x,
                    wave->get_point(i, j).get_y() - offset_y,
                    wave->get_point(i, j).get_z(),
                    1
                }
            };
            wave->set_point(i, j, mult_matr(coords, transfer_matrix, offset_x, offset_y));
        }
    }
}


void HandlerTransform::rotate_dy(shared_ptr<GerstWave> wave, const double angle) {
    double offset_x = get_offset_x(wave), offset_y = get_offset_y(wave);

    vector<vector<double>> transfer_matrix {
        {cos(-angle), 0, -sin(-angle), 0},
        {0, 1, 0, 0},
        {sin(-angle), 0, cos(-angle), 0},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            vector<vector<double>> coords{
                {
                    wave->get_point(i, j).get_x() - offset_x,
                    wave->get_point(i, j).get_y() - offset_y,
                    wave->get_point(i, j).get_z(),
                    1
                }
            };
            wave->set_point(i, j, mult_matr(coords, transfer_matrix, offset_x, offset_y));
        }
    }
}


void HandlerTransform::rotate_dz(shared_ptr<GerstWave> wave, const double angle) {
    double offset_x = get_offset_x(wave), offset_y = get_offset_y(wave);

    vector<vector<double>> transfer_matrix {
        {cos(angle), -sin(angle), 0, 0},
        {sin(angle), cos(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            vector<vector<double>> coords{
                {
                    wave->get_point(i, j).get_x() - offset_x,
                    wave->get_point(i, j).get_y() - offset_y,
                    wave->get_point(i, j).get_z(),
                    1
                }
            };
            wave->set_point(i, j, mult_matr(coords, transfer_matrix, offset_x, offset_y));
        }
    }
}


void HandlerTransform::move_dx(shared_ptr<GerstWave> wave, const double dx) {
    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            Point3D new_point(wave->get_point(i, j).get_x() + dx,
                              wave->get_point(i, j).get_y(),
                              wave->get_point(i, j).get_z());
            wave->set_point(i, j, new_point);
        }
    }
}


void HandlerTransform::move_dy(shared_ptr<GerstWave> wave, const double dy) {
    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            Point3D new_point(wave->get_point(i, j).get_x(),
                              wave->get_point(i, j).get_y() + dy,
                              wave->get_point(i, j).get_z());
            wave->set_point(i, j, new_point);
        }
    }
}


void HandlerTransform::move_dz(shared_ptr<GerstWave> wave, const double dz) {
}


Point3D HandlerTransform::mult_matr(vector<vector<double> > coords, vector<vector<double> > transfer_matrix, double offset_x, double offset_y)
{
    vector<vector<double>> coords_point{{0, 0, 0, 0}};

    for(int i = 0; i < coords.size(); i++) {
        for(int j = 0; j < transfer_matrix[0].size(); j++)
        {
            coords_point[i][j] = 0;
            for(int k = 0; k < transfer_matrix.size(); k++)
                coords_point[i][j] += coords[i][k] * transfer_matrix[k][j];
        }
    }

    return Point3D(coords_point[0][0] + offset_x, coords_point[0][1] + offset_y, coords_point[0][2]);
}


double HandlerTransform::get_offset_x(shared_ptr<GerstWave> wave) {
    double max_x = -100000, min_x = 10000000;
    double temp = 0;

    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            temp = wave->get_point(i, j).get_x();
            if (temp > max_x) {
                max_x = temp;
            }
            if (temp < min_x) {
                min_x = temp;
            }
        }
    }

    return min_x + ((max_x - min_x) / 2);
}


double HandlerTransform::get_offset_y(shared_ptr<GerstWave> wave) {
    double max_y = -100000, min_y = 10000000;
    double temp = 0;

    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            temp = wave->get_point(i, j).get_y();
            if (temp > max_y) {
                max_y = temp;
            }
            if (temp < min_y) {
                min_y = temp;
            }
        }
    }

    return min_y + ((max_y - min_y) / 2);
}
