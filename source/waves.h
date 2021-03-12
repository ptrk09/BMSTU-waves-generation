#ifndef WAVES_H
#define WAVES_H


#include "surface.h"
#include <memory>


/*
Class for harmonic wave
*/
class HarmonicWave: public Surface {
private:
    // params
    double amplitude = -1, wave_len = -1, speed = -1, omega = -1, phi = -1;
    MathVector2D direction = MathVector2D(0, 0);
public:
    Point2D _start_point, _fin_point;
    HarmonicWave(const Point2D start_point, const Point2D fin_point, const int parts_ver);
    shared_ptr<HarmonicWave> copy(HarmonicWave &wave);
    void set_params(const double new_amplitude = 0, const double new_wave_len = 0, const double new_speed = 0);
    void set_direction(const MathVector2D direction);
    MathVector2D get_direction() const;
    double get_amplitude() const;
    double get_wave_len() const;
    double get_speed() const;
    double get_omega() const;
    double get_phi() const;
    // set value x, y, z for cur times in all point matrix
    virtual void set_simulation(const double cur_time);
    void setup_base_wave();
    double get_height(const Point2D point, const double cur_time) const;

protected:
    void check_params(const double amplitude, const double wave_len, const double speed) const;

};

/*
Class for Gerstner wave
*/
class GerstWave: public HarmonicWave {
private:
    double steepness = -1;
public:
    double get_offset_x(const Point3D cur_point, const double cur_time) const;
    double get_offset_y(const Point3D cur_point, const double cur_time) const;
    Point2D _start_point, _fin_point;
    GerstWave(const Point2D start_point, const Point2D fin_point, const int parts_ver);
    shared_ptr<GerstWave> copy();
    void set_steepness(const double steepness);
    double get_steepness();
    // set value x, y, z for cur times in all point matrix
    virtual void set_simulation(const double cur_time);
    QString get_string_disc();
protected:
    void check_steepness() const;
};


#endif // WAVES_H
