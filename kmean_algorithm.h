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
    void saveClusterReferencesToFileStepResult();
    void sortFinalFile();
    void renderResults();
    int calculateElementsInFile();
    void init();
    void doKmeans();
    Coordinate coordinateT;
    void setK(int);
    int getK();
    bool getReadStatus();
    void setReadStatus(bool);
    int getNumberOfIterations();
    void setNumberOfIterations(int);
    int getNumberOfAllOverDataPoints();
    int getHashKeySize();
    QHash<int, QVector<float> > getHashNotClustered();
    void setHashNotClustered(QHash<int, QVector<float> >);
    int getmanualNumberOfIterations();
    void setmanualNumberOfIterations(int);
    bool getmanualIndexChanged();
    void setmanualIndexChanged(bool);

private:
    QHash<int, QVector<float> > hash_notClustered;
    QVector<QHash<int, QVector<float> > > stepResult;
    QVector<QVector<int> > referValueStepResult;
    QVector<int> referValueStepResultVec;
    int numberOfAllOverDataPoints;
    int numberOfElements;
    QVector<float> minDim;
    QVector<float> maxDim;
    int K;
    int numberOfClusters;
    QHash<int, QVector<float> > clusterMeanCoordinate;
    QHash<int, QVector<float> > prevClusterMeanCoordinate;
    int hashKeySize;
    bool fileIsRead = false;
    int it;
    int manualNumberOfIterations;
    bool manualIndexChanged = false;
};

#endif // KMEAN_ALGORITHM_H
