#ifndef GEOOBJLIST_H
#define GEOOBJLIST_H

#include "geoobj.h"
#include "pool.h"
#include "geoobjlist.h"
#include <vector>
#include <mutex>
#include <QListWidget>

class GeoObj;
class Vertex;
class Face;
class Pool;

class GeoObjList
{
public:
    GeoObjList(Pool *pool, GeoObjList *geoObjList, QListWidget *listWidget);
    void add(GeoObj *obj);
    //void paintAll();
public:
    std::mutex m;
    std::vector<GeoObj*> a;
    Pool *pool;
    QListWidget *listWidget;
    GeoObjList *geoObjList;
private:
    int nrObj = 0; // number of objects
private:
    bool add_cuboid(GeoObj *obj);
    bool add_sphere(GeoObj *obj);
    bool add_prism(GeoObj *obj);
    bool add_cylinder(GeoObj *obj);
    bool add_cone(GeoObj *obj);
    bool add_frustumofcone(GeoObj *obj);
    bool add_pymarid(GeoObj *obj);
    bool add_frustum_of_pymarid(GeoObj *obj);
    bool add_obj_file(GeoObj *obj);
};

#endif // GEOOBJLIST_H
