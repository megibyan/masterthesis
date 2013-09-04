/**
*	@file kmean_algorithm.cpp
*	@brief file contains all necessary methods to work with kmean_algorithm
*	@author Mikayel Egibyan
*/

#include "kmean_algorithm.h"

/**
 * This method is used to render the data points got from the .csv file
 * @author Mikayel Egibyan
 */
kmean_algorithm::kmean_algorithm()
{
}


void kmean_algorithm::sortFinalFile()
{
    QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ClusterReferences.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "Dim_1" << "Dim_2" << "Dim_3" << "Dim_4" << "Cluster" << '\n';
}

/**
 * This method is used to read not clustered data from a .csv file
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::readFileOfNotClustereData(QString filename)
{
    QFile file(filename);
    //QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\iris.csv");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
    fileIsRead = true;
    QString fileLine = file.readLine();
    QStringList fileLineSplit = fileLine.split(',');
    hashKeySize = fileLineSplit.size();
    //qDebug() << hashKeySize;

    for(int t=0; t<hashKeySize; t++)
    {
        QVector<float> vec;
        hash_notClustered[t] = vec;
    }
    file.close();

    QFile file1(filename);
    if(!file1.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file1.errorString());
    }
    while(!file1.atEnd())
    {
        QString line = file1.readLine();
        QStringList list = line.split(',');
        for(int t = 0; t<list.size(); t++)
        {
            hash_notClustered[t].push_back(list[t].toFloat());
        }
    }
    //qDebug() << "hash_notClustered[0].size()" << hash_notClustered[0].size();
    doKmeans();
    QHashIterator<int, QVector<float> > i(hash_notClustered);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << ":" << i.value();
    }
}

/**
 * This method is used to find out minimal and maximal values of each dimension
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::findMinMaxCoordinatesOfDimensions()
{
    for(int i = 0; i<hashKeySize; i++)
        {
            minDim.push_back(coordinateT.getMin(hash_notClustered[i]));
            maxDim.push_back(coordinateT.getMax(hash_notClustered[i]));
        }
}

/**
 * This method is used to separate the data points into groups
 * @author Mikayel Egibyan
 **/
int kmean_algorithm::separatePointsIntoGroups(int point)
{
    int clusterReferedValue;
    float euclideanDistancePointClusterMean = 0;
    float minDistancePointClosestMean;

    for(int cluster = 0; cluster<numberOfClusters; cluster ++)
    {
        euclideanDistancePointClusterMean = qSqrt(qPow((clusterMeanCoordinate[0].at(cluster) - hash_notClustered[0].at(point)), 2) + qPow((clusterMeanCoordinate[1].at(cluster) - hash_notClustered[1].at(point)), 2) + qPow((clusterMeanCoordinate[2].at(cluster) - hash_notClustered[2].at(point)), 2) + qPow((clusterMeanCoordinate[3].at(cluster) - hash_notClustered[3].at(point)), 2));
        if(cluster == 0)
        {
            minDistancePointClosestMean = euclideanDistancePointClusterMean;
            clusterReferedValue = cluster;
        }
        if(cluster > 0)
        {
            if(euclideanDistancePointClusterMean < minDistancePointClosestMean)
            {
                minDistancePointClosestMean = euclideanDistancePointClusterMean;
                clusterReferedValue = cluster;
            }
        }
        /*qDebug()<<"X["<<point<<"]: "<<hash_notClustered[0].value(point);
        qDebug()<<"Y["<<point<<"]: "<<hash_notClustered[1].value(point);
        qDebug()<<"Distance to Cluster "<<cluster<<" is: "<<euclideanDistancePointClusterMean;*/

    }
    return clusterReferedValue;
}

/**
 * This method is used to save cluster means into a file
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::saveClusterMeansToFile()
{
    QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ClusterMeans.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    if(file.isOpen())
    {
        for(int i=0; i<numberOfClusters; i++)
        {
            for(int j = 0; j<hashKeySize; j++)
                {
                    out << clusterMeanCoordinate[j].at(i)  << '\t';
                }
            out << '\n';
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
}

/**
 * This method is used to save information to which cluster belongs the point into a file
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::saveClusterReferencesToFile(int a[])
{
    int n = numberOfAllOverDataPoints;
    int m =  hashKeySize;
    QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ClusterReferences.csv");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    //QHashIterator<int, QVector<float> > i(hash_notClustered);
    QTextStream out(&file);
    if(file.isOpen())
    {
        out << "Dim_1" << "," << "Dim_2" << "," << "Dim_3" << "," <<"Dim_4" << "," <<"Cluster" << '\n';
        for (int i=0 ; i< n; i++)
        {
            for (int j = 0; j<m; j++)
            {
                out << hash_notClustered[j].at(i)<<  ",";
            }
            out << a[i] + 1 << '\n';
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
}

/**
 * This method is used to calculate the number of elements in the file
 * @author Mikayel Egibyan
 **/
int kmean_algorithm::calculateElementsInFile()
{
    numberOfElements = 0;
    QHash<int, QVector<float> >::iterator it;
    for (it = hash_notClustered.begin(); it != hash_notClustered.end(); ++it)
    {
        numberOfElements +=  it.value().size();
        //qDebug() << numberOfElements;
        //numberOfElements = it.value().size() + numberOfElements;
    }
    //qDebug() << "Number of elements in the file is " << numberOfElements;
    //qDebug() << "Number of data points is " << numberOfElements/2 << '\n';
}

/**
 * This method is used to initialize the location of the cluster
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::init()
{
    QVector<float> Range;
    for(int i = 0; i < hashKeySize; i++)
      {
          Range.push_back(maxDim[i] - minDim[i]);
      }
    for(int k = 0; k < numberOfClusters; k++)
    {
        for(int j= 0; j<hashKeySize; j++)
        {
            clusterMeanCoordinate[j].push_back(minDim[j] + float(Range[j]*rand() / (RAND_MAX + 1.0)));
        }
    }
    prevClusterMeanCoordinate = clusterMeanCoordinate;
}

/**
 * This method is used to apply k-means algorithm on the given data set
 * @author Mikayel Egibyan
 **/
void kmean_algorithm::doKmeans()
{
    //readFileOfNotClustereData();
    calculateElementsInFile();
    findMinMaxCoordinatesOfDimensions();
    init();
    numberOfAllOverDataPoints = numberOfElements / hashKeySize;
    int referCluster[numberOfAllOverDataPoints];

    float dimOverAll[hashKeySize];
    for(int q = 0; q < hashKeySize; q++)
    {
        dimOverAll[q] = 0;
    }
    it = 0;
    float OverAll = 1;
    while(OverAll != 0)
    {
        OverAll = 0;
        for(int i = 0; i < numberOfAllOverDataPoints; i++)
        {
            referCluster[i] = separatePointsIntoGroups(i);
            //qDebug() << referCluster[i];
        }
        for(int j = 0; j < numberOfClusters; j++)
        {
            for(int f = 0; f < hashKeySize; f++)
            {
                dimOverAll[f] = 0;
            }
            it = 0;
            for(int t = 0; t < numberOfAllOverDataPoints; t++)
            {
                if(referCluster[t] == j)
                {
                    it++;
                    for(int p = 0; p < hashKeySize; p++)
                    {
                       dimOverAll[p] = hash_notClustered[p].at(t) + dimOverAll[p];
                    }
                    //qDebug()<<"X["<<t<<"]: "<<hash_notClustered[0].at(t);
                    //qDebug()<<"Y["<<t<<"]: "<<hash_notClustered[1].at(t);
                    //qDebug()<<"X: "<<xOverAll;
                    //qDebug()<<"Y: "<<yOverAll;
                }
                if(it == 0)
                {
                    QVector<float> Range;
                    for(int y = 0; y < hashKeySize; y++)
                      {
                          Range.push_back(maxDim[y] - minDim[y]);
                          clusterMeanCoordinate[y].replace(j, minDim[y] + float(Range[y] * rand() / (RAND_MAX + 1.0)));
                      }
                }
                if(it != 0)
                {
                    for(int u = 0; u < hashKeySize; u++)
                    {
                        clusterMeanCoordinate[u].replace(j, dimOverAll[u] / it);
                    }
                }
            }
            OverAll = qSqrt((qPow((clusterMeanCoordinate[0].at(j) - prevClusterMeanCoordinate[0].at(j)), 2) + qPow((clusterMeanCoordinate[1].at(j) - prevClusterMeanCoordinate[1].at(j)), 2) + qPow((clusterMeanCoordinate[2].at(j) - prevClusterMeanCoordinate[2].at(j)), 2) + qPow((clusterMeanCoordinate[3].at(j) - prevClusterMeanCoordinate[3].at(j)), 2))) + OverAll;
            for(int o=0; o<hashKeySize; o++)
            {
                prevClusterMeanCoordinate[o].replace(j,clusterMeanCoordinate[o].at(j));
            }
        }
    }
    qDebug() << "Number of itterations is " << it;
    saveClusterMeansToFile();
    saveClusterReferencesToFile(referCluster);
}


void kmean_algorithm::setK(int value)
{
    numberOfClusters = value;
}

int kmean_algorithm::getK()
{
    return numberOfClusters;
}

bool kmean_algorithm::getReadStatus()
{
    return fileIsRead;
}

int kmean_algorithm::getNumberOfIterations()
{
    return it;
}
