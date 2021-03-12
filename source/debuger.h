#ifndef DEBUGER_H
#define DEBUGER_H

#include <iostream>
#include <string>
#include <time.h>
#include <QDebug>
#include <QString>


class Debuger
{
public:
    Debuger();
    static void start_time();
    static void finish_time();
    static double get_tik();
    static double get_sec();
    static void print_double(double value, QString pref);
    static void print_int(int value, QString pref);
    static void print_str(QString value, QString pref);
    static clock_t begin_time;
    static clock_t end_time;
private:
};




#endif // DEBUGER_H
