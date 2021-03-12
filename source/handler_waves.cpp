#include "handler_waves.h"


void HandlerWaves::set_center(shared_ptr<GerstWave> wave) {
    int h_width = f_width >> 1;
    int h_height = f_height >> 1;
    for (int i = 0; i < wave->get_len() + 1; i++) {
        for (int j = 0; j < wave->get_len() + 1; j++) {
            Point3D point(wave->get_point(i, j).get_x(),
                          wave->get_point(i, j).get_y(),
                          wave->get_point(i, j).get_z() - 0);
            wave->set_point(i, j, point);
        }
    }
}

void HandlerWaves::append_from_dsw(double amplitude, double len_wave, double speed, MathVector2D direction, double steepnes) {
    shared_ptr<GerstWave> new_wave(new GerstWave(start_point, fin_point, get_main_wave()->get_len()));
    new_wave->set_params(amplitude, len_wave, speed);
    new_wave->set_direction(direction);
    new_wave->set_steepness(steepnes);
    append_wave(new_wave);
}

void HandlerWaves::delete_wave(int index) {
    vector_waves.erase(vector_waves.begin() + index);
}

void HandlerWaves::clear_vector_waves() {
    vector_waves.clear();
}

vector<QString> HandlerWaves::get_disc() {
    vector<QString> temp;
    for (int i = 0; i < vector_waves.size(); ++i) {
        temp.push_back(vector_waves[i]->get_string_disc());
    }
    return temp;
}

void HandlerWaves::reset_main_wave()
{
    copy_wave = main_wave->copy();
}




HandlerWaves::HandlerWaves(int width, int height) : f_width(width), f_height(height) {

    start_point = Point2D(0, 0);
    fin_point = Point2D(600, 600);

    main_wave = shared_ptr<GerstWave>(new GerstWave(Point2D(0, 0), Point2D(600, 600), 10));
    main_wave->set_params(30, 100, 20);
    main_wave->set_direction(MathVector2D(1, 1));
    main_wave->set_steepness(0.003);
    copy_wave = main_wave->copy();
    set_center(copy_wave);
}

shared_ptr<GerstWave> HandlerWaves::get_main_wave() {
    return copy_wave;
}

void HandlerWaves::set_simulation(const double cur_time) {
    copy_wave = main_wave->copy();
    for (int i = 0; i < copy_wave->get_len() + 1; i++) {
        for (int j = 0; j < copy_wave->get_len() + 1; j++) {
            double cur_x = copy_wave->get_point(i, j).get_x() + main_wave->get_offset_x(main_wave->get_point(i, j), cur_time);
            double cur_y = copy_wave->get_point(i, j).get_y() + main_wave->get_offset_y(main_wave->get_point(i, j), cur_time);
            double cur_z = main_wave->get_height(main_wave->get_point(i, j), cur_time);
            for (int ind = 0; ind < vector_waves.size(); ind++) {
                cur_x += vector_waves[ind]->get_offset_x(vector_waves[ind]->get_point(i, j), cur_time);
                cur_y += vector_waves[ind]->get_offset_y(vector_waves[ind]->get_point(i, j), cur_time);
                cur_z += vector_waves[ind]->get_height(vector_waves[ind]->get_point(i, j), cur_time);
            }
            copy_wave->set_point(i, j, Point3D(cur_x, cur_y, cur_z));
        }
    }
    set_center(copy_wave);
}

void HandlerWaves::append_wave(shared_ptr<GerstWave> wave) {
    vector_waves.push_back(wave);
}

void HandlerWaves::set_main_wave(shared_ptr<GerstWave> wave) {
    main_wave = wave;
    copy_wave = main_wave->copy();
    set_center(copy_wave);
}

Point2D HandlerWaves::get_point_start() {
    return start_point;
}

Point2D HandlerWaves::get_point_fin() {
    return fin_point;
}

void HandlerWaves::set_points_start_fin(Point2D point_start, Point2D point_fin) {
    start_point = point_start;
    fin_point = point_fin;
}

void HandlerWaves::set_border(int width, int hieght) {
    f_width = width;
    f_height = hieght;
}
