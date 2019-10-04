#include "pool.h"
#include "matrix.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////

Vertex::Vertex(int id, double x, double y, double z)
    : id(id)
{
    a[0] = x; a[1] = y; a[2] = z;
    this->hasNormal = false;
}
void Vertex::setNormal(double x, double y, double z)
{
    n[0] = x; n[1] = y; n[2] = z;
    this->hasNormal = true;
}
void Vertex::setNormal(Vector3 V)
{
    setNormal(V.a[0], V.a[1], V.a[2]);
}
void Vertex::translate(double x, double y, double z)
{
    a[0] += x; a[1] += y; a[2] += z;
}
void Vertex::scale(double x, double y, double z)
{
    a[0] *= x; a[1] *= y; a[2] *= z;
}
void Vertex::rotate(double x, double y, double z, double ang) // rotate ang (radians) around vector (x,y,z)
{
    Vector3 V(x, y, z);
    if(V.norm() < 1e-9) return;
    V.normalize();

    /*
    for(int i = 0; i < 3; ++i) {
        printf("%f\n", V.a[i]); fflush(stdout);
    }
    */

    x = V.a[0];
    y = V.a[1];
    z = V.a[2];

    double s = sin(ang);
    double c = cos(ang);
    double m[3][3];
    m[0][0] = x*x*(1-c)+c;
    m[0][1] = x*y*(1-c)-z*s;
    m[0][2] = x*z*(1-c)+y*s;
    m[1][0] = y*x*(1-c)+z*s;
    m[1][1] = y*y*(1-c)+c;
    m[1][2] = y*z*(1-c)-x*s;
    m[2][0] = x*z*(1-c)-y*s;
    m[2][1] = y*z*(1-c)+x*s;
    m[2][2] = z*z*(1-c)+c;
    Matrix33 M(m);

    Vector3 Vnew = Vector3(this).mul(M);
    for(int i = 0; i < 3; ++i) {
        a[i] = Vnew.a[i];
        //printf("%f\n", Vnew.a[i]); fflush(stdout);
    }
}

//////////////////////////////////////////////////////////////////////

Face::Face(int id, std::vector<Vertex *> a)
    : id(id), a(a)
{
    calcDefaultTexturePoints();
    for(int i = 0; i < a.size(); ++i) {
        printf("%f %f\n", tx[i], ty[i]);
    }
    fflush(stdout);
}
void Face::calcDefaultTexturePoints()
{
    int n = a.size();
    double xmin = a[0]->x, xmax = a[0]->x;
    double ymin = a[0]->y, ymax = a[0]->y;
    double zmin = a[0]->z, zmax = a[0]->z;
    for(int i = 1; i < n; ++i) {
        xmin = std::min(xmin, a[i]->x);
        xmax = std::max(xmax, a[i]->x);
        ymin = std::min(ymin, a[i]->y);
        ymax = std::max(ymax, a[i]->y);
        zmin = std::min(zmin, a[i]->z);
        zmax = std::max(zmax, a[i]->z);
    }
    double xd = xmax - xmin;
    double yd = ymax - ymin;
    double zd = zmax - zmin;
    if(xd < yd && xd < zd) { // use y and z
        for(int i = 0; i < n; ++i) {
            tx.push_back((a[i]->y - ymin) / yd);
            ty.push_back((a[i]->z - zmin) / zd);
        }
    } else if(yd < xd && yd < zd) { // use x and z
        for(int i = 0; i < n; ++i) {
            tx.push_back((a[i]->x - xmin) / xd);
            ty.push_back((a[i]->z - zmin) / zd);
        }
    } else { // use x and y
        for(int i = 0; i < n; ++i) {
            tx.push_back((a[i]->x - xmin) / xd);
            ty.push_back((a[i]->y - ymin) / yd);
        }
    }
}

//////////////////////////////////////////////////////////////////////

Pool::Pool()
{

}
Vertex* Pool::newVertex(double x, double y, double z)
{
    std::unique_lock<std::mutex> lock(this->m);
    ++nv;
    Vertex *v = new Vertex(nv, x, y, z);
    vs.insert(vs.end(), *v);
    return v;
}
Vertex* Pool::newVertex(const double *coords)
{
    return newVertex(coords[0], coords[1], coords[2]);
}
Vertex* Pool::newVertex(const int *coords)
{
    return newVertex(coords[0], coords[1], coords[2]);
}
Vertex* Pool::newVertex(Vector3 V)
{
    return newVertex(V.a[0], V.a[1], V.a[2]);
}
Face* Pool::newFace(std::vector<Vertex*> a)
{
    std::unique_lock<std::mutex> lock(this->m);
    ++nf;
    Face *f = new Face(nf, a);
    fs.insert(fs.end(), *f);
    return f;
}
Face* Pool::newFace(Vertex *v1, Vertex *v2, Vertex *v3)
{
    std::vector<Vertex*> a;
    a.push_back(v1);
    a.push_back(v2);
    a.push_back(v3);
    return newFace(a);
}
Face* Pool::newFace(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4)
{
    std::vector<Vertex*> a;
    a.push_back(v1);
    a.push_back(v2);
    a.push_back(v3);
    a.push_back(v4);
    return newFace(a);
}
int Pool::getnv()
{
    return nv;
}
int Pool::getnf()
{
    return nf;
}
