/**
*	@file PointCollection.h
*	@brief file contains the definaion of the class PointCollection
*	@author Mikayel Egibyan
*/

#ifndef POINTCOLLECTION_H
#define POINTCOLLECTION_H

#include <QPointF>
#include <QVector>
#include <QtMath>

class PointCollection: public QVector<QPointF>
{
public:
    PointCollection();
    void addPoint(QPointF);
    QPointF deletePoint(QPointF);
    QPointF getNearestPointToCentroid();
    QPointF PointT;
    QPointF getCentroid();
    void setCentroid(QPointF);
    void updateCentroid();
    float calculateEuclideanDist(QPointF, QPointF);
private:
    QPointF centroid;
};

#endif // POINTCOLLECTION_H
