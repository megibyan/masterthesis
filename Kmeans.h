/**
*	@file Kmeans.h
*	@brief file contains the definaion of the class Kmeans
*	@author Mikayel Egibyan
*/

#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>
#include <QPointF>
#include "QVecTemp.h"
#include "PointCollection.h"

class Kmeans
{
public:
    QVector<PointCollection> kmean(PointCollection, int);
    int FindNearestCluster(QVector<PointCollection>, QPointF);
    QVecTemp<QPointF> temp;
    PointCollection w;
private:

};

#endif // KMEANS_H
