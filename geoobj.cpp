#include "geoobj.h"
#include <QtWidgets>
#include <QtOpenGL/QGLWidget>
#include <glut.h>
#include <string>

GeoObj::GeoObj() {
    this->type = type_unknown;
    this->id = -1;
    this->textureId = -1;
    setColorDefault();
}
GeoObj::GeoObj(GeoObjType type) {
    this->type = type;
    this->id = -1;
    this->textureId = -1;
    setColorDefault();
}
void GeoObj::removeTexture() {
    this->textureId = -1;
}
void GeoObj::setTextureId(int id) {
    this->textureId = id;
}
int GeoObj::getTextureId() {
    return this->textureId;
}
void GeoObj::setColorDefault() {
    color[0] = 0.5; // R
    color[1] = 0.5; // G
    color[2] = 0.5; // B
    color[3] = 1;   // A
}
void GeoObj::setColor(double R, double G, double B, double A) {
    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = A;
}
enum GeoObjType GeoObj::getType() {
    return this->type;
}
std::string GeoObj::getTypeStr() {
    return "unknown";
}
std::string GeoObj::getName() {
    return "Object " + std::to_string(this->id) + " (" + this->getTypeStr() + ")";
}
GeoObj::~GeoObj() {

}
void GeoObj::translate(double x, double y, double z) {
    for(Vertex *v : vs) {
        v->translate(x, y, z);
    }
}
void GeoObj::scale(double x, double y, double z) {
    for(Vertex *v : vs) {
        v->scale(x, y, z);
    }
}
void GeoObj::rotate(double x, double y, double z, double ang) {
    for(Vertex *v : vs) {
        v->rotate(x, y, z, ang);
    }
}
/*
void GeoObj::paint() {

}
*/

//////////////////////////////

/*
void Cuboid::paint() {
    printf("Cuboid::paint()\n"); fflush(stdout);
}

void Sphere::paint() {
    printf("Sphere::paint()\n"); fflush(stdout);
}
*/

ObjFile::ObjFile(ObjModel *objModel) {
    for(int i = 0; i < objModel->list_Vertices.size(); ++i) {
        this->vs.push_back(objModel->list_Vertices.at(i));
    }
    for(int i = 0; i < objModel->list_Faces.size(); ++i) {
        this->fs.push_back(objModel->list_Faces.at(i));
    }
}
