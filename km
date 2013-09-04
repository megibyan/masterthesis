/**
*	@file kmean_algorithm.h
*	@brief file contains the definaion of the class kmean_algorithm
*	@author Mikayel Egibyan
*/

#ifndef KMEAN_ALGORITHM_H
#define KMEAN_ALGORITHM_H

#include <QHash>
#include <QVector>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QtMath>
#include <fstream>
#include "Coordinate.h"

class kmean_algorithm
{
public:
    kmean_algorithm();
    void readFileOfNotClustereData(QString);
    void findMinMaxCoordinatesOfDimensions();
    int separatePointsIntoGroups(int);
    void saveClusterMeansToFile();
    void saveClusterReferencesToFile(int a[]);
    void sortFinalFile();
    int calculateElementsInFile();
    void init();
    void doKmeans();
    Coordinate coordinateT;
    void setK(int);
    int getK();
    bool getReadStatus();
    int getNumberOfIterations();

private:
    QHash<int, QVector<float> > hash_notClustered;
    int numberOfAllOverDataPoints;
    int numberOfElements;
    QVector<float> minDim;
    QVector<float> maxDim;
    int numberOfClusters = 3;
    QHash<int, QVector<float> > clusterMeanCoordinate;
    QHash<int, QVector<float> > prevClusterMeanCoordinate;
    int hashKeySize;
    bool fileIsRead = false;
    int it;
};

#endif // KMEAN_ALGORITHM_H
