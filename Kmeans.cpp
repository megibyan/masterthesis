/**
*	@file Kmeans.cpp
*	@brief file contains all necessary methods to work with Kmeans
*	@author Mikayel Egibyan
*/

#include "Kmeans.h"

QVector<PointCollection> Kmeans::kmean(PointCollection points, int numberofClusters)
{
    QVector<PointCollection> allClusters;
    QVector<QVector<QPointF> > allGroups = temp.SplitVector(points, numberofClusters);
    foreach(QVector<QPointF> group, allGroups)
    {
        PointCollection cluster;
        for(int i= 0; i< group.indexOf(group.last()); i++)
            cluster.append(group.at(i));
        allClusters.push_back(cluster);
    }
    int movements = 1;
    while(movements)
    {
        movements = 0;
        foreach (PointCollection cluster, allClusters)
        {
            for(int index=0; index< cluster.count(); index++)
            {
                QPointF point = cluster[index];

                int nearestCluster = FindNearestCluster(allClusters, point);
                if(nearestCluster != allClusters.indexOf(cluster))
                {
                    if(cluster.count() > 1)
                    {
                        QPointF removedPoint = cluster.deletePoint(point);
                        allClusters[nearestCluster].addPoint(removedPoint);
                        movements += 1;
                    }
                }
            }
        }
    }
    return (allClusters);
}

int Kmeans::FindNearestCluster(QVector<PointCollection> allClusters, QPointF point)
{
    float minimumDistance = 0.0;
    int nearestClusterIndex = -1;

    for (int k = 0; k < allClusters.count(); k++)
    {
        QPointF centroidValue = allClusters[k].getCentroid();
        float distance = w.calculateEuclideanDist(point, centroidValue);
        if (k == 0)
        {
            minimumDistance = distance;
            nearestClusterIndex = 0;
        }
        else if (minimumDistance > distance)
        {
            minimumDistance = distance;
            nearestClusterIndex = k;
        }
    }
    return (nearestClusterIndex);
}
