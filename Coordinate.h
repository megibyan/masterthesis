/**
*	@file Coordinate.h
*	@brief file contains the definaion of the class Coordinate.
*
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

class Coordinate{
public:
    Coordinate();
    void setLabelX(string);
    void setLabelY(string);
    void setLabelCluster(string);
    void setMinCoordinate(float);
    void setMaxCoordinate(float);
    void render_vert(float, float, float, int, int);
    void render_hor (float, float, float, int, int);
    void render_label_X(int, int);
    void render_label_Y(int, int);
    void render_text_information(int, int);
    void render_data_points(int, int);
    //void setRadiusPoint(float);
    void ReadFile(QString);
    void normalizeHashElements(QHash<QString, QVector<float> > &qhash);
    float getMaxHash(QHash<QString, QVector<float> > qhash1);
    float getMinHash(QHash<QString, QVector<float> > qhash2);
    float getMax(QVector<float> vector);
    float getMin(QVector<float> vector);
private:
    Label *x;
    Label *y;
    Label *c;
    CoordinateSystemCoordinates *minCoordinate;
    CoordinateSystemCoordinates *maxCoordinate;
    //float radiusPoint;
    QHash<QString, QVector<float> > hash;
    QHash<QString, QVector<float> > hash_normalized;
    QVector<float> valuesVector;
    QStringList list;
    QStringList headerList;
    QString line;
    QString headerLine;
    int listSize;
    float maxAllOver;
    float minAllOver;
};

#endif // COORDINATE_H
