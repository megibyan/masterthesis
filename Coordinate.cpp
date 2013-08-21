/**
*	@file Coordinate.cpp
*	@brief file contains all necessary methods to work with Coordinates.
*
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
}

/**
* This method is used to set the minimal coordinate
* @author Mikayel Egibyan
*/
void Coordinate::setMinCoordinate(float value)
{
    this->minCoordinate->setValue(value);
}

/**
* This method is used to set the maximal coordinate
* @author Mikayel Egibyan
*/
void Coordinate::setMaxCoordinate(float value)
{
    this->maxCoordinate->setValue(value);
}


/**
* This method is used to set a label to horizontal axis
* @author Mikayel Egibyan
*/
void Coordinate::setLabelX(string value)
{
    this->x->setValue(value);
}

/**
* This method is used to set a label to vertical axis
* @author Mikayel Egibyan
*/
void Coordinate::setLabelY(string value)
{
    this->y->setValue(value);
}

/**
* This method is used to set a label to clusters
* @author Mikayel Egibyan
*/
void Coordinate::setLabelCluster(string value)
{
    this->c->setValue(value);
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

    glPopMatrix();
}

/**
 * This method is used to set a value to the radius of points
 * @author Mikayel Egibyan
 * @param value The value of the radius of points

void Coordinate::setRadiusPoint(float value)
{
    radiusPoint = value;
}
*/

/**
 * This method is used to render the data points got from the .csv file
 * @author Mikayel Egibyan
 */
void Coordinate::render_data_points(int a, int b)
{
    string horValue = "Dim_" + x->getValue();
    string vertValue = "Dim_" + y->getValue();
    QString horV = QString::fromStdString(horValue);
    QString vertV = QString::fromStdString(vertValue);
    QHash<QString, QVector<float> >::iterator it;

    glPushMatrix();
    normalizeHashElements(hash);
    glPointSize(5);
    glColor3f(0, 1, 0);
    glScalef(a, b, 0);

    glBegin(GL_POINTS);
    for (it = hash.begin(); it != hash.end(); ++it)
    {
        for (int j=0; j<it.value().size(); j++)
        {

            if(hash["Cluster"].value(j) == 1)
            {
                glColor3f(0, 1, 0);
                glVertex2f(hash[horV].value(j), hash[vertV].value(j));
            }
            if(hash["Cluster"].value(j) == 2)
            {
                glColor3f(1, 0, 0);
                glVertex2f(hash[horV].value(j), hash[vertV].value(j));
            }
            if(hash["Cluster"].value(j) == 3)
            {
                glColor3f(0, 0, 1);
                glVertex2f(hash[horV].value(j), hash[vertV].value(j));
            }
        }
    }
    glEnd();

    glFlush();
    glPopMatrix();

}

/**
 * This method is used to read a .csv file
 * @author Mikayel Egibyan
 **/
void Coordinate::ReadFile(QString filename)
{
    QFile file(filename);
    //QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\sample.csv");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
    headerLine = file.readLine().trimmed();
    //headerLine = headerLine.simplified();
    //headerLine.replace('\n',"");
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

    normalizeHashElements(hash);
    QHashIterator<QString, QVector<float> > i(hash);
        while (i.hasNext())
        {
            i.next();
            qDebug() << i.key() << ":" << i.value();
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
    for (it = qhash.begin(); it != qhash.end(); ++it)
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
