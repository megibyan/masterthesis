/**
*	@file mainwindow.h
*	@brief file contains the definaion of the class mainwindow.
*
*	@author Mikayel Egibyan
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "glwidget.h"
#include "Coordinate.h"
#include <QStringList>
#include <QHash>
#include <QString>
#include <QVector>
#include <QDebug>
#include "kmean_algorithm.h"
//#include "Mouse.h"
#include <GL/gl.h>
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent( QKeyEvent *keyEvent );
    void mouseMoveEvent(QMouseEvent *eventMove);
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
    void createPopUp();
    void createPopUpMerge();
    QPoint getMouseGlobalPosition();
    void setPopUpTogle(bool);
    bool getPopUpTogle();
    void setPopUpTogleMerge(bool);
    bool getPopUpTogleMerge();
    float calculateHalfSpaces(float, float,float, float, float, float);
    void determineLinePress(QPointF);
    void determineLineRelease(QPointF);
    void determineLine();
    QPointF getLinePress();
    QPointF getLineRelease();
    bool getdivisionMode();
    void setdivisionMode(bool);
    void generateNewCentroids(QHash<QString, QVector<float> >);

private slots:    
    void on_actionExit_triggered();
    void on_hor_axis_dropbox_currentIndexChanged();
    void on_refresh_clicked();
    void on_vert_axis_dropbox_currentIndexChanged();
    void Load();
    void LoadKmeans();
    void on_clust_num_dropbox_currentIndexChanged();
    //Coordinate cT;
    void on_sellection_type_dropbox_currentIndexChanged();
    void on_actionInformation_triggered();
    void on_pushButton_2_pressed();
    void setHashOrig(QHash<QString, QVector<float> >);
    QHash<QString, QVector<float> > getHashOrig();
    void on_pushButton_3_clicked();
    void triggeredPromote(QAction*);
    void triggeredMerge(QAction*);
    void on_actionSave_changes_triggered();
    void AddToNewPromote();
    void on_radioButton_clicked();
    void divideCluster();
    void on_radioButton_2_clicked();
    void on_Reset_clicked();

private:
    QVector<float> mouse;
    Ui::MainWindow *ui;
    //Coordinate *dim;
    kmean_algorithm kmean;
    QString filename;
    QString filename_1;
    float eye_x;
    float eye_y;
    float eye_z;
    float WidgetW;
    float WidgetH;
    QPointF lineBegin;
    QPointF lineEnd;
    QPointF buttonPressCoordinates;
    QPointF buttonReleaseCoordinates;
    QPointF mouseCurrentPosition;
    bool m;
    QPoint mouseGlobalPosition;
    QHash<QString, QVector<float> > hashOrig;
    int index;
    bool popUpTogle = false;
    bool popUpTogleMerge = false;
    QVector<int> indicesRect;
    QHash<QString, QVector<float> > stepByStepCluster;
    bool divisionMode=false;
    QHash<int, QVector<float> > clusterMeanCoordinate;
    QHash<int, QVector<float> > prevClusterMeanCoordinate;
    QVector<float> minDim;
    QVector<float> maxDim;
    bool rightButtonPressed = false;
    bool leftButtonPressed = false;
    bool leftButtonReleased = false;
};

#endif // MAINWINDOW_H
