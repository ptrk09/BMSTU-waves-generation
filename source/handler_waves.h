#ifndef HANDLER_WAVES_H
#define HANDLER_WAVES_H

#include "waves.h"

class HandlerWaves {
public:
    HandlerWaves(int width, int height);
    shared_ptr<GerstWave> get_main_wave();
    void set_simulation(const double cur_time);
    void append_wave(shared_ptr<GerstWave> wave);
    void set_main_wave(shared_ptr<GerstWave> wave);
    Point2D get_point_start();
    Point2D get_point_fin();
    void set_points_start_fin(Point2D point_start, Point2D point_fin);
    void set_border(int width, int hieght);
    void set_center(shared_ptr<GerstWave> wave);
    void append_from_dsw(double amplitude, double len_wave, double speed, MathVector2D direction, double steepnes);
    void delete_wave(int index);
    void clear_vector_waves();
    vector<QString> get_disc();
    void reset_main_wave();

private:
    int f_width; int f_height;
    Point2D start_point, fin_point;
    shared_ptr<GerstWave> main_wave;
    shared_ptr<GerstWave> copy_wave;
    vector<shared_ptr<GerstWave>> vector_waves;
};

#endif // HANDLER_WAVES_H
