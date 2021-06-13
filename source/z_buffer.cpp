#include "z_buffer.h"
#include "debuger.h"


ZBuffer::ZBuffer() : m_light(Light(Point3D(50, 10, -500), QColor(220, 219, 146, 255))) {
    f_width = 800; f_height = 800;
    z_buffer_size = f_width * f_height;
    m_buffer = new double[z_buffer_size];
    for(unsigned int i = 0; i < z_buffer_size; i++) {
        m_buffer[i] = -1000000;
    }

    set_color_wave(QColor(6, 190, 210, 255));
}


void ZBuffer::fill_scene(QImage *image) {
    rgba64 *bits = reinterpret_cast<rgba64 *>(image->bits());
    double xScanLine1, xScanLine2;
    double x1 = 0, x2 = 0, tc = 0, z1 = 0, z2 = 0, z = 0;
    double x[3], y[3], z_a[3];
    bool bordersFound;
    int ymax, ymin, yScanLine, e1;
    MathVector3D view = MathVector3D(0, 0, 0);
    Triangle tempSurface;
    Normal normal;

    for(unsigned int j = 0; j < triangle_buffer.size(); ++j) {
        tempSurface = triangle_buffer.at(j);
        normal = tempSurface.get_normal();
        view = MathVector3D(
            m_light.get_direction().get_x_coord() - tempSurface.get_p1().get_x(),
            m_light.get_direction().get_y_coord() - tempSurface.get_p1().get_y(),
            m_light.get_direction().get_z_coord() - tempSurface.get_p1().get_z()
        );
        set_coords_points(&x[0], &y[0], &z_a[0], tempSurface);
        ymin = std::min(std::min(y[0], y[1]),y[2]);
        ymax = std::max(std::max(y[0], y[1]),y[2]);

        MathVector3D l = m_light.get_direction();
        MathVector3D norm = normal.get_normalize();
        double cosinus[3];
        int rc[3], bc[3], gc[3];

        set_color(
            &rc[0], &gc[0], &bc[0],
            &x[0], &y[0], &z_a[0],
            &cosinus[0], l, norm
        );

        int i1 = 0, i2 = 0;
        for (yScanLine = round(ymin); yScanLine < round(ymax); yScanLine++) {
            bordersFound = false;
            for (int e = 0; e < 3; e++) {
                e1 = e + 1;
                if (e1 == 3) { e1 = 0; }

                if (y[e] < y[e1] && (y[e1] <= yScanLine || yScanLine < y[e])) {
                    continue;
                } else if (y[e] > y[e1] && (y[e1] > yScanLine || yScanLine >= y[e])) {
                    continue;
                } else if (y[e] == y[e1]) {
                    continue;
                }

                tc = (y[e] - yScanLine) / (y[e] - y[e1]);
                if (bordersFound) {
                    x2 = x[e] + ( tc * (x[e1] - x[e]));
                    z2 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                    i2 = qRgba(
                        Light::check_rgb_color((int)(rc[e] + tc*(rc[e1] - rc[e]))),
                        Light::check_rgb_color((int)(gc[e] + tc*(gc[e1] - gc[e]))),
                        Light::check_rgb_color((int)(bc[e] + tc*(bc[e1] - bc[e]))),
                        180
                    );
                } else {
                    x1 = x[e] +  (tc * (x[e1] - x[e]));
                    z1 = z_a[e] + tc * (z_a[e1] - z_a[e]);
                    i1 = qRgba(Light::check_rgb_color((int)(rc[e] + tc*(rc[e1] - rc[e]))),
                               Light::check_rgb_color((int)(gc[e] + tc*(gc[e1] - gc[e]))),
                               Light::check_rgb_color((int)(bc[e] + tc*(bc[e1] - bc[e]))),
                               180);
                    bordersFound = true;
                }
            }

            if (x2 < x1) {
                std::swap(x2, x1);
                std::swap(z2, z1);
                std::swap(i2, i1);
            }

            xScanLine1 = (x1 < -1*std::numeric_limits<float>::max()) ? -1*std::numeric_limits<float>::max() : x1;
            xScanLine2 = (x2 < f_width - 1) ? x2 : f_width - 1;
            for (int xScanLine = round(xScanLine1); xScanLine < round(xScanLine2); xScanLine++) {
                float tc = (x1 - xScanLine) / (x1 - x2);
                z = z1 + tc * (z2 - z1);


                int index = (int)round((xScanLine) +(yScanLine) * f_width);
                if (index < z_buffer_size && z > m_buffer[index]) {
                    int clr = qRgba(Light::check_rgb_color((int)(qRed(i1) + tc*(qRed(i2) - qRed(i1)))),
                                    Light::check_rgb_color((int)(qGreen(i1) + tc*(qGreen(i2) - qGreen(i1)))),
                                    Light::check_rgb_color((int)(qBlue(i1) + tc*(qBlue(i2) - qBlue(i1)))), 100);
                    QRgb l_color = qRgba(get_color_light().red(), get_color_light().green(), get_color_light().green(), get_color_light().alpha());

                    QRgb color = qRgba(qRed(clr)*0.70 + 0.30*qRed(l_color)*qAlpha(l_color)/255,
                               qGreen(clr)*0.70 + 0.30*qGreen(l_color)*qAlpha(l_color)/255,
                               qBlue(clr)*0.70 + 0.30*qBlue(l_color)*qAlpha(l_color)/255, 100);
                    m_buffer[index] = z;

                    uint16_t red_c = (qRed(color) / 255.0) * 65365;
                    uint16_t green_c = (qGreen(color) / 255.0) * 65365;
                    uint16_t blue_c = (qBlue(color) / 255.0) * 65365;

                    bits[index].red = red_c;
                    bits[index].green = green_c;
                    bits[index].blue = blue_c;
                }
            }
        }
    }
}


void ZBuffer::start_fill(shared_ptr<GerstWave> wave, QImage *image) {
    set_polygons(wave);
    restart_buffer();
    fill_scene(image);
}


void ZBuffer::set_polygons(shared_ptr<GerstWave> wave) {
    triangle_buffer.clear();
    Triangle temp;
    MathVector3D math_vector_normal(0, 0, 0);
    for (int i = 1; i < wave->get_len(); i+=2) {
        for (int j = 1; j < wave->get_len(); j+=2) {
            math_vector_normal = get_normal(wave->get_point(i, j), wave->get_point(i - 1, j - 1), wave->get_point(i + 1, j - 1));
            temp = Triangle(wave->get_point(i - 1, j - 1), wave->get_point(i + 1, j - 1), wave->get_point(i, j)); // l
            temp.set_normal(
                Normal(
                    math_vector_normal.get_x_coord(),
                    math_vector_normal.get_y_coord(),
                    math_vector_normal.get_z_coord()
                )
            );
            triangle_buffer.push_back(temp);


            math_vector_normal = get_normal(wave->get_point(i, j), wave->get_point(i + 1, j - 1), wave->get_point(i + 1, j + 1));
            temp = Triangle(wave->get_point(i + 1, j - 1), wave->get_point(i + 1, j + 1), wave->get_point(i, j)); // d
            temp.set_normal(
                Normal(
                    math_vector_normal.get_x_coord(),
                    math_vector_normal.get_y_coord(),
                    math_vector_normal.get_z_coord()
                )
            );
            triangle_buffer.push_back(temp);


            math_vector_normal = get_normal(wave->get_point(i, j), wave->get_point(i + 1, j + 1), wave->get_point(i - 1, j + 1));
            temp = Triangle(wave->get_point(i + 1, j + 1), wave->get_point(i - 1, j + 1), wave->get_point(i, j)); // r
            temp.set_normal(
                Normal(
                    math_vector_normal.get_x_coord(),
                    math_vector_normal.get_y_coord(),
                    math_vector_normal.get_z_coord()
                )
            );
            triangle_buffer.push_back(temp);

            math_vector_normal = get_normal(wave->get_point(i, j), wave->get_point(i - 1, j + 1), wave->get_point(i - 1, j - 1));
            temp = Triangle(wave->get_point(i - 1, j + 1), wave->get_point(i - 1, j - 1), wave->get_point(i, j)); // u
            temp.set_normal(
                Normal(
                    math_vector_normal.get_x_coord(),
                    math_vector_normal.get_y_coord(),
                    math_vector_normal.get_z_coord()
                )
            );
            triangle_buffer.push_back(temp);
        }
    }
}


void ZBuffer::set_border(int width, int hieght) {
    f_width = width;
    f_height = hieght;
    z_buffer_size = f_width * f_height;
    resize_buffer(z_buffer_size);
}


void ZBuffer::set_color_wave(QColor new_color) {
    color_wave.setRed(new_color.red());
    color_wave.setGreen(new_color.green());
    color_wave.setBlue(new_color.blue());
    color_wave.setAlpha(new_color.alpha());
}


void ZBuffer::set_light(Light new_light) {
    m_light = new_light;
}


QColor ZBuffer::get_color_light() {
    return m_light.get_color();
}

QColor ZBuffer::get_color_wave() {
    return color_wave;
}


MathVector3D ZBuffer::get_normal(const Point3D point1, const Point3D point2, const Point3D point3) {
    MathVector3D mv1 = MathVector3D(
        point2.get_x() - point1.get_x(),
        point2.get_y() - point1.get_y(),
        point2.get_z() - point1.get_z()
    );

    MathVector3D mv2 = MathVector3D(
        point3.get_x() - point1.get_x(),
        point3.get_y() - point1.get_y(),
        point3.get_z() - point1.get_z()
    );

     MathVector3D mv = MathVector3D::crossProduct(mv1, mv2);

     return mv;
}


void ZBuffer::set_coords_points(double * const x, double * const y, double * const z, Triangle &tempSurface) {
    x[0] = round(tempSurface.get_p1().get_x()); y[0] = round(tempSurface.get_p1().get_y()); z[0] = tempSurface.get_p1().get_z();
    x[1] = round(tempSurface.get_p2().get_x()); y[1] = round(tempSurface.get_p2().get_y()); z[1] = tempSurface.get_p2().get_z();
    x[2] = round(tempSurface.get_p3().get_x()); y[2] = round(tempSurface.get_p3().get_y()); z[2] = tempSurface.get_p3().get_z();
}


void ZBuffer::set_color(int * const rc, int * const gc, int * const bc, double *x, double *y, double *z_a, double *cosinus, MathVector3D l, MathVector3D norm) {
    QRgb color = qRgba(color_wave.red(), color_wave.green(), color_wave.blue(), 255);
    for (int i = 0; i < 3; ++i) {
        MathVector3D lt(l.get_x_coord()- x[i], l.get_y_coord() - y[i], l.get_z_coord() - z_a[i]);
        cosinus[i] = (norm.get_x_coord()*lt.get_x_coord() + norm.get_y_coord()*lt.get_y_coord() + norm.get_z_coord()*lt.get_z_coord()) /
                (norm.get_len() * lt.get_len());

        rc[i] = Light::check_rgb_color((int)(180*cosinus[i] + qRed(color)));
        gc[i] = Light::check_rgb_color((int)(180*cosinus[i] + qGreen(color)));
        bc[i] = Light::check_rgb_color((int)(180*cosinus[i] + qBlue(color)));
    }
}


void ZBuffer::resize_buffer(unsigned int cur_z_buffer_size) {
    delete[] m_buffer;
    m_buffer = new double[cur_z_buffer_size];
    for(unsigned int i = 0; i < cur_z_buffer_size; i++) {
        m_buffer[i] = -1000000;
    }
}


void ZBuffer::restart_buffer()
{
    for(unsigned int i = 0; i < z_buffer_size; i++) {
        m_buffer[i] = -1000000;
    }
}
