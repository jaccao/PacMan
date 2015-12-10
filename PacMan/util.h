#ifndef UTIL_H
#define UTIL_H

#define PI 3.141592

#ifdef USE_QT
#include<QDebug>
#endif

class Util
{
public:
    static double abs(double v);
    static int topInt(double v);
    static bool isDebugTime(bool dec=false);
};

#endif // UTIL_H
