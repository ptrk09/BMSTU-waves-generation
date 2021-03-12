#include "transform_buffer.h"

TransformBuffer::TransformBuffer() {
    clear_buffer();
}

void TransformBuffer::append(BufType type, double value) {
    switch (type) {
    case BUF_MOVE_OX:
        _is_move_dx = true;
        value_move_dx += value;
        break;
    case BUF_MOVE_OY:
        _is_move_dy = true;
        value_move_dy += value;
        break;
    case BUF_ROTATE_OX:
        _is_rotate_dx = true;
        value_rotate_dx += value;
        break;
    case BUF_ROTATE_OY:
        _is_rotate_dy = true;
        value_rotate_dy += value;
        break;
    case BUF_ROTATE_OZ:
        _is_rotate_dz = true;
        value_rotate_dz += value;
        break;
    }
}

void TransformBuffer::clear_buffer() {
    value_rotate_dx = 0; value_rotate_dy = 0, value_rotate_dz = 0;
    value_move_dx = 0, value_move_dy = 0;
    _is_move_dx = false;
    _is_move_dy = false;
    _is_rotate_dx = false;
    _is_rotate_dy = false;
    _is_rotate_dz = false;
}

bool TransformBuffer::is_rotate_dx() {
    return _is_rotate_dx;
}

bool TransformBuffer::is_rotate_dy() {
    return _is_rotate_dy;
}

bool TransformBuffer::is_rotate_dz() {
    return _is_rotate_dz;
}

bool TransformBuffer::is_move_dx() {
    return _is_move_dx;
}

bool TransformBuffer::is_move_dy() {
    return _is_move_dy;
}

double TransformBuffer::get_value_rotate_dx() {
    return value_rotate_dx;
}

double TransformBuffer::get_value_rotate_dy() {
    return value_rotate_dy;
}

double TransformBuffer::get_value_rotate_dz() {
    return value_rotate_dz;
}

double TransformBuffer::get_value_move_dx() {
    return value_move_dx;
}

double TransformBuffer::get_value_move_dy() {
    return value_move_dy;
}
