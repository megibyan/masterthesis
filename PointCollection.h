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
    QPointF deletePoint(int);
    QPointF deletePoint(QPointF);
    QPointF getNearestPointToCentroid();
    QPointF PointT;
    QPointF getCenroid();
    float calculateEuclideanDist(QPointF, QPointF);
    void setCentoird(QPointF);
    void updateCentroid();
private:
    QPointF centorid;
};

#endif // POINTCOLLECTION_H
