#ifndef HANDLER_H
#define HANDLER_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include  <cstddef>


#include "handler_transform.h"
#include "transform_buffer.h"
#include "z_buffer.h"
#include "handler_waves.h"

class Handler {
public:
    static shared_ptr<Handler> instance();

    void rotate_wave(const RotateType type);
    void move_wave(const MoveType type);

    void set_data_move_dialog(const double _dx_move, const double _dy_move, const double _dz_move);
    void set_data_rotate_dialog(const double _dx_rotate, const double _dy_rotate, const double _dz_rotate);

    void fill_scene(QImage *image);
    void simulation_by_time(const double cur_time);
    void set_light(Light new_light);
    void set_wave_color(QColor new_color);
    QColor get_light_color();
    QColor get_wave_color();

    void set_main_wave(Point2D point1, Point2D point2, int count, MathVector2D direction, double amplitude_wave=0, double len_wave=0, double spped_wave=0, double steep_wave=0);

    Point2D get_start_point();
    Point2D get_fin_point();
    MathVector2D get_direction();
    double get_amplitude();
    double get_wave_len();
    double get_speed();
    int get_count();
    double get_steep();

    void append_from_dsw(double amplitude, double len_wave, double speed, MathVector2D direction, double steepnes);
    void delete_wave(int index);
    void reset_wave();
    vector<QString> get_disc_waves();

private:
    Handler();
    void set_old_position_screen();

    shared_ptr<HandlerTransform> handler_transform;
    shared_ptr<TransformBuffer> buffer;
    shared_ptr<ZBuffer> z_buffer;
    shared_ptr<HandlerWaves> handler_waves;
};


//

#endif // HANDLER_H
