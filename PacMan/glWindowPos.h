#ifndef GLWINDOWPOS_H
#define GLWINDOWPOS_H

void glWindowPos2s(short  x,short  y);
void glWindowPos2i(int    x,int    y);
void glWindowPos2f(float  x,float  y);
void glWindowPos2d(double x,double y);
void glWindowPos3s(short  x,short  y,short  z);
void glWindowPos3i(int    x,int    y,int    z);
void glWindowPos3f(float  x,float  y,float  z);
void glWindowPos3d(double x,double y,double z);
void glWindowPos4s(short  x,short  y,short  z,short  w);
void glWindowPos4i(int    x,int    y,int    z,int    w);
void glWindowPos4f(float  x,float  y,float  z,float  w);
void glWindowPos4d(double x,double y,double z,double w);
void glWindowPos2sv(const short  v[2]);
void glWindowPos2iv(const int    v[2]);
void glWindowPos2fv(const float  v[2]);
void glWindowPos2dv(const double v[2]);
void glWindowPos3sv(const short  v[3]);
void glWindowPos3iv(const int    v[3]);
void glWindowPos3fv(const float  v[3]);
void glWindowPos3dv(const double v[3]);
void glWindowPos4sv(const short  v[4]);
void glWindowPos4iv(const int    v[4]);
void glWindowPos4fv(const float  v[4]);
void glWindowPos4dv(const double v[4]);

#endif
