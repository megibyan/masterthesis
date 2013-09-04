#include "windows.h"
#include "mainwindow.h"
#include <QApplication>
#include "Scene.h"
#include "glwidget.h"
#include <GL/glut.h>

//Scene *scene;


int main(int argc, char *argv[])
{
    glutInit(&argc, (char**)argv);
   // scene = Scene::getInstance();
   // scene->loadCSVData();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
