#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "pool.h"

class ObjModel
{
public:

    QString path;
    int num_Vertices;
    int num_Faces;

    QList<Vertex*> list_Vertices;
    QList<Face*> list_Faces;
};

#endif // OBJMODEL_H
