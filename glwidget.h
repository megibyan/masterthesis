/**
*	@file glwidget.h
*	@brief file contains the definaion of the class glwidget
*	@author Mikayel Egibyan
*/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QtMath>
#include <QDebug>
#include <QGroupBox>
#include <GL/glu.h>
#include <mainwindow.h>
#include "Coordinate.h"
#include "Scene.h"
#include "CoordinateSystemCoordinates.h"
#include "kmean_algorithm.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void updateGL_mech();
    float getNormalizedWidth(int);
    float getNormalizedHeight(int);
    float rndup(float n);
    Coordinate coordinateT;
    kmean_algorithm kmean;
    void setQ(bool);
    bool getQ();
    void setPushedX(float);
    float getPushedX();
    void setPushedY(float);
    float getPushedY();
    void setCurrentX(float);
    float getCurrentX();
    void setCurrentY(float);
    float getCurrentY();
    void setReleasedX(float);
    float getReleasedX();
    void setReleasedY(float);
    float getReleasedY();
    void setHashToRender(QHash<QString, QVector<float> >);
    QHash<QString, QVector<float> > getHashToRender();
    int getNumberOfIteration();
    void setNumberOfIteration(int);

private:
    bool q;
    CoordinateSystemCoordinates maxCoordinate;
    CoordinateSystemCoordinates minCoordinate;
    QTimer timer;
    float pushedX;
    float pushedY;
    float currentX;
    float currentY;
    float releasedX;
    float releasedY;
    float selectedPointX;
    float selectedPointY;
    int numberOfiterations;
    QHash<QString, QVector<float> > hashToRender;
};

#endif // GLWIDGET_H
