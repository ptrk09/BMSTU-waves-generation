#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "math_vectors_operation.h"
#include "waves.h"
#include "structurs.h"
#include "light.h"


class ZBuffer {
public:
    ZBuffer();
    void fill_scene(QImage *image);
    void start_fill(shared_ptr<GerstWave> wave, QImage *image);
    void set_polygons(shared_ptr<GerstWave> wave);
    void set_border(int width, int hieght);
    void set_color_wave(QColor new_color);
    void set_light(Light new_light);
    QColor get_color_light();
    QColor get_color_wave();
private:
    QColor color_wave;
    double *m_buffer;
    Light m_light;
    unsigned int z_buffer_size;
    int f_width, f_height;
    vector<Triangle> triangle_buffer;
    MathVector3D get_normal(const Point3D point1, const Point3D point2, const Point3D point3);
    void set_coords_points(double *const x, double *const y, double *const z, Triangle& tempSurface);
    void set_color(int * const rc, int * const gc, int * const bc, double *x, double *y, double *z_a, double *cosinus, MathVector3D l, MathVector3D norm);
    void resize_buffer(unsigned int cur_z_buffer_size);
    void restart_buffer();
};

#endif // Z_BUFFER_H
