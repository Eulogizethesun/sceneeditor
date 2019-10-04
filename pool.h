#ifndef POOL_H
#define POOL_H

#include<vector>
#include<set>
#include<mutex>
#include "matrix.h"
#include<algorithm>

class Vector3;
class Matrix33;

class Vertex
{
public:
    int id;     // id starts from 1
    mutable double a[3]; // mutable means a can be changed without changing the ordering (id) in a set
    mutable double n[3]; // normal vector
    mutable bool hasNormal = false;
    const double &x=a[0], &y=a[1], &z=a[2];
    const double &nx=n[0], &ny=n[1], &nz=n[2];
public:
    Vertex(int id, double x, double y, double z);
    bool operator < (const Vertex &that) const {return id < that.id;}
    void setNormal(double x, double y, double z);
    void setNormal(Vector3 V);
    void translate(double x, double y, double z);
    void scale(double x, double y, double z);
    void rotate(double x, double y, double z, double ang); // rotate ang (radians) around vector (x,y,z)
};

class Face
{
public:
    int id;     // id starts from 1
    const std::vector<Vertex*> a;
    std::vector<double> tx, ty; // texture points
public:
    void calcDefaultTexturePoints();
    Face(int id, std::vector<Vertex*> a);
    bool operator < (const Face &that) const {return id < that.id;}
};

class Pool
{
private:
    int nv = 0;     // number of vertices
    int nf = 0;     // number of faces
public:
    std::mutex m;
    std::set<Vertex> vs;    // vertices
    std::set<Face> fs;      // faces
public:
    Pool();
    Vertex* newVertex(double x, double y, double z);
    Vertex* newVertex(const double *coords);
    Vertex* newVertex(const int *coords);
    Vertex* newVertex(Vector3 V);
    Face* newFace(std::vector<Vertex*> a);
    Face* newFace(Vertex *v1, Vertex *v2, Vertex *v3);
    Face* newFace(Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4);
    int getnv();
    int getnf();
};

#endif // POOL_H
