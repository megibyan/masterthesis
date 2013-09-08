/**
*	@file Coordinate.cpp
*	@brief file contains all necessary methods to coordinate the scene.
*   @brief file also contains some render information
*	@author Mikayel Egibyan
*/

#include <QMessageBox>
#include "Coordinate.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
Coordinate::Coordinate()
{
    x = new Label("X");
    y = new Label("Y");
    c = new Label;
    minCoordinate = new CoordinateSystemCoordinates(0.01);
    maxCoordinate = new CoordinateSystemCoordinates(0.99);
    getSelectionType();
}

/**
* This method is used to set the minimal coordinate
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setMinCoordinate(float value)
{
    this->minCoordinate->setValue(value);
}

/**
* This method is used to set the maximal coordinate
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setMaxCoordinate(float value)
{
    this->maxCoordinate->setValue(value);
}

/**
* This method is used to set a label to horizontal axis
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setLabelX(string value)
{
    this->x->setValue(value);
}

/**
* This method is used to set a label to vertical axis
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setLabelY(string value)
{
    this->y->setValue(value);
}

/**
* This method is used to set a label to clusters
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setLabelCluster(string value)
{
    this->c->setValue(value);
}

/**
* This method is used to set selection type of points
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setSelectionType(int value)
{
    selectionType = value;
}

/**
* This method is used to get selection type of points
* @author Mikayel Egibyan
*/
int Coordinate::getSelectionType()
{
    return selectionType;
}

/**
* This method is used to get true if a point is selected
* @author Mikayel Egibyan
*/
bool Coordinate::getPointAlreadySelected()
{
    return pointAlreadySelected;
}

/**
* This method is used to set true if the points are selected
* @author Mikayel Egibyan
*/
void Coordinate::setPointAlreadySelected(bool value)
{
    pointAlreadySelected = value;
}

/**
* This method is used to get true if a centroid is selected
* @author Mikayel Egibyan
*/
bool Coordinate::getCentroidAlreadySelected()
{
    return centroidAlreadySelected;
}

/**
* This method is used to set true if a centroid is selected
* @author Mikayel Egibyan
*/
void Coordinate::setCentroidAlreadySelected(bool value)
{
    centroidAlreadySelected = value;
}

/**
* This method is used to get true if the points are selected
* @author Mikayel Egibyan
*/
bool Coordinate::getPointsAlreadySelectedRect()
{
    return pointsAlreadySelectedRect;
}

/**
* This method is used to set true if a points is selected
* @author Mikayel Egibyan
*/
void Coordinate::setPointsAlreadySelectedRect(bool value)
{
    pointsAlreadySelectedRect = value;
}

/**
* This method is used to render line, rectangle and point
* @author Mikayel Egibyan
* @param a,b - scale parameters, t - render or not, pushed* - mouse click position, current* - mouse current position
*/
void Coordinate::render_rect(int a, int b, bool t, float pushedX, float pushedY, float currentX, float currentY)
{
    string horValue = "Dim_" + x->getValue();
    string vertValue = "Dim_" + y->getValue();
    QString horV = QString::fromStdString(horValue);
    QString vertV = QString::fromStdString(vertValue);
    QHash<QString, QVector<float> >::iterator it;

    if(selectionType == 1)
    {
        if(t)
        {
            q = true;
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0, 0, 1, 0.1);
            glScalef(a, b, 0);
            glRectf(pushedX, pushedY, currentX, currentY);
            glFlush();
            glDisable(GL_BLEND);
            glPopMatrix();
            setlineIsDrawn(false);
        }
    }
    if(selectionType == 0)
    {
        if(t)
        {
            q = false;
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1, 0, 0, 0.1);
            glScalef(a, b, 0);
            glBegin(GL_LINES);
            glVertex2f(pushedX, pushedY);
            glVertex2f(currentX, currentY);
            glEnd();
            glFlush();
            glDisable(GL_BLEND);
            glPopMatrix();
            setlineBeginX(pushedX);
            setlineBeginY(pushedY);
            setlineEndX(currentX);
            setlineEndY(currentY);
            setlineIsDrawn(true);
        }
    }
    if(selectionType == 2)
    {
        if(t)
        {
            q = true;
            setlineIsDrawn(false);
        }
    }
}

/**
* This method is used to render the vertical axis
* @author Mikayel Egibyan
*/
void Coordinate::render_vert(float red_vert, float green_vert, float blue_vert, int a, int b)
{
    glPushMatrix();
    glColor3f(red_vert, green_vert, blue_vert);
    glScalef(a, b, 0);
    glBegin(GL_LINES);
        //y
        glVertex2f(0.01, 0.01);
        glVertex2f(0.01, 0.99);
        //y arrow
        glVertex2f(0.01, 0.99);
        glVertex2f(0.005, 0.985);

        glVertex2f(0.01, 0.99);
        glVertex2f(0.015, 0.985);
    glEnd();
    glFlush();
    glPopMatrix();
}

/**
* This method is used to render the horizontal axis
* @author Mikayel Egibyan
*/
void Coordinate::render_hor(float red_hor, float green_hor, float blue_hor, int a, int b)
{
    glPushMatrix();
    glColor3f(red_hor, green_hor, blue_hor);
    glScalef(a, b, 0);
    //glTranslatef(-20, -15, 0);

    glBegin(GL_LINES);
        //x
        glVertex2f(0.01, 0.01);
        glVertex2f(0.99, 0.01);
        //x arrow
        glVertex2f(0.99, 0.01);
        glVertex2f(0.985, 0.005);

        glVertex2f(0.99, 0.01);
        glVertex2f(0.985, 0.015);
    glEnd();
    glFlush();
    glPopMatrix();
}

/**
* This method is used to render the label for horizontal axis
* @author Mikayel Egibyan
*/
void Coordinate::render_label_X(int a, int b)
{
    glPushMatrix();
    glColor3f(0, 0, 0);
    //glTranslatef(-20, -15, 0);
    glScalef(a, b, 0);
    //glRasterPos2f(0, 0);
    glRasterPos2f(0.991, 0.01);

    const char * label = x->getValue().c_str();
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) label);
    glFlush();
    glPopMatrix();
}

/**
* This method is used to render the label for vertical axis
* @author Mikayel Egibyan
*/
void Coordinate::render_label_Y(int a, int b)
{
    glPushMatrix();
    glColor3f(0, 0, 0);
    glScalef(a, b, 0);
    glRasterPos2f(0.01, 0.991);

    const char * label = y->getValue().c_str();
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) label);
    glFlush();
    glPopMatrix();
}

/**
* This method is used to render some text information on the widget
* @author Mikayel Egibyan
*/
void Coordinate::render_text_information(int a, int b)
{
    glPushMatrix();
    glColor3f(1, 0, 0);
    glScalef(a, b, 0);
    glRasterPos2f(0.78, 0.98);
    const char * labelx = x->getValue().c_str();
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) "Horizontal axis - ");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) labelx);

    glRasterPos2f(0.78, 0.96);
    const char * labely = y->getValue().c_str();
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) "Vertical axis   - ");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) labely);

    glRasterPos2f(0.78, 0.94);

    const char *cluster = c->getValue().c_str();
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) "Number of clusters - ");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) cluster);

    glRasterPos2f(0.78, 0.92);
    int iter = getNumberOfIterations();
    stringstream ss;
    ss << iter;
    string str = ss.str();
    const char *iterations = str.c_str();
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) "Number of iterations - ");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char *) iterations);

    glPopMatrix();
}

/**
* This method is used to celect centroid
* @author Mikayel Egibyan
* @param a,b - scale parameters, pushed* - mouse click position
*/
void Coordinate::selectCentroid(int a, int b, float pushedX, float pushedY)
{
    string horValue = "Dim_" + x->getValue();
    string vertValue = "Dim_" + y->getValue();
    QString horV = QString::fromStdString(horValue);
    QString vertV = QString::fromStdString(vertValue);
    QHash<QString, QVector<float> >::iterator it;
    QHash<QString, QVector<float> >::iterator itt;
    if(q)
    {
        if(selectionType == 2)
        {
            float epsilion = 0.01;
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glPointSize(10);
            glColor4f(1, 0, 0, 0.1);
            glScalef(a, b, 0);
            glBegin(GL_POINTS);
            for (it = centroids.begin(); it != centroids.end(); it++)
            {
                for (int j=0; j<it.value().size(); j++)
                {
                    if(centroids[horV].value(j) >= pushedX && centroids[vertV].value(j) >=pushedY)
                    {
                        if(centroids[horV].value(j) <= pushedX + epsilion  && centroids[vertV].value(j) <=pushedY + epsilion)
                        {
                            glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                            setSelectedCentroidIndex(j);
                            setSelectedPointXOriginal();
                            setSelectedPointYOriginal();
                            setSelectedPointX();
                            setSelectedPointY();
                            setCentroidAlreadySelected(true);
                            setPointAlreadySelected(false);
                            setPointsAlreadySelectedRect(false);
                            clusterNumber = int(centroids["Cluster"].value(j));
                            for (itt = hash.begin(); itt != hash.end(); itt++)
                            {
                                for (int r=0; r<itt.value().size(); r++)
                                {
                                    if(hash["Cluster"].value(r) == clusterNumber)
                                    {
                                        glBegin(GL_POINTS);
                                        glVertex2f(hash[horV].value(r), hash[vertV].value(r));
                                        glEnd();
                                    }
                                }
                            }
                            glEnd();
                        }
                    }
                    if(centroids[horV].value(j) <= pushedX && centroids[vertV].value(j) <=pushedY)
                    {
                        if(centroids[horV].value(j) >= pushedX + epsilion  && centroids[vertV].value(j) >=pushedY + epsilion)
                        {
                            glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                            setSelectedCentroidIndex(j);
                            setSelectedPointXOriginal();
                            setSelectedPointYOriginal();
                            setSelectedPointX();
                            setSelectedPointY();
                            setCentroidAlreadySelected(true);
                            setPointAlreadySelected(false);
                            setPointsAlreadySelectedRect(false);
                            clusterNumber = int(centroids["Cluster"].value(j));
                            for (itt = hash.begin(); itt != hash.end(); itt++)
                            {
                                for (int r=0; r<itt.value().size(); r++)
                                {
                                    if(hash["Cluster"].value(r) == clusterNumber)
                                    {
                                        glBegin(GL_POINTS);
                                        glVertex2f(hash[horV].value(r), hash[vertV].value(r));
                                        glEnd();
                                    }
                                }
                            }
                            glEnd();
                        }
                    }
                }
            }

            glEnd();
            glFlush();
            glDisable(GL_BLEND);
            glPopMatrix();
        }
    }
}

/**
* This method is used to find the number of clusters from the file
* @author Mikayel Egibyan
*/
int Coordinate::findNumberOfClusters()
{
    setNumberOfClusters(getMax(hashOriginal["Cluster"]));
    return getNumberOfClusters();
}

/**
* This method is used to set the got number of clusters
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setNumberOfClusters(int value)
{
    numberOfClusters = value;
}

/**
* This method is used to get number of clusters
* @author Mikayel Egibyan
*/
int Coordinate::getNumberOfClusters()
{
    return numberOfClusters;
}

/**
* This method is used to get the number of iterations
* @author Mikayel Egibyan
*/
int Coordinate::getNumberOfIterations()
{
    return numberOfiterations;
}

/**
* This method is used to set the number of iterations
* @author Mikayel Egibyan
* @param value
*/
void Coordinate::setNumberOfIterations(int value)
{
    numberOfiterations = value;
}

/**
* This method is used to get the reference cluster of selected point
* @author Mikayel Egibyan
*/
int Coordinate::getNumberOfClusterSelectedCentroid()
{
    return clusterNumber;
}

/**
* This method is used to visualize the selection of point, points and centroid
* @author Mikayel Egibyan
* @param a,b - scale parameters, pushed* - mouse click position, released* - mouse release position
*/
void Coordinate::selectPoints(int a, int b, float pushedX, float pushedY, float releasedX, float releasedY)
{
    string horValue = "Dim_" + x->getValue();
    string vertValue = "Dim_" + y->getValue();
    QString horV = QString::fromStdString(horValue);
    QString vertV = QString::fromStdString(vertValue);
    QHash<QString, QVector<float> >::iterator it;

    if(q)
    {
        if(selectionType == 2)
        {
            float epsilion = 0.01;
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glPointSize(10);
            glColor4f(1, 0, 0, 0.1);
            glScalef(a, b, 0);
            glBegin(GL_POINTS);
            for (it = hash.begin(); it != hash.end(); it++)
            {
                for (int j=0; j<it.value().size(); j++)
                {
                    if(hash[horV].value(j) >= pushedX && hash[vertV].value(j) >=pushedY)
                    {
                        if(hash[horV].value(j) <= pushedX + epsilion  && hash[vertV].value(j) <=pushedY + epsilion)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            setSelectedPointIndex(j);
                            setSelectedPointXOriginal();
                            setSelectedPointYOriginal();
                            setSelectedPointX();
                            setSelectedPointY();
                            setPointAlreadySelected(true);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(false);
                        }
                    }
                    if(hash[horV].value(j) <= pushedX && hash[vertV].value(j) <=pushedY)
                    {
                        if(hash[horV].value(j) >= pushedX + epsilion  && hash[vertV].value(j) >=pushedY + epsilion)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            setSelectedPointIndex(j);
                            setSelectedPointXOriginal();
                            setSelectedPointYOriginal();
                            setSelectedPointX();
                            setSelectedPointY();
                            setPointAlreadySelected(true);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(false);
                        }
                    }
                }
            }
            glEnd();
            glFlush();
            glDisable(GL_BLEND);
            glPopMatrix();
        }

        if(selectionType == 1)
        {
            selectedPointIndex = 0;
            glPushMatrix();
            //normalizeHashElements(hash);
            glEnable(GL_BLEND);
            glPointSize(10);
            glColor4f(0, 0, 1, 0.1);
            glScalef(a, b, 0);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_POINTS);
            selectedPointIndexRect.clear();
            for (it = hash.begin(); it != hash.end(); it++)
            {
                for (int j=0; j<it.value().size(); j++)
                {
                    if(hash[horV].value(j) >= pushedX && hash[vertV].value(j) >=pushedY)
                    {
                        if(hash[horV].value(j) <= releasedX && hash[vertV].value(j) <=releasedY)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            selectedPointIndexRect.push_back(j);
                            setPointAlreadySelected(false);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(true);
                        }
                    }
                    if(hash[horV].value(j) <= pushedX && hash[vertV].value(j) <=pushedY)
                    {
                        if(hash[horV].value(j) >= releasedX && hash[vertV].value(j) >=releasedY)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            selectedPointIndexRect.push_back(j);
                            setPointAlreadySelected(false);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(true);
                        }
                    }
                    if(hash[horV].value(j) <= pushedX && hash[vertV].value(j) >=pushedY)
                    {
                        if(hash[horV].value(j) >= releasedX && hash[vertV].value(j) <=releasedY)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            selectedPointIndexRect.push_back(j);
                            setPointAlreadySelected(false);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(true);
                        }
                    }
                    if(hash[horV].value(j) >= pushedX && hash[vertV].value(j) <=pushedY)
                    {
                        if(hash[horV].value(j) <= releasedX && hash[vertV].value(j) >=releasedY)
                        {
                            glVertex2f(hash[horV].value(j), hash[vertV].value(j));
                            selectedPointIndexRect.push_back(j);
                            setPointAlreadySelected(false);
                            setCentroidAlreadySelected(false);
                            setPointsAlreadySelectedRect(true);
                        }
                    }
                }
            }
            setSelectedPointIndexRect(selectedPointIndexRect);
            //for(int z=0; z<selectedPointIndexRect.size(); z++)
            //    qDebug() << selectedPointIndexRect.value(z);
            glEnd();
            glFlush();
            glDisable(GL_BLEND);
            glPopMatrix();
        }
    }
}

/**
* This method is used to visualize the centroids
* @author Mikayel Egibyan
* @param a,b - scale parameters
*/
void Coordinate::render_centroids(int a, int b)
{
    if(getShowCentroids())
    {
        string horValue = "Dim_" + x->getValue();
        string vertValue = "Dim_" + y->getValue();
        QString horV = QString::fromStdString(horValue);
        QString vertV = QString::fromStdString(vertValue);
        QHash<QString, QVector<float> >::iterator it;

        glPushMatrix();
        glPointSize(7);
        glScalef(a, b, 0);

        for (it = centroids.begin(); it != centroids.end(); ++it)
        {
            for (int j=0; j<it.value().size(); j++)
            {
                if(centroids["Cluster"].value(j) == 1)
                {
                    glColor3f(0.2, 0.2, 0.2);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();

                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();

                    stringstream xx;
                    xx << centroidsOriginal[horV].value(j);
                    string coordsS = xx.str();
                    const char *coords = coordsS.c_str();

                    stringstream yy;
                    yy << centroidsOriginal[vertV].value(j);
                    string coordsSS = yy.str();
                    const char *coordss = coordsSS.c_str();

                    string delimiter = " / ";
                    const char * delimiterChar = delimiter.c_str();

                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                    glRasterPos2f(centroids[horV].value(j) - 0.03, centroids[vertV].value(j) + 0.01);
                    //glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) coords);
                    //glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) delimiterChar);
                    //glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) coordss);
                }
                if(centroids["Cluster"].value(j) == 2)
                {

                    glColor3f(0.5, 0.5, 0.5);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();
                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();
                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                }
                if(centroids["Cluster"].value(j) == 3)
                {
                    glColor3f(0.8, 0.8, 0.8);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();
                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();
                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                }
                if(centroids["Cluster"].value(j) == 4)
                {
                    glColor3f(0.3, 0.3, 0.3);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();
                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();
                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                }
                if(centroids["Cluster"].value(j) == 5)
                {
                    glColor3f(0.6, 0.6, 0.6);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();
                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();
                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                }
                if(centroids["Cluster"].value(j) == 6)
                {
                    glColor3f(0.7, 0.7, 0.7);
                    glBegin(GL_POINTS);
                    glVertex2f(centroids[horV].value(j), centroids[vertV].value(j));
                    glEnd();
                    stringstream ss;
                    ss << centroids["Cluster"].value(j);
                    string str = ss.str();
                    const char *clusterLabel = str.c_str();
                    glRasterPos2f(centroids[horV].value(j), centroids[vertV].value(j) - 0.02);
                    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) clusterLabel);
                }
            }
        }

        glEnd();
        glFlush();
        glPopMatrix();
    }
}

/**
 * This method is used to render the data points got from the .csv file
 * @author Mikayel Egibyan
 */
void Coordinate::render_data_points(int a, int b, QHash<QString, QVector<float> > h )
{
    string horValue = "Dim_" + x->getValue();
    string vertValue = "Dim_" + y->getValue();
    QString horV = QString::fromStdString(horValue);
    QString vertV = QString::fromStdString(vertValue);
    QHash<QString, QVector<float> >::iterator it;

    glPushMatrix();
    normalizeHashElements(h);
    glPointSize(5);
    glColor3f(0, 1, 0);
    glScalef(a, b, 0);
    glBegin(GL_POINTS);

    for (it = h.begin(); it != h.end(); ++it)
    {
        for (int j=0; j<it.value().size(); j++)
        {

            if(h["Cluster"].value(j) == 1)
            {
                glColor3f(0, 1, 0);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
            if(h["Cluster"].value(j) == 2)
            {
                glColor3f(1, 0, 0);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
            if(h["Cluster"].value(j) == 3)
            {
                glColor3f(0, 0, 1);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
            if(h["Cluster"].value(j) == 4)
            {
                glColor3f(0, 1, 1);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
            if(h["Cluster"].value(j) == 5)
            {
                glColor3f(0, 0, 0);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
            if(h["Cluster"].value(j) == 6)
            {
                glColor3f(1, 1, 0);
                glVertex2f(h[horV].value(j), h[vertV].value(j));
            }
        }
    }

    glEnd();
    glFlush();
    glPopMatrix();
    setDataRendered(true);
}

/**
 * This method is used to get the start coordinate where the line rendering starts
 * @author Mikayel Egibyan
 */
float Coordinate::getlineBeginX()
{
    return lineBeginX;
}

/**
 * This method is used to set the start coordinate where the line rendering starts
 * @author Mikayel Egibyan
 * @param value
 */
void Coordinate::setlineBeginX(float value)
{
    lineBeginX = value;
}

/**
 * This method is used to get the start coordinate where the line rendering starts
 * @author Mikayel Egibyan
 */
float Coordinate::getlineBeginY()
{
    return lineBeginY;
}

/**
 * This method is used to set the start coordinate where the line rendering starts
 * @author Mikayel Egibyan
 * @param value
 */
void Coordinate::setlineBeginY(float value)
{
    lineBeginY = value;
}

/**
 * This method is used to get the end coordinate where the line rendering starts
 * @author Mikayel Egibyan
 */
float Coordinate::getlineEndX()
{
    return lineEndX;
}

/**
 * This method is used to set the end coordinate where the line rendering starts
 * @author Mikayel Egibyan
 * @param value
 */
void Coordinate::setlineEndX(float value)
{
    lineEndX = value;
}

/**
 * This method is used to get the end coordinate where the line rendering starts
 * @author Mikayel Egibyan
 */
float Coordinate::getlineEndY()
{
    return lineEndY;
}

/**
 * This method is used to set the end coordinate where the line rendering starts
 * @author Mikayel Egibyan
 * @param value
 */
void Coordinate::setlineEndY(float value)
{
    lineEndY = value;
}

/**
 * This method is used to get the returned value of coordinate
 * @author Mikayel Egibyan
 */
string Coordinate::returnGotXvalue()
{
    return gotX;
}

/**
 * This method is used to get the returned value of coordinate
 * @author Mikayel Egibyan
 */
string Coordinate::returnGotYvalue()
{
    return gotY;
}

/**
 * This method is used to get if the line is rendered
 * @author Mikayel Egibyan
 */
bool Coordinate::getlineIsDrawn()
{
    return lineIsDrawn;
}

/**
 * This method is used to set if the line is rendered
 * @author Mikayel Egibyan
 * @param value
 */
void Coordinate::setlineIsDrawn(bool value)
{
    lineIsDrawn = value;
}

/**
 * This method is used to set the coordinate of coordinate
 * @author Mikayel Egibyan
 */
void Coordinate::setGotXvalue()
{
    gotX = x->getValue();
}

/**
 * This method is used to set the coordinate of coordinate
 * @author Mikayel Egibyan
 */
void Coordinate::setGotYvalue()
{
    gotY = y->getValue();
}

/**
 * This method is used to get if the file is read
 * @author Mikayel Egibyan
 */
bool Coordinate::getFileLoadedStatus()
{
    return readfileBool;
}

/**
 * This method is used to read already clustered data from a .csv file
 * @author Mikayel Egibyan
 * @param filename
 **/
void Coordinate::ReadFile(QString filename)
{
    QFile file(filename);
    //QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\sample.csv");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
    else
    {
        readfileBool = true;
        headerLine = file.readLine().trimmed();
        headerList = headerLine.split(',');
        listSize = headerList.size();
        for(int t=0; t<listSize; t++)
        {
            QVector<float> vec;
            hash[headerList[t]] = vec;
        }
        while(!file.atEnd())
        {
            line = file.readLine();
            list = line.split(',');
            for(int j=0; j<listSize; j++)
            {
                hash[headerList[j]].push_back(list[j].toFloat());
            }
        }
        hashOriginal = hash;
        normalizeHashElements(hash);
        storeClusterCentroids();
        /*QHashIterator<QString, QVector<float> > i(hash);
            while (i.hasNext())
            {
                i.next();
                qDebug() << i.key() << ":" << i.value();
            }*/
    }
}

/**
 * This method is used to read already clustered data centroids from a .csv file
 * @author Mikayel Egibyan
 **/
void Coordinate::storeClusterCentroids()
{
    if(readfileBool)
    {
        QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ClusterMeans.csv");
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(0, "Error", "No file with clusers' mean information found.");
        }
        QString headerLineCentroid = file.readLine().trimmed();
        QStringList headerListCentroid = headerLineCentroid.split(',');
        int listSizeCenroid = headerListCentroid.size();
        for(int t=0; t<listSizeCenroid; t++)
        {
            QVector<float> vec;
            centroids[headerListCentroid[t]] = vec;
        }
        while(!file.atEnd())
        {
            QString lineCentroid = file.readLine();
            QStringList listCentroid = lineCentroid.split(',');
            for(int j=0; j<listSizeCenroid; j++)
            {
                centroids[headerListCentroid[j]].push_back(listCentroid[j].toFloat());
            }
        }
        centroidsOriginal = centroids;
        //normalizeHashElements(centroids);
        float new_value;
        float old_value;
        string header_name_string = "Cluster";
        const char *header_name_constChar = header_name_string.c_str();
        float min = getMinHash(hashOriginal);
        float max = getMaxHash(hashOriginal);
        float a = maxCoordinate->getValue();
        float b = minCoordinate->getValue();
        QHash<QString, QVector<float> >::iterator it;
        for (it = centroids.begin(); it != centroids.end(); it++)
        {
            if (it.key() != header_name_constChar)
           {
              for (int j=0; j<it.value().size(); j++)
              {
                 old_value = it.value().at(j);
                 new_value = (old_value-min)/(max-min)*(a-b) + b;
                 it.value().replace(j, new_value);
              }
           }
        }
        setCentroidsLoaded(true);
    }
}

/**
 * This method is used to store not normailized data
 * @author Mikayel Egibyan
 * @param filename
 **/
void Coordinate::storeOriginalData(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
    QString headerLineOriginal = file.readLine().trimmed();
    QStringList headerListOriginal = headerLineOriginal.split(',');
    int listSizeOriginal = headerListOriginal.size();
    for(int t=0; t<listSizeOriginal; t++)
    {
        QVector<float> vec;
        hashOriginal[headerListOriginal[t]] = vec;
    }
    while(!file.atEnd())
    {
        QString lineOriginal = file.readLine();
        QStringList listOriginal = lineOriginal.split(',');
        for(int j=0; j<listSizeOriginal; j++)
        {
            hashOriginal[headerListOriginal[j]].push_back(listOriginal[j].toFloat());
        }
    }
}

/**
 * This method is used to normalize the values to local coordinate system
 * @author Mikayel Egibyan
 * @param qhash The qhash is QHash<QString, QVector<float> > QHash
 **/
void Coordinate::normalizeHashElements(QHash<QString, QVector<float> > &qhash)
{
    float new_value;
    float old_value;
    string header_name_string = "Cluster";
    const char *header_name_constChar = header_name_string.c_str();
    float min = getMinHash(qhash);
    float max = getMaxHash(qhash);
    float a = maxCoordinate->getValue();
    float b = minCoordinate->getValue();
    QHash<QString, QVector<float> >::iterator it;
    for (it = qhash.begin(); it != qhash.end(); it++)
    {
        if (it.key() != header_name_constChar)
       {
          for (int j=0; j<it.value().size(); j++)
          {
             old_value = it.value().at(j);
             new_value = (old_value-min)/(max-min)*(a-b) + b;
             it.value().replace(j, new_value);
          }
       }
    }
}

/**
 * This method is used to denormalize the values to local coordinate system
 * @author Mikayel Egibyan
 * @param qhash The qhash is QHash<QString, QVector<float> > QHash
 **/
void Coordinate::denormalizeHashElements(QHash<QString, QVector<float> > &qhash)
{
    float new_value;
    float old_value;
    string header_name_string = "Cluster";
    const char *header_name_constChar = header_name_string.c_str();
    float min = getMinHash(qhash);
    float max = getMaxHash(qhash);
    float a = maxCoordinate->getValue();
    float b = minCoordinate->getValue();
    QHash<QString, QVector<float> >::iterator it;
    for (it = qhash.begin(); it != qhash.end(); ++it)
    {
        if (it.key() != header_name_constChar)
       {
          for (int j=0; j<it.value().size(); j++)
          {
             old_value = it.value().at(j);
             new_value = (((max-min)*old_value)+(min*(a-b))-b)/(a-b);
             it.value().replace(j, new_value);
          }
       }
    }
}

/**
 * This method is used to get the minimal value from all the vectors in the hash
 * @author Mikayel Egibyan
 * @param qhash2 The qhash2 is QHash<QString, QVector<float> > QHash
 **/
float Coordinate::getMinHash(QHash<QString, QVector<float> > qhash2)
{
    float min;
    QVector<float> vecMIN;
    string header_name_string = "Cluster";
    const char *header_name_constChar = header_name_string.c_str();
    QHashIterator<QString, QVector<float> > i(qhash2);
    while(i.hasNext())
    {
        i.next();
        if(i.key().operator !=(header_name_constChar))
        {
            min = getMin(i.value());
            vecMIN.push_back(min);
        }
    }
    minAllOver = getMin(vecMIN);
    return minAllOver;
}

/**
 * This method is used to get the maximal value from all the vectors in the hash
 * @author Mikayel Egibyan
 * @param qhash1 The qhash1 is QHash<QString, QVector<float> > QHash
 **/
float Coordinate::getMaxHash(QHash<QString, QVector<float> > qhash1)
{
    float max;
    QVector<float> vecMAX;
    string header_name_string = "Cluster";
    const char *header_name_constChar = header_name_string.c_str();
    QHashIterator<QString, QVector<float> > i(qhash1);
    while(i.hasNext())
    {
        i.next();
        if(i.key().operator !=(header_name_constChar))
        {
            max = getMax(i.value());
            vecMAX.push_back(max);
        }
    }
    maxAllOver = getMax(vecMAX);
    return maxAllOver;

}

/**
 * This method is used to get the maximal value from the vector
 * @author Mikayel Egibyan
 * @param vector The vector is QVector<float> type vector
 **/
float Coordinate::getMax(QVector<float> vector)
{
    float max = numeric_limits<float>::min();
        for(int i = 0; i < vector.size(); i++)
        {
            if(vector.at(i) > max)
            {
                max = vector.at(i);
            }
        }
    return max;
}

/**
 * This method is used to get the minimal value from the vector
 * @author Mikayel Egibyan
 * @param vector The vector is QVector<float> type vector
 **/
float Coordinate::getMin(QVector<float> vector)
{
    float min = numeric_limits<float>::max();
        for(int i = 0; i < vector.size(); i++)
        {
            if(vector.at(i) < min)
            {
                min = vector.at(i);
            }
        }
    return min;
}

/**
 * This method is used to get information of the selcted point and points
 * @author Mikayel Egibyan
 **/
void Coordinate::getSelectedPoint()
{
    if(readfileBool)
    {
        if(selectionType == 1)
        {
            QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\SelectedValues.txt");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            file.readAll();
            file.close();
            file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
            QTextStream outq(&file);
            if(file.isOpen())
            {
                for(int d = 1; d < listSize; d++)
                {
                    std::string s;
                    std::stringstream out;
                    out << d;
                    s = out.str();
                    string dim = "Dim_" + s;
                    QString Dim = QString::fromStdString(dim);
                    outq << Dim << ',';
                }
                outq << "Cluster" << '\n';

                QVector<int> indicesVect = getSelectedPointIndexRect();
                for(int l = 0; l < indicesVect.size() / 5; l++)
                {
                    for(int d = 1; d < listSize; d++)
                    {
                        std::string s;
                        std::stringstream out;
                        out << d;
                        s = out.str();
                        string dim = "Dim_" + s;
                        QString Dim = QString::fromStdString(dim);
                        outq << hashOriginal[Dim].value(indicesVect[l]) << ',';
                        //outq << hash["Cluster"].value(indicesVect[l]);
                    }
                    outq << hashOriginal["Cluster"].value(indicesVect[l]) << '\n';
                }
                file.close();
            }
            else
            {
                QMessageBox::warning(0, "Error", file.errorString());
            }

        }
        if(selectionType == 2)
        {
            QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\SelectedValue.txt");
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            file.readAll();
            file.close();
            file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
            QTextStream outq(&file);
            if(file.isOpen())
            {
                for(int d = 1; d < listSize; d++)
                {
                    std::string s;
                    std::stringstream out;
                    out << d;
                    s = out.str();
                    string dim = "Dim_" + s;
                    QString Dim = QString::fromStdString(dim);
                    outq << Dim << ',';
                }
                outq << "Cluster" << '\n';
                for(int d = 1; d < listSize; d++)
                {
                    std::string s;
                    std::stringstream out;
                    out << d;
                    s = out.str();
                    string dim = "Dim_" + s;
                    QString Dim = QString::fromStdString(dim);
                    outq << hashOriginal[Dim].value(selectedPointIndex) << ',';
                }
                outq << hashOriginal["Cluster"].value(selectedPointIndex);
                file.close();
            }
            else
            {
                QMessageBox::warning(0, "Error", file.errorString());
            }
        }
    }
}

/**
 * This method is used to render label for point
 * @author Mikayel Egibyan
 * @param a, b - scaling factors, x,y - normalized coordinates, xOrig,yOrig - denormalized coordinates
 **/
void Coordinate::renderLabelForPoint(int a, int b, float x, float y, float xOrig, float yOrig)
{
    if(selectionType == 2)
    {
        glPushMatrix();
        glColor3f(1, 0, 1);
        glScalef(a, b, 0);
        stringstream ss (stringstream::in | stringstream::out);
        ss << xOrig;
        string xChar = ss.str();

        stringstream s (stringstream::in | stringstream::out);
        s << yOrig;
        string yChar = s.str();

        string delimiter = " / ";

        glRasterPos2f(x - 0.015, y + 0.015);
        const char * labelX = xChar.c_str();
        const char * labelY = yChar.c_str();
        const char * delimiterChar = delimiter.c_str();
        glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) labelX);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) delimiterChar);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char *) labelY);
        glPopMatrix();
    }
}

/**
 * This method is used to set the normalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointXOriginal()
{
    string horValue = "Dim_" + x->getValue();
    QString horV = QString::fromStdString(horValue);
    selectedPointXOriginal = hashOriginal[horV].value(getSelectedPointIndex());
    //qDebug() << selectedPointXOriginal << hashOriginal[horV].value(getSelectedPointIndex());
}

/**
 * This method is used to get the normalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointXOriginal()
{
    return selectedPointXOriginal;
}

/**
 * This method is used to set the normalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointYOriginal()
{
    string vertValue = "Dim_" + y->getValue();
    QString vertV = QString::fromStdString(vertValue);
    selectedPointYOriginal = hashOriginal[vertV].value(getSelectedPointIndex());
}

/**
 * This method is used to get the normalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointYOriginal()
{
    return selectedPointYOriginal;
}

/**
 * This method is used to set the normalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointX()
{
    string horValue = "Dim_" + x->getValue();
    QString horV = QString::fromStdString(horValue);
    selectedPointX = hash[horV].value(getSelectedPointIndex());
}

/**
 * This method is used to get the normalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointX()
{
    return selectedPointX;
}

/**
 * This method is used to set the normalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointY()
{
    string vertValue = "Dim_" + y->getValue();
    QString vertV = QString::fromStdString(vertValue);
    selectedPointY = hash[vertV].value(getSelectedPointIndex());
}

/**
 * This method is used to get the normalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointY()
{
    return selectedPointY;
}

/**
 * This method is used to set the denormalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointXOriginalCentroid()
{
    string horValue = "Dim_" + x->getValue();
    QString horV = QString::fromStdString(horValue);
    selectedPointXOriginalCentroid = centroidsOriginal[horV].value(getSelectedCentroidIndex());
    //qDebug() << selectedPointXOriginal << hashOriginal[horV].value(getSelectedPointIndex());
}

/**
 * This method is used to get the denormalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointXOriginalCentroid()
{
    return selectedPointXOriginalCentroid;
}

/**
 * This method is used to set the denormalized information about the point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointYOriginalCentroid()
{
    string vertValue = "Dim_" + y->getValue();
    QString vertV = QString::fromStdString(vertValue);
    selectedPointYOriginalCentroid = centroidsOriginal[vertV].value(getSelectedCentroidIndex());
}

/**
 * This method is used to get the denormalized information about the point
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointYOriginalCentroid()
{
    return selectedPointYOriginalCentroid;
}

/**
 * This method is used to set the normalized information about the normalized centroid
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointXCentroid()
{
    string horValue = "Dim_" + x->getValue();
    QString horV = QString::fromStdString(horValue);
    selectedPointXCentroid = centroids[horV].value(getSelectedCentroidIndex());
}

/**
 * This method is used to set the normalized information about the normalized centroid
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointXCentroid()
{
    return selectedPointXCentroid;
}

/**
 * This method is used to set the normalized information about the normalized centroid
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointYCentroid()
{
    string vertValue = "Dim_" + y->getValue();
    QString vertV = QString::fromStdString(vertValue);
    selectedPointYCentroid = centroids[vertV].value(getSelectedCentroidIndex());
}

/**
 * This method is used to get the normalized information about the normalized centroid
 * @author Mikayel Egibyan
 **/
float Coordinate::getSelectedPointYCentroid()
{
    return selectedPointYCentroid;
}

/**
 * This method is used to set a toggle for rendering
 * @author Mikayel Egibyan
 **/
void Coordinate::setRenderTogle(bool value)
{
    renderTogle = value;
}

/**
 * This method is used to get a toggle for rendering
 * @author Mikayel Egibyan
 **/
bool Coordinate::getRenderTogle()
{
    return renderTogle;
}

/**
 * This method is used to get denormalized data
 * @author Mikayel Egibyan
 **/
QHash<QString, QVector<float> > Coordinate::getHashOriginal()
{
    return hashOriginal;
}

/**
 * This method is used to get normalized data
 * @author Mikayel Egibyan
 **/
QHash<QString, QVector<float> > Coordinate::getHash()
{
    return hash;
}

/**
 * This method is used to set the index of selected point
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointIndex(int value)
{
    selectedPointIndex = value;
}

/**
 * This method is used to get the index of selected point
 * @author Mikayel Egibyan
 **/
int Coordinate::getSelectedPointIndex()
{
    return selectedPointIndex;
}

/**
 * This method is used to set the index of selected centroid
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedCentroidIndex(int value)
{
    selectedCentroidIndex = value;
}

/**
 * This method is used to get the index of selected centroid
 * @author Mikayel Egibyan
 **/
int Coordinate::getSelectedCentroidIndex()
{
    return selectedCentroidIndex;
}

/**
 * This method is used to get the indices of selected points
 * @author Mikayel Egibyan
 **/
QVector<int> Coordinate::getSelectedPointIndexRect()
{
    return selectedPointIndexRect;
}

/**
 * This method is used to set the indices of selected points
 * @author Mikayel Egibyan
 **/
void Coordinate::setSelectedPointIndexRect(QVector<int> vec)
{
    selectedPointIndexRect = vec;
}

/**
 * This method is used to get if the centroids are stored
 * @author Mikayel Egibyan
 **/
bool Coordinate::getCentroidsLoaded()
{
    return centroidsLoaded;
}

/**
 * This method is used to set the centroids are stored
 * @author Mikayel Egibyan
 **/
void Coordinate::setCentroidsLoaded(bool value)
{
    centroidsLoaded = value;
}

/**
 * This method is used to set if the data is renderes
 * @author Mikayel Egibyan
 **/
void Coordinate::setDataRendered(bool value)
{
    dataIsRendered = value;
}

/**
 * This method is used to get if the data is renderes
 * @author Mikayel Egibyan
 **/
bool Coordinate::getDataRendered()
{
    return dataIsRendered;
}

/**
 * This method is used to get the the toggle information to show centroids
 * @author Mikayel Egibyan
 **/
bool Coordinate::getShowCentroids()
{
    return showCentroids;
}

/**
 * This method is used to set the the toggle information to show centroids
 * @author Mikayel Egibyan
 **/
void Coordinate::setShowCentroids(bool value)
{
    showCentroids = value;
}
