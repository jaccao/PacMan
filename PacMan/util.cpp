#include "util.h"
#include <cmath>

double Util::abs(double v)
{
    if(v<0) return v*-1.0;
    return v;
}

int Util::topInt(double v)
{
    double r=std::fmod(v,1.0);
    if(r<0) return(((int)v)-1);
    if(r>0) return(((int)v)+1);
    return(v);
}

bool Util::isDebugTime(bool dec)
{
    static int ct=1;
    if(dec) ct--;
    if(ct<0) ct=128;
    return(!ct);
}
