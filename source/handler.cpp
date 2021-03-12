#include "handler.h"


Handler::Handler() {
    handler_transform = shared_ptr<HandlerTransform>(new HandlerTransform());
    buffer = shared_ptr<TransformBuffer>(new TransformBuffer());
    z_buffer = shared_ptr<ZBuffer>(new ZBuffer());
    handler_waves = shared_ptr<HandlerWaves>(new HandlerWaves(1280, 720));
    z_buffer->set_border(1280, 720);
    handler_waves->set_border(1280, 720);
}


void Handler::set_old_position_screen() {
    double angle = 0, dt = 0;
    if (buffer->is_rotate_dx()) {
        angle = handler_transform->rotate_wave(handler_waves->get_main_wave(), ROTATE_OX, buffer->get_value_rotate_dx());
    }

    if (buffer->is_rotate_dy()) {
        angle = handler_transform->rotate_wave(handler_waves->get_main_wave(), ROTATE_OY, buffer->get_value_rotate_dy());
    }

    if (buffer->is_rotate_dz()) {
        angle = handler_transform->rotate_wave(handler_waves->get_main_wave(), ROTATE_OZ, buffer->get_value_rotate_dz());
    }

    if (buffer->is_move_dx()) {
        dt = handler_transform->move_wave(handler_waves->get_main_wave(), MOVE_OX, buffer->get_value_move_dx());
    }

    if (buffer->is_move_dy()) {
        dt = handler_transform->move_wave(handler_waves->get_main_wave(), MOVE_OY, buffer->get_value_move_dy());
    }
}


shared_ptr<Handler> Handler::instance() {
    static shared_ptr<Handler> myInstance(new Handler());
    return myInstance;
}


void Handler::rotate_wave(const RotateType type) {
    double angle = handler_transform->rotate_wave(handler_waves->get_main_wave(), type);
    switch (type) {
    case ROTATE_OX:
        buffer->append(BUF_ROTATE_OX, angle);
        break;
    case ROTATE_OY:
        buffer->append(BUF_ROTATE_OY, angle);
        break;
    case ROTATE_OZ:
        buffer->append(BUF_ROTATE_OZ, angle);
        break;
    }
}


void Handler::move_wave(const MoveType type) {
    double dt = handler_transform->move_wave(handler_waves->get_main_wave(), type);
    switch (type) {
    case MOVE_OX:
        buffer->append(BUF_MOVE_OX, dt);
        break;
    case MOVE_OY:
        buffer->append(BUF_MOVE_OY, dt);
        break;
    case MOVE_OZ:
        buffer->append(BUF_MOVE_OZ, dt);
        break;
    }
}


void Handler::set_data_move_dialog(const double _dx_move, const double _dy_move, const double _dz_move) {
    handler_transform->set_data_move_dialog(_dx_move, _dy_move, _dz_move);
}


void Handler::set_data_rotate_dialog(const double _dx_rotate, const double _dy_rotate, const double _dz_rotate) {
    handler_transform->set_data_rotate_dialog(_dx_rotate, _dy_rotate, _dz_rotate);
}


void Handler::fill_scene(QImage *image) {
    z_buffer->start_fill(handler_waves->get_main_wave(), image);
}


void Handler::simulation_by_time(const double cur_time) {
    handler_waves->set_simulation(cur_time);
    set_old_position_screen();
}


void Handler::set_light(Light new_light) {
    z_buffer->set_light(new_light);
}


void Handler::set_wave_color(QColor new_color) {
    z_buffer->set_color_wave(new_color);
}


QColor Handler::get_light_color() {
    return z_buffer->get_color_light();
}


QColor Handler::get_wave_color() {
    return z_buffer->get_color_wave();
}


void Handler::set_main_wave(Point2D point1, Point2D point2, int count, MathVector2D direction, double amplitude_wave, double len_wave, double spped_wave, double steep_wave) {
    shared_ptr<GerstWave> new_wave(new GerstWave(point1, point2, count));

    new_wave->set_params(amplitude_wave, len_wave, spped_wave);
    new_wave->set_steepness(steep_wave);
    new_wave->set_direction(direction);

    handler_waves->set_main_wave(new_wave);
    handler_waves->set_points_start_fin(point1, point2);
}


Point2D Handler::get_start_point() {
    return handler_waves->get_point_start();
}


Point2D Handler::get_fin_point() {
    return handler_waves->get_point_fin();
}


MathVector2D Handler::get_direction() {
    return handler_waves->get_main_wave()->get_direction();
}


double Handler::get_amplitude() {
    return handler_waves->get_main_wave()->get_amplitude();
}


double Handler::get_wave_len() {
    return handler_waves->get_main_wave()->get_wave_len();
}


double Handler::get_speed() {
    return handler_waves->get_main_wave()->get_speed();
}


int Handler::get_count() {
    return handler_waves->get_main_wave()->get_len();
}


double Handler::get_steep() {
    return handler_waves->get_main_wave()->get_steepness();
}


void Handler::append_from_dsw(double amplitude, double len_wave, double speed, MathVector2D direction, double steepnes) {
    handler_waves->append_from_dsw(amplitude, len_wave, speed, direction,  steepnes);
}


void Handler::delete_wave(int index) {
    handler_waves->delete_wave(index);
}


void Handler::reset_wave() {
    buffer->clear_buffer();
    handler_waves->clear_vector_waves();
    handler_waves->reset_main_wave();
}


vector<QString> Handler::get_disc_waves() {
    return handler_waves->get_disc();
}

