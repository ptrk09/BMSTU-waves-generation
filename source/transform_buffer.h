#ifndef TRANSFORM_BUFFER_H
#define TRANSFORM_BUFFER_H

#include <vector>
#include <iostream>
#include <QDebug>

using namespace std;

enum BufType {
    BUF_ROTATE_OX,
    BUF_ROTATE_OY,
    BUF_ROTATE_OZ,
    BUF_MOVE_OX,
    BUF_MOVE_OY,
    BUF_MOVE_OZ
};


class TransformBuffer {
public:
    TransformBuffer();
    void append(BufType type, double value);
    int get_count() const;

    void clear_buffer();

    bool is_rotate_dx();
    bool is_rotate_dy();
    bool is_rotate_dz();
    bool is_move_dx();
    bool is_move_dy();

    double get_value_rotate_dx();
    double get_value_rotate_dy();
    double get_value_rotate_dz();
    double get_value_move_dx();
    double get_value_move_dy();

private:
    bool _is_move_dx, _is_move_dy;
    bool _is_rotate_dx, _is_rotate_dy, _is_rotate_dz;
    double value_rotate_dx, value_rotate_dy, value_rotate_dz;
    double value_move_dx, value_move_dy;
    vector<pair<BufType, double>> buffer;
};

#endif // TRANSFORM_BUFFER_H
