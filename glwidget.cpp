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
    //coordinateT.setNumberOfIterations(kmean.getNumberOfIterations());
}

/**
* This method is used to normalize the width
* @author Mikayel Egibyan
*/
float GLWidget::getNormalizedWidth(int value)
{
    float a = (float)value;
    float min = 0;
    float max = 1;
    return (a/(QWidget::width()))*(max-min) + min;
}

/**
* This method is used to normalize the height
* @author Mikayel Egibyan
*/
float GLWidget::getNormalizedHeight(int value)
{
    float a = (float)value;
    float min = 0;
    float max = 1;
    return (a/(QWidget::height()))*(max-min) + min;
}

/**
* This method is used to round up a float number
* @author Mikayel Egibyan
*/
float GLWidget::rndup(float n)
{
    return floor(n*10000+0.5)/10000;
}

/**
* This method is used set rendering togle
* @author Mikayel Egibyan
*/
void GLWidget::setQ(bool value)
{
    q = value;
}

/**
* This method is used get rendering togle
* @author Mikayel Egibyan
*/
bool GLWidget::getQ()
{
    return q;
}

/**
* This method is used set the mouse press coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setPushedX(float value)
{
    pushedX = value;
}

/**
* This method is used get the mouse press coordinate
* @author Mikayel Egibyan
*/
float GLWidget::getPushedX()
{
    return pushedX;
}

/**
* This method is used set the mouse press coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setPushedY(float value)
{
    pushedY = value;
}

/**
* This method is used get the mouse press coordinate
* @author Mikayel Egibyan
*/
float GLWidget::getPushedY()
{
    return pushedY;
}

/**
* This method is used set the mouse current coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setCurrentX(float value)
{
    currentX = value;
}

/**
* This method is used get the mouse current coordinate
* @author Mikayel Egibyan
*/
float GLWidget::getCurrentX()
{
    return currentX;
}

/**
* This method is used set the mouse current coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setCurrentY(float value)
{
    currentY = value;
}

/**
* This method is used get the mouse current coordinate
* @author Mikayel Egibyan
*/
float GLWidget::getCurrentY()
{
    return currentY;
}

/**
* This method is used set the mouse release coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setReleasedX(float value)
{
    releasedX = value;
}

/**
* This method is used get the mouse release coordinate
* @author Mikayel Egibyan
*/
float GLWidget::getReleasedX()
{
    return releasedX;
}

/**
* This method is used set the mouse release coordinate
* @author Mikayel Egibyan
*/
void GLWidget::setReleasedY(float value)
{
     releasedY = value;
}

/**
* This method is used gset the mouse release coordinate
* @author Mikayel Egibyan
*/
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
        coordinateT.render_centroids(QWidget::width(), QWidget::height());
    }
    coordinateT.render_rect(QWidget::width(), QWidget::height(), q, pushedX, pushedY, currentX, currentY);
    coordinateT.selectPoints(QWidget::width(), QWidget::height(), pushedX, pushedY, releasedX, releasedY);
    coordinateT.selectCentroid(QWidget::width(), QWidget::height(), pushedX, pushedY);
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

/**
* This method is used set the number of iterations
* @author Mikayel Egibyan
*/
void GLWidget::setNumberOfIteration(int value)
{
    numberOfiterations = value;
}

/**
* This method is used get the number of iterations
* @author Mikayel Egibyan
*/
int GLWidget::getNumberOfIteration()
{
    return numberOfiterations;
}

/**
* This method is used set the data that must be rendered
* @author Mikayel Egibyan
*/
void GLWidget::setHashToRender(QHash<QString, QVector<float> > hash)
{
    hashToRender = hash;
}

/**
* This method is used get the data that must be rendered
* @author Mikayel Egibyan
*/
QHash<QString, QVector<float> > GLWidget::getHashToRender()
{
    return hashToRender;
}
