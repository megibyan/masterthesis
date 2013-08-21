#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>
#include <QPointF>
#include "PointCollection.h"

class Kmeans
{
public:
    Kmeans();
    static QVector<QPointF> kmean(QPointF, int);
private:
};

#endif // KMEANS_H
