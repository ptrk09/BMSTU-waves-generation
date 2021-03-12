#include "debuger.h"


clock_t Debuger::begin_time = 0;
clock_t Debuger::end_time = 0;

void Debuger::start_time() {
    begin_time = clock();
}

void Debuger::print_double(double value, QString pref) {
    qDebug() << "\nDebuger print double value: " << pref << value << "\n";
}

void Debuger::print_int(int value, QString pref) {
    qDebug() << "\nDebuger print int value: " << pref << value << "\n";
}


void print_str(QString value, QString pref) {
    qDebug() << "\nDebuger print QString value: " << pref << value << "\n";
}


void Debuger::finish_time() {
    end_time = clock();
}


double Debuger::get_sec() {
    return (double)(end_time - begin_time) / CLOCKS_PER_SEC;
}


double Debuger::get_tik() {
    return (double)(end_time - begin_time);
}
