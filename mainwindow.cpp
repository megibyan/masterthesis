/**
*	@file mainwindow.cpp
*	@brief file contains all necessary methods to work with mainwindow.
*
*	@author Mikayel Egibyan
*/

#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dim = new Coordinate;
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    connect(ui->actionLoad_file, SIGNAL(triggered()), this, SLOT(Load()));

    /* modelH = qobject_cast<QStandardItemModel *>(ui->hor_axis_dropbox->model());
    modelV = qobject_cast<QStandardItemModel *>(ui->vert_axis_dropbox->model());
    itemV = modelV->item(ui->hor_axis_dropbox->currentIndex());
    itemH = modelH->item(ui->vert_axis_dropbox->currentIndex());*/

    for(int i = 1; i <= 6; i++)
        ui->clust_num_dropbox->addItem(QString::number(i));

    for(int i = 1; i <= 6; i++)
        ui->hor_axis_dropbox->addItem(QString::number(i));

    for(int j = 1; j <= 6; j++)
        ui->vert_axis_dropbox->addItem(QString::number(j));

   // ui->hor_axis_dropbox->setCurrentIndex(0);
   // ui->vert_axis_dropbox->setItemData(0, 0, Qt::UserRole -1);

   // ui->vert_axis_dropbox->setCurrentIndex(1);
    //ui->hor_axis_dropbox->setItemData(1, 0, Qt::UserRole -1);

    widget->coordinateT.setLabelX("X");
    widget->coordinateT.setLabelY("Y");
    widget->coordinateT.setLabelCluster("n/a");
}

/**
 * Default destructor
 * @author Mikayel Egibyan
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * This method is used to handle the keyboard event
 * @author Mikayel Egibyan
 * @param key The ASCII code of pressed key
 */
void MainWindow::keyPressEvent( QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Escape)
        exit(0);
    if(keyEvent->key() == Qt::Key_Up)
        eye_z = eye_z + 1;
    if(keyEvent->key() == Qt::Key_Down)
        ;
    if(keyEvent->key() == Qt::Key_Left)
        ;
    if(keyEvent->key() == Qt::Key_Right)
        ;
}

/**
 * This method is used to handle the Exit menu event
 * @author Mikayel Egibyan
 */
void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

/**
 * This method is used to handle the Horizontal combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_hor_axis_dropbox_currentIndexChanged()
{
     //QVariant  v(1|32);
    //ui->hor_axis_dropbox->setItemData(1, v, Qt::UserRole -1);
   // int t = ui->hor_axis_dropbox->currentIndex();
    //ui->vert_axis_dropbox->setItemData(ui->hor_axis_dropbox->currentIndex(), 0, Qt::UserRole -1);
    //if(ui->hor_axis_dropbox->currentIndex()==ui->vert_axis_dropbox->currentIndex())
      //  ui->vert_axis_dropbox->setItemData(t, v, Qt::UserRole -1);

   /* if(ui->hor_axis_dropbox->currentIndex()==4)
        itemH->setEnabled(false);*/
    if(ui->hor_axis_dropbox->currentIndex()== ui->vert_axis_dropbox->currentIndex())
        QMessageBox::warning(this, "Wrong choise", "Horizontal and vertical axis cannot have the same value. PLease select different values.");

    QString label = ui->hor_axis_dropbox->currentText();
    string str = label.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelX(str);
    //widget->coordinateT.render_text_information();
}

/**
 * This method is used to handle the Vertical combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_vert_axis_dropbox_currentIndexChanged()
{
    //model_v = qobject_cast<QStandardItemModel *>(ui->vert_axis_dropbox->model());
    //item_v = model_v->item(ui->vert_axis_dropbox->currentIndex());

    //if(ui->vert_axis_dropbox->currentIndex()== ui->hor_axis_dropbox->currentIndex())
      //  QMessageBox::warning(this, "Wrong choise", "!Horizontal and vertical axis cannot have the same value. PLease select different values.");

    QString label = ui->vert_axis_dropbox->currentText();
    string str = label.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelY(str);
   // widget->coordinateT.render_text_information();
}

/**
 * This method is used to handle the Refresh button click event
 * @author Mikayel Egibyan
 */
void MainWindow::on_refresh_clicked()
{
     GLWidget *widget = this->findChild<GLWidget *>("glwidget");
     widget->updateGL_mech();
}

/**
 * This method is used to handle the Load menu event
 * @author Mikayel Egibyan
 */
void MainWindow::Load()
{
    filename = QFileDialog::getOpenFileName(this, "Load a file");
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.ReadFile(filename);
}
/*
 *
 * This method is used to read the data file and store the information in the data model
 * @author Mikayel Egibyan

void MainWindow::ReadFile()
{
    QFile file(filename);
    //QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\sample.csv");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
    headerLine = file.readLine();
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
    QHashIterator<QString, QVector<float> > i(hash);
    while (i.hasNext())
    {
        i.next();
        qDebug() << i.key() << ":" << i.value();
    }
}
*/

/**
 * This method is used to handle the Cluster combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_clust_num_dropbox_currentIndexChanged()
{
    QString cluster = ui->clust_num_dropbox->currentText();
    string strCluster = cluster.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelCluster(strCluster);
}

void MainWindow::on_xScroll_sliderMoved(int position)
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");

}

void MainWindow::on_xScroll_actionTriggered(int action)
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    action = ui->xScroll->value();
    qDebug() << action;
    widget->coordinateT.setMinCoordinate(0.5);

}
