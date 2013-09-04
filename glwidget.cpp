/**
*	@file glwidget.cpp
*	@brief file contains all necessary methods to work with glwidget
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
    getQ();
    getCurrentX();
    getCurrentY();
    getPushedX();
    getPushedY();
    getReleasedX();
    getReleasedY();
}

/**
* This method is used to update the GL mechanically
* @author Mikayel Egibyan
*/
void GLWidget::updateGL_mech()
{
    updateGL();
    qDebug() << QWidget::width();
    qDebug() << getNormalizedWidth(200);
    qDebug() << selectedPointX << selectedPointY;
}

float GLWidget::getNormalizedWidth(int value)
{
    float a = (float)value;
    float min = 0;
    float max = 1;
    return (a/(QWidget::width()))*(max-min) + min;
}

float GLWidget::getNormalizedHeight(int value)
{
    float a = (float)value;
    float min = 0;
    float max = 1;
    return (a/(QWidget::height()))*(max-min) + min;
}

float GLWidget::rndup(float n)
{
    return floor(n*10000+0.5)/10000;
}

void GLWidget::setQ(bool value)
{
    q = value;
}

bool GLWidget::getQ()
{
    return q;
}

void GLWidget::setPushedX(float value)
{
    pushedX = value;
}

float GLWidget::getPushedX()
{
    return pushedX;
}

void GLWidget::setPushedY(float value)
{
    pushedY = value;
}

float GLWidget::getPushedY()
{
    return pushedY;
}

void GLWidget::setCurrentX(float value)
{
    currentX = value;
}

float GLWidget::getCurrentX()
{
    return currentX;
}

void GLWidget::setCurrentY(float value)
{
    currentY = value;
}

float GLWidget::getCurrentY()
{
    return currentY;
}

void GLWidget::setReleasedX(float value)
{
    releasedX = value;
}

float GLWidget::getReleasedX()
{
    return releasedX;
}

void GLWidget::setReleasedY(float value)
{
     releasedY = value;
}

float GLWidget::getReleasedY()
{
    return releasedY;
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
    coordinateT.render_hor(1, 0, 0, QWidget::width(), QWidget::height());
    coordinateT.render_label_X(QWidget::width(), QWidget::height());
    coordinateT.render_vert(0, 0, 1, QWidget::width(), QWidget::height());
    coordinateT.render_label_Y(QWidget::width(), QWidget::height());
    coordinateT.render_text_information(QWidget::width(), QWidget::height());
    if(coordinateT.getRenderTogle())
    {
        coordinateT.render_data_points(QWidget::width(), QWidget::height(), getHashToRender());
    }
    coordinateT.render_rect(QWidget::width(), QWidget::height(), q, pushedX, pushedY, currentX, currentY);
    coordinateT.selectPoints(QWidget::width(), QWidget::height(), pushedX, pushedY, releasedX, releasedY);
    coordinateT.renderLabelForPoint(QWidget::width(), QWidget::height(), coordinateT.getSelectedPointX(), coordinateT.getSelectedPointY(), coordinateT.getSelectedPointXOriginal(), coordinateT.getSelectedPointYOriginal());
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


void GLWidget::setHashToRender(QHash<QString, QVector<float> > hash)
{
    hashToRender = hash;
}

QHash<QString, QVector<float> > GLWidget::getHashToRender()
{
    return hashToRender;
}



