
/**
*	@file glwidget.cpp
*	@brief file contains all necessary methods to work with glwidget.
*
*	@author Mikayel Egibyan
*/

#include "glwidget.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start();
}

/**
* This method is used to update the GL mechanically
* @author Mikayel Egibyan
*/
void GLWidget::updateGL_mech()
{
    updateGL();
}

/**
* This method is used to initialize the GL
* @author Mikayel Egibyan
*/
void GLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 0);
}

/**
* This method is used to render everything on the widget
* @author Mikayel Egibyan
*/
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glScalef(QWidget::height(), QWidget::width(), 0);
    coordinateT.render_hor(1, 0, 0, QWidget::width(), QWidget::height());
    coordinateT.render_label_X(QWidget::width(), QWidget::height());
    //qDebug() << width <<"/"<< height;

    coordinateT.render_vert(0, 0, 1, QWidget::width(), QWidget::height());
    coordinateT.render_label_Y(QWidget::width(), QWidget::height());

    coordinateT.render_text_information(QWidget::width(), QWidget::height());
    //coordinateT.setRadiusPoint(5);
    coordinateT.render_data_points(QWidget::width(), QWidget::height());
}

/**
* This method is used to resize the widget
* @author Mikayel Egibyan
*/
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



