/**
*	@file Coordinate.h
*	@brief file contains the definaion of the class Coordinate
*	@author Mikayel Egibyan
*/

#ifndef COORDINATE_H
#define COORDINATE_H
#include "windows.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <QString>
#include "Label.h"
#include "QFileDialog"
#include <QVector>
#include <QDebug>
#include <limits>
#include "CoordinateSystemCoordinates.h"
#include <sstream>
#include <string>

class Coordinate{
public:
    Coordinate();

    void render_rect(int, int, bool, float, float, float, float, float, float);
    void render_vert(float, float, float, int, int);
    void render_hor (float, float, float, int, int);
    void render_label_X(int, int);
    void render_label_Y(int, int);
    void render_text_information(int, int);
    void render_data_points(int, int, QHash<QString, QVector<float> >);
    void render_centroids(int, int);
    void render_newCentroids(int, int);
    void renderLabelForPoint(int, int, float, float, float, float);

    void storeNewClusterCentroids();
    void ReadFile(QString);
    void storeOriginalData(QString);
    void storeClusterCentroids();

    void normalizeHashElements(QHash<QString, QVector<float> > &qhash);
    void denormalizeHashElements(QHash<QString, QVector<float> > &qhash);

    void distFromLine(QHash<QString, QVector<float> >, int, int);
    float calculateHalfSpaces(float, float,float, float, float, float);
    int findNumberOfClusters();

    void setSelectionType(int);
    void selectPoints(int, int, float, float, float, float);
    void selectCentroid(int, int, float, float);
    void selectNewCentroid(int, int, float, float);

    //set
    void setChangedData(QHash<QString, QVector<float> > );
    void setNewCentroidsCreated(bool);
    void setLabelX(string);
    void setLabelY(string);
    void setLabelCluster(string);
    void setMinCoordinate(float);
    void setMaxCoordinate(float);
    void setSelectedPointXOriginal();
    void setSelectedPointYOriginal();
    void setSelectedPointX();
    void setSelectedPointY();
    void setSelectedPointXOriginalCentroid();
    void setSelectedPointYOriginalCentroid();
    void setSelectedPointXCentroid();
    void setSelectedPointYCentroid();
    void setPointAlreadySelected(bool);
    void setCentroidAlreadySelected(bool);
    void setNewCentroidAlreadySelected(bool);
    void setPointsAlreadySelectedRect(bool);
    void setRenderTogle(bool);
    void setSelectedPointIndex(int);
    void setSelectedCentroidIndex(int);
    void setSelectedPointIndexRect(QVector<int>);
    void setCentroidsLoaded(bool);
    void setNewCentroidsLoaded(bool);
    void setDataRendered(bool);  
    void setShowCentroids(bool);
    void setNumberOfIterations(int); 
    void setNumberOfClusters(int);
    void setGotXvalue();
    void setGotYvalue();
    void setlineBeginX(float);
    void setlineBeginY(float);
    void setlineEndX(float);
    void setlineEndY(float);
    void setlineIsDrawn(bool);

    //get
    QHash<QString, QVector<float> > getChangedData();
    bool getNewCentroidsCreated();
    float getMaxHash(QHash<QString, QVector<float> > qhash1);
    float getMinHash(QHash<QString, QVector<float> > qhash2);
    float getMax(QVector<float> vector);
    float getMin(QVector<float> vector);
    int getSelectionType();
    float getSelectedPointXOriginal();
    void getSelectedCendtroid();
    void getSelectedPoint();
    float getSelectedPointYOriginal();
    float getSelectedPointX();
    float getSelectedPointY();
    float getSelectedPointXOriginalCentroid();
    float getSelectedPointYOriginalCentroid();
    float getSelectedPointXCentroid();
    float getSelectedPointYCentroid();
    bool getPointAlreadySelected();
    bool getCentroidAlreadySelected();
    bool getNewCentroidAlreadySelected();
    bool getPointsAlreadySelectedRect();
    bool getRenderTogle();
    QHash<QString, QVector<float> > getHashOriginal();
    QHash<QString, QVector<float> > getHash();
    int getSelectedPointIndex();
    bool getCentroidsLoaded();
    bool getNewCentroidsLoaded();
    int getSelectedCentroidIndex();
    QVector<int> getSelectedPointIndexRect();
    bool getDataRendered();
    bool getShowCentroids();
    int getNumberOfClusterSelectedCentroid();
    int getNumberOfIterations();
    bool getlineIsDrawn();
    float getlineEndY();
    float getlineEndX();
    float getlineBeginY();
    float getlineBeginX();
    string returnGotXvalue();
    string returnGotYvalue();
    bool getFileLoadedStatus();
    int getNumberOfClusters();


private:
    Label *x;
    Label *y;
    Label *c;
    string gotX;
    string gotY;
    CoordinateSystemCoordinates *minCoordinate;
    CoordinateSystemCoordinates *maxCoordinate;
    QHash<QString, QVector<float> > hash;
    QHash<QString, QVector<float> > hashOriginal;
    QHash<QString, QVector<float> > centroids;
    QHash<QString, QVector<float> > newCentroids;
    QHash<QString, QVector<float> > newCentroidsOriginal;
    QHash<QString, QVector<float> > centroidsOriginal;
    QVector<float> valuesVector;
    QStringList list;
    QStringList headerList;
    QString line;
    QString headerLine;
    int listSize;
    float maxAllOver;
    float minAllOver;
    int selectionType;
    bool q;
    int selectedPointIndex;
    int selectedCentroidIndex;
    QVector<int> selectedPointIndexRect;
    bool readfileBool = false;
    float selectedPointXOriginal;
    float selectedPointYOriginal;
    float selectedPointX;
    float selectedPointY;
    float selectedPointXOriginalCentroid;
    float selectedPointYOriginalCentroid;
    float selectedPointXCentroid;
    float selectedPointYCentroid;
    bool pointAlreadySelected;
    bool centroidAlreadySelected;
    bool newcentroidAlreadySelected;
    bool pointsAlreadySelectedRect;
    bool renderTogle;
    bool centroidsLoaded = false;
    bool newCentroidsLoaded = false;
    bool dataIsRendered = false;
    bool showCentroids = false;
    bool renderCent;
    int clusterNumber;
    int numberOfiterations;
    int numberOfClusters;
    float lineBeginX;
    float lineBeginY;
    float lineEndX;
    float lineEndY;
    bool lineIsDrawn = false;
    bool newCentroidsConstructed = false;
    QHash<QString, QVector<float> > changedData;
};

#endif // COORDINATE_H
