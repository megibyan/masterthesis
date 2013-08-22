/**
*	@file PointCollection.cpp
*	@brief file contains all necessary methods to work with PointCollection
*	@author Mikayel Egibyan
*/

#include "PointCollection.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
PointCollection::PointCollection()
{

}

/**
 * This method is used to get a value of centroid
 * @author Mikayel Egibyan
 * @return The value of the centroid
 */
QPointF PointCollection::getCentroid()
{
    return centroid;
}

/**
 * This method is used to set a value centroid
 * @author Mikayel Egibyan
 * @param centroid Centroid is Point type object
 */
void PointCollection::setCentroid(QPointF centroid)
{
    this->centroid = centroid;
}

/**
 * This method is used to update the centroid
 * @author Mikayel Egibyan
*/
void PointCollection::updateCentroid()
{
    QPointF p;
    double xSum = 0;
    double ySum = 0;
    for(QVector::iterator it=this->begin(); it!=this->end(); it++)
    {
        xSum = xSum + it->rx();
        ySum = ySum + it->ry();
    }

    centroid.rx() = (xSum / (double)this->count());
    centroid.ry() = (ySum / (double)this->count());
}

/**
 * This method is used to find the nearest point to the centroid
 * @author Mikayel Egibyan
 */
QPointF PointCollection::getNearestPointToCentroid()
{
    float minDist = 0.0;
    int NearestPointToCentroidIndex = -1;
    while(!this->empty())
    {
        QPointF point;
        float dist = calculateEuclideanDist(point, centroid);
        if(this->indexOf(point) == 0)
        {
            minDist = dist;
            NearestPointToCentroidIndex = this->indexOf(point);
        }
        else
        {
            if(minDist > dist)
            {
                minDist = dist;
                NearestPointToCentroidIndex = this->indexOf(point);
            }
        }
    }
    return(this->at(NearestPointToCentroidIndex));
}

/**
 * This method is used to get the Euclidean distance between two points
 * @author Mikayel Egibyan
 * @param point_1,point_2 point_1,point_2 are Point type objects
 */
float PointCollection::calculateEuclideanDist(QPointF point_1, QPointF point_2)
{
    float x1 = point_1.x(), y1 = point_1.y();
    float x2 = point_2.x(), y2 = point_2.y();

    float dist = qSqrt(qPow(x2 - x1, 2.0) + qPow(y2 - y1, 2.0));
    return (dist);
}

QPointF PointCollection::deletePoint(QPointF p)
{
    QPointF *removedPoint = new QPointF(p.x(), p.y());
    this->remove(this->indexOf(*removedPoint));
    updateCentroid();

    return(*removedPoint);
}

void PointCollection::addPoint(QPointF p)
{
    this->append(p);
    updateCentroid();
}
