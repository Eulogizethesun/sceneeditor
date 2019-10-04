#include "matrix.h"
#include "pool.h"
#include <cmath>

Vector3::Vector3(double x, double y, double z)
{
    a[0] = x; a[1] = y; a[2] = z;
}
Vector3::Vector3(Vertex *v)
{
    for(int i = 0; i < 3; ++i) {
        a[i] = v->a[i];
    }
}
double Vector3::norm() const
{
    return sqrt(this->dot(*this));
}
void Vector3::normalize()
{
    double n = this->norm();
    if(fabs(n) < 1e-9) return;
    for(int i = 0; i < 3; ++i) {
        a[i] /= n;
    }
}
Vector3 Vector3::operator + (const Vector3 &that) const
{
    return Vector3(a[0] + that.a[0],
                   a[1] + that.a[1],
                   a[2] + that.a[2]);
}
Vector3 Vector3::operator - (const Vector3 &that) const
{
    return Vector3(a[0] - that.a[0],
                   a[1] - that.a[1],
                   a[2] - that.a[2]);
}
Vector3 Vector3::operator / (double that) const
{
    return Vector3(a[0] / that,
                   a[1] / that,
                   a[2] / that);
}
double Vector3::dot(const Vector3 &that) const
{
    double sum = 0;
    for(int i = 0; i < 3; ++i) {
        sum += a[i] * that.a[i];
    }
    return sum;
}
Vector3 Vector3::cross(const Vector3 &that) const
{
    return Vector3(a[1] * that.a[2] - a[2] * that.a[1],
                   a[2] * that.a[0] - a[0] * that.a[2],
                   a[0] * that.a[1] - a[1] * that.a[0]);
}
Vector3 Vector3::mul(const Matrix33 &M) const
{
    Vector3 V(0,0,0);
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            V.a[i] += M.a[i][j] * this->a[j];
        }
    }
    return V;
}

Matrix33::Matrix33(double a[3][3])
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            this->a[i][j] = a[i][j];
        }
    }
}
