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

private slots:
    void on_actionExit_triggered();
    void on_hor_axis_dropbox_currentIndexChanged();
    void on_refresh_clicked();
    void on_vert_axis_dropbox_currentIndexChanged();
    void Load();
    void on_clust_num_dropbox_currentIndexChanged();
    void on_xScroll_sliderMoved(int position);

    void on_xScroll_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    Coordinate *dim;
    QString filename;
    float eye_x;
    float eye_y;
    float eye_z;
};

#endif // MAINWINDOW_H




