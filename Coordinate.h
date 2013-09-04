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

class Coordinate{
public:
    Coordinate();
    void setLabelX(string);
    void setLabelY(string);
    void setLabelCluster(string);
    void setMinCoordinate(float);
    void setMaxCoordinate(float);
    void render_rect(int, int, bool, float, float, float, float);
    void render_vert(float, float, float, int, int);
    void render_hor (float, float, float, int, int);
    void render_label_X(int, int);
    void render_label_Y(int, int);
    void render_text_information(int, int);
    void render_data_points(int, int, QHash<QString, QVector<float> >);
    void renderLabelForPoint(int, int, float, float, float, float);
    //void setRadiusPoint(float);

    void ReadFile(QString);
    void storeOriginalData(QString);

    void normalizeHashElements(QHash<QString, QVector<float> > &qhash);
    void denormalizeHashElements(QHash<QString, QVector<float> > &qhash);

    float getMaxHash(QHash<QString, QVector<float> > qhash1);
    float getMinHash(QHash<QString, QVector<float> > qhash2);
    float getMax(QVector<float> vector);
    float getMin(QVector<float> vector);
    void setSelectionType(int);
    int getSelectionType();
    void selectPoints(int, int, float, float, float, float);
    void getSelectedPoint();
    void setSelectedPointXOriginal();
    float getSelectedPointXOriginal();
    void setSelectedPointYOriginal();
    float getSelectedPointYOriginal();
    void setSelectedPointX();
    float getSelectedPointX();
    void setSelectedPointY();
    float getSelectedPointY();
    bool getPointAlreadySelected();
    void setPointAlreadySelected(bool);
    void setRenderTogle(bool);
    bool getRenderTogle();
    QHash<QString, QVector<float> > getHashOriginal();
    QHash<QString, QVector<float> > getHash();
    void setSelectedPointIndex(int);
    int getSelectedPointIndex();

private:
    Label *x;
    Label *y;
    Label *c;
    CoordinateSystemCoordinates *minCoordinate;
    CoordinateSystemCoordinates *maxCoordinate;
    //float radiusPoint;
    QHash<QString, QVector<float> > hash;
    QHash<QString, QVector<float> > hashOriginal;
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
    int selctedValueIndexRect;
    QVector<int> selectedPointIndexRect;
    bool readfileBool = false;
    float selectedPointXOriginal;
    float selectedPointYOriginal;
    float selectedPointX;
    float selectedPointY;
    bool pointAlreadySelected;
    bool renderTogle;
};

#endif // COORDINATE_H
