#include "waves.h"
#include "exception.h"
#include "math_vectors_operation.h"
#include <math.h>
#include <QDebug>

#ifdef _DEBUG_
    void print_data_HarmonicWave(HarmonicWave test_wave) {
        cout << "debug print: " << endl << endl;
        for (size_t i = 0; i < test_wave.get_len(); ++i) {
            for (size_t j = 0; j < test_wave.get_len(); ++j) {
                cout << test_wave.get_point(i, j) << " ";
            }
            cout << endl;
        }
    }
#endif


HarmonicWave::HarmonicWave(const Point2D start_point, const Point2D fin_point, const int parts_ver): Surface(start_point, fin_point, parts_ver), _start_point(start_point), _fin_point(fin_point) {
}


shared_ptr<HarmonicWave> HarmonicWave::copy(HarmonicWave &wave)
{
    shared_ptr<HarmonicWave> new_wave(new HarmonicWave(wave._start_point, wave._fin_point, wave.get_len()));
    return new_wave;
}


void HarmonicWave::check_params(const double amplitude, const double wave_len, const double speed) const {
    if (amplitude < 0 || wave_len < 0 || speed < 0) {
        throw NegativeValueException("All params(amplitude, wave_len, speed) must not be less than 0");
    }
}


void HarmonicWave::set_params(const double new_amplitude, const double new_wave_len, const double new_speed) {
    check_params(new_amplitude, new_wave_len, new_speed);

    amplitude = new_amplitude;
    wave_len = new_wave_len;
    speed = new_speed;

    omega = 2 / wave_len;
    phi = speed * (2 / wave_len);
}


void HarmonicWave::set_direction(const MathVector2D direction) {
    this->direction = direction;
}


double HarmonicWave::get_height(const Point2D cur_point, const double cur_time) const {
    check_params(amplitude, wave_len, speed);

    MathVector2D position(cur_point.get_x(), cur_point.get_y());
    double rez = amplitude * sin(get_scal_mult(direction, position) * omega + cur_time * phi);
    return rez;
}




void HarmonicWave::set_simulation(const double cur_time) {
    check_params(amplitude, wave_len, speed);

    for (int i = 0; i < get_len(); ++i) {
        for (int j = 0; j < get_len(); ++j) {
            double cur_x = get_point(i, j).get_x();
            double cur_y = get_point(i, j).get_y();
            double cur_z = get_height(get_point(i, j), cur_time);
            set_point(i, j, Point3D(cur_x, cur_y, cur_z));
        }
    }
}


void HarmonicWave::setup_base_wave() {
    init_matrix_point();
}


double HarmonicWave::get_amplitude() const {
    return amplitude;
}


double HarmonicWave::get_wave_len() const {
    return wave_len;
}


double HarmonicWave::get_speed() const {
    return speed;
}


double HarmonicWave::get_omega() const {
    return omega;
}


double HarmonicWave::get_phi() const {
    return phi;
}


MathVector2D HarmonicWave::get_direction() const {
    return direction;
}


GerstWave::GerstWave(const Point2D start_point, const Point2D fin_point, const int parts_ver): HarmonicWave(start_point, fin_point, parts_ver), _start_point(start_point), _fin_point(fin_point) {

}


shared_ptr<GerstWave> GerstWave::copy()
{
    shared_ptr<GerstWave> new_wave(new GerstWave(this->_start_point, this->_fin_point, this->get_len()));
    new_wave->set_params(this->get_amplitude(), this->get_wave_len(), this->get_speed());
    new_wave->set_steepness(this->get_steepness());
    new_wave->set_direction(this->get_direction());
    for (int i = 0; i < new_wave->get_len() + 1; i++) {
        for (int j = 0; j < new_wave->get_len() + 1; j++) {
            new_wave->set_point(i, j, this->get_point(i, j));
        }
    }
    return new_wave;
}


void GerstWave::set_steepness(const double steepness) {
    this->steepness = steepness;
    check_steepness();
}

double GerstWave::get_steepness() {
    return steepness;
}


void GerstWave::check_steepness() const {
    if (steepness < 0 || steepness > 1 / (get_amplitude() * get_omega())) {
        throw OutOfRangeException("Steepness must be in [0; 1/(omega * amplitude)");
    }
}


double GerstWave::get_offset_x(const Point3D cur_point, const double cur_time) const {
    MathVector2D position(cur_point.get_x(), cur_point.get_y());
    return steepness * get_amplitude() * get_direction().get_x_coord()
            * cos(get_omega() * get_scal_mult(get_direction(), position) +
            get_phi() * cur_time);
}


double GerstWave::get_offset_y(const Point3D cur_point, const double cur_time) const {
    MathVector2D position(cur_point.get_x(), cur_point.get_y());
    return steepness * get_amplitude() * get_direction().get_y_coord()
            * cos(get_omega() * get_scal_mult(get_direction(), position) +
            get_phi() * cur_time);
}


void GerstWave::set_simulation(const double cur_time) {
    check_steepness();
    check_params(get_amplitude(), get_wave_len(), get_speed());

    for (int i = 0; i < get_len() + 1; ++i) {
        for (int j = 0; j < get_len() + 1; ++j) {
            double cur_x = get_point(i, j).get_x() + get_offset_x(get_point(i, j), cur_time);
            double cur_y = get_point(i, j).get_y() + get_offset_y(get_point(i, j), cur_time);
            double cur_z = get_height(get_point(i, j), cur_time);
            set_point(i, j, Point3D(cur_x, cur_y, cur_z));
        }
    }
}

QString GerstWave::get_string_disc() {
    QString valueAsString = "ampl:" + QString::number(get_amplitude()) +
            " len wave:" + QString::number(get_wave_len()) + " speed wave:" + QString::number(get_speed())
            + " dir x:" + QString::number(get_direction().get_x_coord(),'f', 2) + " dir y:" + QString::number(get_direction().get_y_coord(),'f', 2)
            + " steep:" + QString::number(get_steepness(),'f', 6);
    return valueAsString;
}
