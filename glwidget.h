/**
*	@file glwidget.h
*	@brief file contains the definaion of the class glwidget.
*
*	@author Mikayel Egibyan
*/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QGroupBox>
#include <mainwindow.h>
#include "Coordinate.h"
#include "Scene.h"
#include <QDebug>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void updateGL_mech();
    Coordinate coordinateT;
private:
    QTimer timer;
    float eye_x;
    float eye_y;
    float eye_z;
    int width;
    int height;
};

#endif // GLWIDGET_H
