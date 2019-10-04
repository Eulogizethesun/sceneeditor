#ifndef GEOOBJ_H
#define GEOOBJ_H

#include <QtWidgets>
#include <QtOpenGL/QGLWidget>
#include <glut.h>
#include <vector>
#include <string>
#include "pool.h"
#include"mainglwidget.h"
#include"objmodel.h"

/*
 * OpenGL does not work well with object oriented programming
 * Reference
 * https://www.khronos.org/opengl/wiki/Common_Mistakes#The_Object_Oriented_Language_Problem
 */

class MainGLWidget;
class ObjModel;

enum GeoObjType {
    type_unknown,
    type_cuboid,
    type_sphere,
    type_cylinder,
    type_cone,
    type_frustumofcone,
    type_prism,
    type_pymarid,
    type_frustum_of_pymarid,
    type_obj_file
};

class GeoObj
{
public:
    std::vector<Vertex*> vs;    // vertices
    std::vector<Face*> fs;      // faces
    double color[4];
    int textureId;
public:
    GeoObj();
    GeoObj(enum GeoObjType type);
    void setColorDefault();
    void setColor(double R, double G, double B, double A);
    void removeTexture();
    void setTextureId(int id);
    int getTextureId();
    enum GeoObjType getType();
    std::string getName();
    void setId(int id) {this->id = id;}
    int getId() {return id;}
    virtual std::string getTypeStr();
    virtual ~GeoObj(); // make GeoObj polymorphic
    //virtual void paint();
    void translate(double x, double y, double z);
    void scale(double x, double y, double z);
    void rotate(double x, double y, double z, double ang); // rotate ang (radians) around vector (x,y,z)
private:
    GeoObjType type;
    int id;
};

class Cuboid : public GeoObj
{
public:
    constexpr static float cube_coords[6][4][3] = {
        {{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0}}, // down
        {{0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}}, // up
        {{0,0,0}, {1,0,0}, {1,0,1}, {0,0,1}}, // left
        {{0,1,0}, {1,1,0}, {1,1,1}, {0,1,1}}, // right
        {{0,0,0}, {0,1,0}, {0,1,1}, {0,0,1}}, // front
        {{1,0,0}, {1,1,0}, {1,1,1}, {1,0,1}}, // back
    };
    constexpr static int cube_vertex_coords[8][3] = {
        {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
        {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}
    };
    constexpr static int cube_faces[6][4] = {
        {0, 3, 2, 1}, // down
        {4, 5, 6, 7}, // up
        {0, 1, 5, 4}, // left
        {3, 7, 6, 2}, // right
        {0, 4, 7, 3}, // front
        {1, 2, 6, 5}, // back
    };
    double a, b, c;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Cuboid(double a, double b, double c,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_cuboid),
        a(a), b(b), c(c),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
public:
    std::string getTypeStr() {return "Cuboid";}
    //void paint();
};

class Sphere : public GeoObj
{
public:
    double r;
    double cx, cy, cz;
public:
    Sphere(double r,
           double cx, double cy, double cz) :
        GeoObj(type_sphere),
        r(r),
        cx(cx), cy(cy), cz(cz)
    {}
public:
    std::string getTypeStr() {return "Sphere";}
    //void paint();
};

class Prism : public GeoObj
{
public:

    double a, h, n;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Prism(double a, double h, double n,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_prism),
        a(a), h(h), n(n),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
public:
    std::string getTypeStr() {return "Prism";}
    //void paint();
};

class Cylinder :public GeoObj
{
public:
    double r;
    double h;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Cylinder( double r, double h,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_cylinder),
        r(r),h(h),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
    std::string getTypeStr() {return "Cylinder";}
};

class Cone :public GeoObj
{
public:
    double r;
    double h;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Cone(  double r,
           double h,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_cone),
        r(r),
        h(h),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
    std::string getTypeStr() {return "Cone";}
};
class FrustumofCone:public GeoObj
{
public:
    double h;
    double r_lower,r_upper;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    FrustumofCone(double h,
           double r_lower,double r_upper,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_frustumofcone),
        h(h),
        r_lower(r_lower),r_upper(r_upper),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
    std::string getTypeStr() {return "Frustum of Cone";}
};

class Pymarid : public GeoObj
{
public:

    double a, h, n;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Pymarid(double a, double h, double n,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_pymarid),
        a(a), h(h), n(n),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
    std::string getTypeStr() {return "Pyramid";}
};

class Frustum_of_pymarid : public GeoObj
{
public:

    double a_lower,a_upper, h, n;
    double cx, cy, cz;
    double nx, ny, nz;
public:
    Frustum_of_pymarid(double a_lower, double a_upper, double h, double n,
           double cx, double cy, double cz,
           double nx, double ny, double nz) :
        GeoObj(type_frustum_of_pymarid),
        a_lower(a_lower), a_upper(a_upper), h(h), n(n),
        cx(cx), cy(cy), cz(cz),
        nx(nx), ny(ny), nz(nz)
    {}
    std::string getTypeStr() {return "Frustum of pyramid";}
};


class ObjFile : public GeoObj
{
public:
    //ObjFile() {}
    ObjFile(ObjModel *objModel);
    std::string getTypeStr() {return ".obj file";}
};

#endif // GEOOBJ_H
