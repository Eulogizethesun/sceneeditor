#ifndef MATRIX_H
#define MATRIX_H

#include "pool.h"

class Vertex;
class Matrix33;

class Vector3
{
public:
    double a[3];
public:
    Vector3(double x, double y, double z);
    Vector3(Vertex *v);
    double norm() const;
    void normalize();
    Vector3 operator + (const Vector3 &that) const;
    Vector3 operator - (const Vector3 &that) const;
    Vector3 operator / (double that) const;
    double dot(const Vector3 &that) const;
    Vector3 cross(const Vector3 &that) const;
    Vector3 mul(const Matrix33 &M) const;
};

class Matrix33
{
public:
    double a[3][3];
public:
    Matrix33(double a[3][3]);
};

#endif // MATRIX_H
