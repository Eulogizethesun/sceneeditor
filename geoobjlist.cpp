#include "geoobjlist.h"
#include "matrix.h"
#include"math.h"
#define Pi acos(-1.0)

GeoObjList::GeoObjList(Pool *pool, GeoObjList *geoObjList, QListWidget *listWidget)
{
    this->nrObj = 0;
    this->pool = pool;
    this->geoObjList = geoObjList;
    this->listWidget = listWidget;
}

void GeoObjList::add(GeoObj *obj) {
    {
        std::unique_lock<std::mutex> lock(this->m);
        this->a.push_back(obj);
    }
    switch(obj->getType()) {
        case type_cuboid: add_cuboid(obj); break;
        case type_sphere: add_sphere(obj); break;
        case type_prism: add_prism(obj); break;
        case type_cylinder: add_cylinder(obj); break;
        case type_cone: add_cone(obj);break;
        case type_frustumofcone: add_frustumofcone(obj);break;
        case type_pymarid: add_pymarid(obj);break;
        case type_frustum_of_pymarid: add_frustum_of_pymarid(obj);break;
        case type_obj_file: add_obj_file(obj); break;
        default: break;
    }
    obj->setId(++nrObj);
    //this->listWidget->addItem(QString::fromStdString(obj->getName()));
}
bool GeoObjList::add_cuboid(GeoObj *obj) {
    Cuboid *p = dynamic_cast<Cuboid*>(obj);
    if(p == nullptr) return false;
    for(int i = 0; i < 8; ++i) {
        Vertex *v = pool->newVertex(
                    (Cuboid::cube_vertex_coords[i][0] - 0.5) * p->a,
                    (Cuboid::cube_vertex_coords[i][1] - 0.5) * p->b,
                    (Cuboid::cube_vertex_coords[i][2]      ) * p->c);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    for(int i = 0; i < 6; ++i) {
        std::vector<Vertex*> a;
        for(int j = 0; j < 4; ++j) {
            Vertex *v = p->vs[Cuboid::cube_faces[i][j]];
            a.push_back(v);
        }
        Face *f = pool->newFace(a);
        p->fs.push_back(f);
    }
    return true;
}

static void unit_sphere_texture_map(Vertex *v, double &tx, double &ty) {
    tx = atan2(v->y, v->x) / (2*Pi) + 0.5;
    ty = v->z / 2 + 0.5;
}
static void unit_sphere_subdivide(Vertex *v1, Vertex *v2, Vertex *v3, Sphere *p, Pool *pool, int depth) {
    /*
     * Reference:
     * http://www.glprogramming.com/red/chapter02.html#name8
     */
    if(depth > 4) {
        Face *f = pool->newFace(v1, v2, v3);
        unit_sphere_texture_map(v1, f->tx[0], f->ty[0]);
        unit_sphere_texture_map(v2, f->tx[1], f->ty[1]);
        unit_sphere_texture_map(v3, f->tx[2], f->ty[2]);
        p->fs.push_back(f);
        return;
    }
    Vector3 V1(v1);
    Vector3 V2(v2);
    Vector3 V3(v3);
    Vector3 V12 = (V1 + V2) / 2; V12.normalize();
    Vector3 V23 = (V2 + V3) / 2; V23.normalize();
    Vector3 V31 = (V3 + V1) / 2; V31.normalize();
    Vertex *v12 = pool->newVertex(V12); v12->setNormal(V12);
    Vertex *v23 = pool->newVertex(V23); v23->setNormal(V23);
    Vertex *v31 = pool->newVertex(V31); v31->setNormal(V31);
    p->vs.push_back(v12);
    p->vs.push_back(v23);
    p->vs.push_back(v31);
    unit_sphere_subdivide(v1, v12, v31, p, pool, depth + 1);
    unit_sphere_subdivide(v12, v2, v23, p, pool, depth + 1);
    unit_sphere_subdivide(v31, v23, v3, p, pool, depth + 1);
    unit_sphere_subdivide(v12, v23, v31, p, pool, depth + 1);
}
bool GeoObjList::add_sphere(GeoObj *obj) {
    Sphere *p = dynamic_cast<Sphere*>(obj);
    if(p == nullptr) return false;
    p->vs.push_back(pool->newVertex(-1, 0, 0));
    p->vs.push_back(pool->newVertex(+1, 0, 0));
    p->vs.push_back(pool->newVertex(0, -1, 0));
    p->vs.push_back(pool->newVertex(0, +1, 0));
    p->vs.push_back(pool->newVertex(0, 0, -1));
    p->vs.push_back(pool->newVertex(0, 0, +1));
    for(Vertex *v : p->vs) {
        v->setNormal(v->a[0], v->a[1], v->a[2]);
    }
    //p->fs.push_back(pool->newFace(p->vs[5], p->vs[2], p->vs[1]));
    unit_sphere_subdivide(p->vs[5], p->vs[0], p->vs[2], p, pool, 1);
    unit_sphere_subdivide(p->vs[5], p->vs[2], p->vs[1], p, pool, 1);
    unit_sphere_subdivide(p->vs[5], p->vs[1], p->vs[3], p, pool, 1);
    unit_sphere_subdivide(p->vs[5], p->vs[3], p->vs[0], p, pool, 1);
    unit_sphere_subdivide(p->vs[4], p->vs[0], p->vs[3], p, pool, 1);
    unit_sphere_subdivide(p->vs[4], p->vs[3], p->vs[1], p, pool, 1);
    unit_sphere_subdivide(p->vs[4], p->vs[1], p->vs[2], p, pool, 1);
    unit_sphere_subdivide(p->vs[4], p->vs[2], p->vs[0], p, pool, 1);
    p->scale(p->r, p->r, p->r);
    p->translate(p->cx, p->cy, p->cz);
    return true;
}

bool GeoObjList::add_cylinder(GeoObj *obj) {
    Cylinder *p = dynamic_cast<Cylinder*>(obj);
    if(p == nullptr) return false;
    int n=100;
    for(int i = 0; i < n; ++i) {
        Vertex *v = pool->newVertex(
                    p->r * cos(2*Pi*i/n),
                    p->r * sin(2*Pi*i/n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    for(int i = 0; i < n; ++i) {
        Vertex *v = pool->newVertex(
                    p->r * cos(2*Pi*i/n),
                    p->r * sin(2*Pi*i/n),
                    p->h);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }

    std::vector<Vertex*> a;
    for(int j = n-1; j>=0 ; --j) {
        Vertex *v = p->vs[j];
        a.push_back(v);
    }
    Face *f = pool->newFace(a);
    p->fs.push_back(f);


    std::vector<Vertex*> a2;
    for(int j = 0; j <n; ++j) {
        Vertex *v = p->vs[j+n];
        a2.push_back(v);
    }
    Face *f2 = pool->newFace(a2);
    p->fs.push_back(f2);

    int prism_vertex1[4]={0,n,2*n-1,n-1};
    std::vector<Vertex*> a3;
    for(int i = 0; i < 4; ++i) {
        Vertex *v = p->vs[prism_vertex1[i]];
        a3.push_back(v);
    }
    Face *f3 = pool->newFace(a3);
    p->fs.push_back(f3);

    int prism_vertex2[4]={0,1,n+1,n};
    for(int j = 0; j < (n-1); ++j) {
        std::vector<Vertex*> a1;
        for(int i = 0; i < 4; ++i) {
            Vertex *v1 = p->vs[j+prism_vertex2[i]];
            a1.push_back(v1);
        }
        Face *f1 = pool->newFace(a1);
        p->fs.push_back(f1);
    }

    return true;
}

bool GeoObjList::add_prism(GeoObj *obj) {
    Prism *p = dynamic_cast<Prism*>(obj);
    if(p == nullptr) return false;
    for(int i = 0; i < (p->n); ++i) {
        Vertex *v = pool->newVertex(
                    p->a *0.5/sin(Pi/p->n) * cos(2*Pi*i/p->n),
                    p->a *0.5/sin(Pi/p->n)* sin(2*Pi*i/p->n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    for(int i = 0; i < (p->n); ++i) {
        Vertex *v = pool->newVertex(
                    p->a * 0.5/sin(Pi/p->n) * cos(2*Pi*i/p->n),
                    p->a * 0.5/sin(Pi/p->n) * sin(2*Pi*i/p->n),
                    p->h);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }

    std::vector<Vertex*> a;
    for(int j = static_cast<int>((p->n)-1); j>=0 ; --j) {
        Vertex *v = p->vs[j];
        a.push_back(v);
    }
    Face *f = pool->newFace(a);
    p->fs.push_back(f);


    std::vector<Vertex*> a2;
    for(int j = 0; j < p->n; ++j) {
        Vertex *v = p->vs[j+p->n];
        a2.push_back(v);
    }
    Face *f2 = pool->newFace(a2);
    p->fs.push_back(f2);

    int prism_vertex1[4]={0,static_cast<int>(p->n),static_cast<int>(2*(p->n)-1),static_cast<int>(p->n-1)};
    std::vector<Vertex*> a3;
    for(int i = 0; i < 4; ++i) {
        Vertex *v = p->vs[prism_vertex1[i]];
        a3.push_back(v);
    }
    Face *f3 = pool->newFace(a3);
    p->fs.push_back(f3);

    int prism_vertex2[4]={0,1,static_cast<int>((p->n)+1),static_cast<int>(p->n)};
    for(int j = 0; j < (p->n-1); ++j) {
        std::vector<Vertex*> a1;
        for(int i = 0; i < 4; ++i) {
            Vertex *v1 = p->vs[j+prism_vertex2[i]];
            a1.push_back(v1);
        }
        Face *f1 = pool->newFace(a1);
        p->fs.push_back(f1);
    }

    return true;
}

bool GeoObjList::add_cone(GeoObj *obj) {
    Cone *p = dynamic_cast<Cone*>(obj);
    if(p == nullptr) return false;
    int n=100;
    for(int i = 0; i < n; i++) {
        Vertex *v = pool->newVertex(
                    p->r *cos(i*2*Pi/n),
                    p->r *sin(-i*2*Pi/n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> a;
    for(int j = 0; j<n ; j++) {
        Vertex *v = p->vs[j];
        a.push_back(v);
    }
    Face *f = pool->newFace(a);
    p->fs.push_back(f);

    Vertex *top=pool->newVertex(0,0,p->h);
    p->vs.push_back(top);
    top->translate(p->cx,p->cy,p->cz);
    for(int i=0;i<n-1;i++)
    {
        Face *side=pool->newFace(p->vs[i+1],p->vs[i],top);
        p->fs.push_back(side);
    }
    Face *side=pool->newFace(p->vs[0],p->vs[n-1],top);
    p->fs.push_back(side);

    return true;
}

bool GeoObjList::add_frustumofcone(GeoObj *obj) {
    FrustumofCone *p = dynamic_cast<FrustumofCone*>(obj);
    if(p == nullptr) return false;
    int n=100;
    for(int i = 0; i < n; i++) {
        Vertex *v = pool->newVertex(
                    p->r_lower *cos(i*2*Pi/n),
                    p->r_lower *sin(-i*2*Pi/n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> lower;
    for(int j = 0; j<n ; j++) {
        Vertex *v = p->vs[j];
        lower.push_back(v);
    }
    Face *l = pool->newFace(lower);
    p->fs.push_back(l);

    for(int i = 0; i < n; i++) {
        Vertex *v = pool->newVertex(
                    p->r_upper *cos(i*2*Pi/n),
                    p->r_upper *sin(i*2*Pi/n),
                    p->h);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> upper;
    for(int j = n; j<2*n ; j++) {
        Vertex *v = p->vs[j];
        upper.push_back(v);
    }
    Face *u = pool->newFace(upper);
    p->fs.push_back(u);

    for(int i=1;i<n-1;i++)
    {
        Face *side=pool->newFace(p->vs[i+1],p->vs[i],p->vs[2*n-i],p->vs[2*n-i-1]);
        p->fs.push_back(side);
    }
    Face *side1=pool->newFace(p->vs[1],p->vs[0],p->vs[n],p->vs[2*n-1]);
    p->fs.push_back(side1);
    Face *side2=pool->newFace(p->vs[0],p->vs[n-1],p->vs[n+1],p->vs[n]);
    p->fs.push_back(side2);
    return true;
}

bool GeoObjList::add_pymarid(GeoObj *obj) {
    Pymarid *p = dynamic_cast<Pymarid*>(obj);
    if(p == nullptr) return false;
    for(int i = 0; i < p->n; i++) {
        Vertex *v = pool->newVertex(
                    p->a/2/sin(Pi/p->n) *cos(i*2*Pi/p->n),
                    p->a/2/sin(Pi/p->n) *sin(-i*2*Pi/p->n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> a;
    for(int j = 0; j<p->n ; j++) {
        Vertex *v = p->vs[j];
        a.push_back(v);
    }
    Face *f = pool->newFace(a);
    p->fs.push_back(f);

    Vertex *top=pool->newVertex(0,0,p->h);
    top->translate(p->cx,p->cy,p->cz);
    for(int i=0;i<p->n-1;i++)
    {
        Face *side=pool->newFace(p->vs[i+1],p->vs[i],top);
        p->fs.push_back(side);
    }
    Face *side=pool->newFace(p->vs[0],p->vs[p->n-1],top);
    p->fs.push_back(side);


    return true;
}

bool GeoObjList::add_frustum_of_pymarid(GeoObj *obj) {
    Frustum_of_pymarid *p = dynamic_cast<Frustum_of_pymarid*>(obj);
    if(p == nullptr) return false;
    for(int i = 0; i < p->n; i++) {
        Vertex *v = pool->newVertex(
                    p->a_lower/2/sin(Pi/p->n) *cos(i*2*Pi/p->n),
                    p->a_lower/2/sin(Pi/p->n) *sin(-i*2*Pi/p->n),
                    0);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> lower;
    for(int j = 0; j<p->n ; j++) {
        Vertex *v = p->vs[j];
        lower.push_back(v);
    }
    Face *l = pool->newFace(lower);
    p->fs.push_back(l);

    for(int i = 0; i < p->n; i++) {
        Vertex *v = pool->newVertex(
                    p->a_upper/2/sin(Pi/p->n) *cos(i*2*Pi/p->n),
                    p->a_upper/2/sin(Pi/p->n) *sin(i*2*Pi/p->n),
                    p->h);
        v->translate(p->cx, p->cy, p->cz);
        p->vs.push_back(v);
    }
    std::vector<Vertex*> upper;
    for(int j = p->n; j<2*p->n ; j++) {
        Vertex *v = p->vs[j];
        upper.push_back(v);
    }
    Face *u = pool->newFace(upper);
    p->fs.push_back(u);

    for(int i=1;i<p->n-1;i++)
    {
        Face *side=pool->newFace(p->vs[i+1],p->vs[i],p->vs[2*p->n-i],p->vs[2*p->n-i-1]);
        p->fs.push_back(side);
    }
    Face *side1=pool->newFace(p->vs[1],p->vs[0],p->vs[p->n],p->vs[2*p->n-1]);
    p->fs.push_back(side1);
    Face *side2=pool->newFace(p->vs[0],p->vs[p->n-1],p->vs[p->n+1],p->vs[p->n]);
    p->fs.push_back(side2);
    return true;
}


bool GeoObjList::add_obj_file(GeoObj *obj) {
    ObjFile *p = dynamic_cast<ObjFile*>(obj);
    if(p == nullptr) return false;
    return true;
}

/*
void GeoObjList::paintAll() {
    std::unique_lock<std::mutex> lock(this->m);
    printf("%d\n", a.size());
    for(GeoObj *obj : this->a) {
        obj->paint();
    }
}
*/
