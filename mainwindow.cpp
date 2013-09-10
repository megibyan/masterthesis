/**
*	@file mainwindow.cpp
*	@brief file contains all necessary methods to work with mainwindow
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
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    connect(ui->actionLoad_file, SIGNAL(triggered()), this, SLOT(Load()));
    connect(ui->actionK_mean_the_data, SIGNAL(triggered()), this, SLOT(LoadKmeans()));
    ui->sellection_type_dropbox->setCurrentIndex(0);
    ui->clust_num_dropbox->setCurrentIndex(0);
    widget->kmean.setK(ui->clust_num_dropbox->currentIndex() + 1);
    widget->coordinateT.setSelectionType(ui->sellection_type_dropbox->currentIndex());
    for(int i = 1; i <= 6; i++)
        ui->clust_num_dropbox->addItem(QString::number(i));
    for(int i = 1; i <= 4; i++)
        ui->hor_axis_dropbox->addItem(QString::number(i));
    for(int j = 1; j <= 4; j++)
        ui->vert_axis_dropbox->addItem(QString::number(j));
    widget->coordinateT.setLabelX("X");
    widget->coordinateT.setLabelY("Y");
    widget->coordinateT.setLabelCluster("n/a");
    QString labelX = ui->vert_axis_dropbox->currentText();
    string strX = labelX.toStdString();
    QString labelY = ui->vert_axis_dropbox->currentText();
    string strY = labelY.toStdString();
    widget->coordinateT.setLabelX(strX);
    widget->coordinateT.setLabelY(strY);
    kmean.setK(1);
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
}

/**
 * This method is used to handle the mouse release event
 * @author Mikayel Egibyan
 * @param releaseEvent
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    if(releaseEvent->button() & Qt::LeftButton)
    {
        rightButtonPressed = false;
        leftButtonReleased = true;
        leftButtonPressed = false;
        //setMouseTracking(false);
        m = false;
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        buttonReleaseCoordinates.setX(x);
        buttonReleaseCoordinates.setY(y_);
        //qDebug() << buttonReleaseCoordinates.x() << buttonReleaseCoordinates.y();
        widget->setQ(false);
        widget->setReleasedX(buttonReleaseCoordinates.x());
        widget->setReleasedY(buttonReleaseCoordinates.y());
        if(widget->coordinateT.getSelectionType() == 0 && getdivisionMode())
        {
            determineLineRelease(buttonReleaseCoordinates);
        }
    }
}

/**
 * This method is used to create a pop-up menu for merge action
 * @author Mikayel Egibyan
 */
void MainWindow::createPopUpMerge()
{
    if(getPopUpTogleMerge())
    {
        QPoint position;
        position = getMouseGlobalPosition();
        QMenu * menu = new QMenu();
        int last = kmean.getK();
        for(int i = 1; i <= last; i++)
        {
            QAction * action = new QAction(QString("Merge with %1").arg(i), menu);
            action->setProperty("index", i);
            menu->addAction(action);
        }
        menu->addAction("Divide", this, SLOT(divideCluster()));
        connect(menu, SIGNAL(triggered(QAction*)), SLOT(triggeredMerge(QAction*)));
        menu->popup(position);
    }
}

/**
 * This method is used to set values to the line's start point
 * @author Mikayel Egibyan
 */
void MainWindow::determineLinePress(QPointF press)
{
    lineBegin.setX(press.x());
    lineBegin.setY(press.y());
    //qDebug() << lineBegin.x() << lineBegin.y();
}

/**
 * This method is used to set values to the line's end point
 * @author Mikayel Egibyan
 */
void MainWindow::determineLineRelease(QPointF release)
{
    lineEnd.setX(release.x());
    lineEnd.setY(release.y());
    //qDebug() << lineEnd.x() << lineEnd.y();
}

/**
 * This method is used to get the line
 * @author Mikayel Egibyan
 */
void MainWindow::determineLine()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(getdivisionMode())
    {
        setMouseTracking(true);
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        int a = widget->coordinateT.findNumberOfClusters() + 1;
        int cluster = widget->coordinateT.getNumberOfClusterSelectedCentroid();
        widget->coordinateT.distFromLine(hashOrig, cluster, a);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
        setHashOrig(hashOrig);
        setMouseTracking(false);
    }
}


/**
 * This method is used to get the line's start point
 * @author Mikayel Egibyan
 */
QPointF MainWindow::getLinePress()
{
    return lineBegin;
}

/**
 * This method is used to get the line's end point
 * @author Mikayel Egibyan
 */
QPointF MainWindow::getLineRelease()
{
    return lineEnd;
}

/**
 * This method is used to get if the cluster is divided
 * @author Mikayel Egibyan
 */
bool MainWindow::getdivisionMode()
{
    return divisionMode;
}

/**
 * This method is used to set if the cluster is divided
 * @author Mikayel Egibyan
 */
void MainWindow::setdivisionMode(bool value)
{
    divisionMode = value;
}

/**
 * This method is used to divide the cluster
 * @author Mikayel Egibyan
 */
void MainWindow::divideCluster()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    ui->sellection_type_dropbox->setCurrentIndex(0);
    if(widget->coordinateT.getSelectionType() == 0)
    {
        qDebug() << true;
        setdivisionMode(true);
    }
}

/**
 * This method is used to creat a pop-up menu for promotion
 * @author Mikayel Egibyan
 */
void MainWindow::createPopUp()
{
    if(getPopUpTogle())
    {
        QPoint position;
        position = getMouseGlobalPosition();
        QMenu * menu = new QMenu();
        int last = kmean.getK();
        for(int i = 1; i <= last; i++)
        {
            QAction * action = new QAction(QString("Promote to %1").arg(i), menu);
            action->setProperty("index", i);
            menu->addAction(action);
        }
        if(kmean.getK() < 6)
        {
            menu->addAction("Add to new", this, SLOT(AddToNewPromote()));
        }
        connect(menu, SIGNAL(triggered(QAction*)), SLOT(triggeredPromote(QAction*)));
        menu->popup(position);
    }
}

/**
 * This method is used to control pop-up menu for merging
 * @author Mikayel Egibyan
 */
void MainWindow::triggeredMerge(QAction* a)
{
    const QVariant indexK(a->property("index"));
    if (!indexK.isValid())
        return;
    const int i = indexK.toInt();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(getHashOrig().isEmpty())
        setHashOrig(widget->coordinateT.getHashOriginal());
    getHashOrig();
    int cluster = widget->coordinateT.getNumberOfClusterSelectedCentroid();
    for(int u=0; u<hashOrig["Cluster"].size(); u++)
    {
        if(hashOrig["Cluster"].value(u) == cluster)
            hashOrig["Cluster"].replace(u, i);
    }
    setHashOrig(hashOrig);
    widget->setHashToRender(hashOrig);
    generateNewCentroids(hashOrig);
    widget->coordinateT.storeNewClusterCentroids();
    widget->coordinateT.setNewCentroidsCreated(true);
    widget->coordinateT.setChangedData(getHashOrig());
}

/**
 * This method is used to control the action of adding to a new cluster
 * @author Mikayel Egibyan
 */
void MainWindow::AddToNewPromote()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    int a = widget->coordinateT.findNumberOfClusters() + 1;
    if(widget->coordinateT.getSelectionType() == 1)
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        indicesRect = widget->coordinateT.getSelectedPointIndexRect();
        for(int z=0; z<indicesRect.size(); z++)
        {
            hashOrig["Cluster"].replace(indicesRect[z], a);
        }
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
        generateNewCentroids(hashOrig);
        widget->coordinateT.storeNewClusterCentroids();
        widget->coordinateT.setNewCentroidsCreated(true);
        widget->coordinateT.setChangedData(getHashOrig());
    }
    if(widget->coordinateT.getSelectionType() == 2)
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, a);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
        generateNewCentroids(hashOrig);
        widget->coordinateT.storeNewClusterCentroids();
        widget->coordinateT.setNewCentroidsCreated(true);
        //widget->coordinateT.setChangedData(getHashOrig());
    }
    setHashOrig(hashOrig);
    widget->setHashToRender(hashOrig);
}

/**
 * This method is used to generate new centroids after each change in data
 * @author Mikayel Egibyan
 */
void MainWindow::generateNewCentroids(QHash<QString, QVector<float> > hash)
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    int K = widget->coordinateT.getMax(hash["Cluster"]);
    float Dim1[K];
    float Dim2[K];
    float Dim3[K];
    float Dim4[K];
    float centroidD1[K];
    float centroidD2[K];
    float centroidD3[K];
    float centroidD4[K];

    int counter[K];
    for(int i = 0; i < K ; i++)
    {
        Dim1[i] = 0;
        Dim2[i] = 0;
        Dim3[i] = 0;
        Dim4[i] = 0;
        counter[i] = 0;
        for(int j = 0; j < hash["Cluster"].size(); j++)
        {
            if(hash["Cluster"].value(j) == i+1)
            {
                Dim1[i] += hash["Dim_1"].value(j);
                Dim2[i] += hash["Dim_2"].value(j);
                Dim3[i] += hash["Dim_3"].value(j);
                Dim4[i] += hash["Dim_4"].value(j);
                counter[i]++;
            }
        }
    }

    for(int l = 0; l < K; l++)
    {
        centroidD1[l] = Dim1[l] / counter[l];
        centroidD2[l] = Dim2[l] / counter[l];
        centroidD3[l] = Dim3[l] / counter[l];
        centroidD4[l] = Dim4[l] / counter[l];
    }

    QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\NewClusters.csv");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    if(file.isOpen())
    {
        out << "Dim_1" << "," << "Dim_2" << "," << "Dim_3" << "," <<"Dim_4" << "," <<"Cluster" << '\n';
        for(int n = 0; n < K; n++)
        {
            out << centroidD1[n] << "," << centroidD2[n] << "," << centroidD3[n] << "," << centroidD4[n] << "," << n+1 << '\n';
        }
    }
    else
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
}



/**
 * This method is used to control the pop-up menu for promotion
 * @author Mikayel Egibyan
 */
void MainWindow::triggeredPromote(QAction* a)
{
    const QVariant indexK(a->property("index"));
    if (!indexK.isValid())
        return;
    const int i = indexK.toInt();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(widget->coordinateT.getSelectionType() == 1)
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        indicesRect = widget->coordinateT.getSelectedPointIndexRect();
        for(int z=0; z<indicesRect.size(); z++)
        {
            hashOrig["Cluster"].replace(indicesRect[z], i);
        }
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
        generateNewCentroids(hashOrig);
        widget->coordinateT.storeNewClusterCentroids();
        widget->coordinateT.setNewCentroidsCreated(true);
        widget->coordinateT.setChangedData(getHashOrig());
    }
    if(widget->coordinateT.getSelectionType() == 2)
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, i);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
        generateNewCentroids(hashOrig);
        widget->coordinateT.storeNewClusterCentroids();
        widget->coordinateT.setNewCentroidsCreated(true);
        widget->coordinateT.setChangedData(getHashOrig());
    }
}

/**
 * This method is used to set the togle information of pop-up menu for promotion
 * @author Mikayel Egibyan
 */
void MainWindow::setPopUpTogle(bool value)
{
    popUpTogle = value;
}

/**
 * This method is used to get the togle information of pop-up menu for promotion
 * @author Mikayel Egibyan
 */
bool MainWindow::getPopUpTogle()
{
    return popUpTogle;
}

/**
 * This method is used to set the togle information of pop-up menu for merging
 * @author Mikayel Egibyan
 */
void MainWindow::setPopUpTogleMerge(bool value)
{
    popUpTogleMerge = value;
}

/**
 * This method is used to get the togle information of pop-up menu for merging
 * @author Mikayel Egibyan
 */
bool MainWindow::getPopUpTogleMerge()
{
    return popUpTogleMerge;
}

/**
 * This method is used to get the mouse global coordinates
 * @author Mikayel Egibyan
 */
QPoint MainWindow::getMouseGlobalPosition()
{
    return mouseGlobalPosition;
}

/**
 * This method is used to handle the mouse press event
 * @author Mikayel Egibyan
 * @param eventPress
 */
void MainWindow::mousePressEvent(QMouseEvent  *eventPress)
{
    if((eventPress->buttons() & Qt::RightButton))
    {
        rightButtonPressed = true;
        leftButtonReleased = false;
        leftButtonPressed = false;
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        if(widget->coordinateT.getSelectionType() == 2)
        {
            if(widget->coordinateT.getPointAlreadySelected())
            {
                setPopUpTogle(true);
                setPopUpTogleMerge(false);
                mouseGlobalPosition = eventPress->globalPos();
                createPopUp();
            }
            if(widget->coordinateT.getCentroidAlreadySelected())
            {
                setPopUpTogle(false);
                setPopUpTogleMerge(true);
                mouseGlobalPosition = eventPress->globalPos();
                createPopUpMerge();
            }
        }
        if(widget->coordinateT.getSelectionType() == 1)
        {
            if(widget->coordinateT.getPointsAlreadySelectedRect())
            {
                setPopUpTogle(true);
                setPopUpTogleMerge(false);
                mouseGlobalPosition = eventPress->globalPos();
                createPopUp();
            }
        }
    }
    if((eventPress->buttons() & Qt::LeftButton))
    {
        rightButtonPressed = false;
        leftButtonReleased = false;
        leftButtonPressed = true;
        setMouseTracking(true);
        m = true;
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        buttonPressCoordinates.setX(x);
        buttonPressCoordinates.setY(y_);
        widget->setQ(true);
        widget->setPushedX(buttonPressCoordinates.x());
        widget->setPushedY(buttonPressCoordinates.y());
        widget->setCurrentX(buttonPressCoordinates.x());
        widget->setCurrentY(buttonPressCoordinates.y());
        if(widget->coordinateT.getSelectionType() == 0 && getdivisionMode())
        {
            determineLinePress(buttonPressCoordinates);
        }
    }
}

/**
 * This method is used to handle the mouse move event
 * @author Mikayel Egibyan
 * @param eventPress
 */
void MainWindow::mouseMoveEvent(QMouseEvent *eventMove)
{
    if((eventMove->buttons() & Qt::LeftButton))
    {
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        mouseCurrentPosition.setX(x);
        mouseCurrentPosition.setY(y_);
        widget->setCurrentX(mouseCurrentPosition.x());
        widget->setCurrentY(mouseCurrentPosition.y());
        determineLine();
        if(leftButtonPressed && !leftButtonReleased)
            determineLine();
        //if(widget->coordinateT.getlineIsDrawn() && getdivisionMode())
            //determineLine();
    }
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
    QString label = ui->hor_axis_dropbox->currentText();
    string str = label.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelX(str);
}

/**
 * This method is used to handle the selection combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_sellection_type_dropbox_currentIndexChanged()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setSelectionType(ui->sellection_type_dropbox->currentIndex());
    if(ui->sellection_type_dropbox->currentIndex() != 0)
        setdivisionMode(false);

}

/**
 * This method is used to handle the Vertical combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_vert_axis_dropbox_currentIndexChanged()
{
    QString label = ui->vert_axis_dropbox->currentText();
    string str = label.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelY(str);
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
    widget->coordinateT.setRenderTogle(true);
    widget->setHashToRender(widget->coordinateT.getHash());
    //widget->coordinateT.readFileOfNotClustereData();
    if(widget->coordinateT.getFileLoadedStatus())
    {
        ui->clust_num_dropbox->setCurrentIndex(widget->coordinateT.findNumberOfClusters()-1);
        ui->clust_num_dropbox->setDisabled(true);
        QString label = ui->clust_num_dropbox->currentText();
        string str = label.toStdString();
        widget->coordinateT.setLabelCluster(str);
    }
}

/**
 * This method is used to handle the LoadKmeans menu event
 * @author Mikayel Egibyan
 */
void MainWindow::LoadKmeans()
{
    filename_1 = QFileDialog::getOpenFileName(this, "Load a file");
    kmean.readFileOfNotClustereData(filename_1);
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getReadStatus())
    {
        ui->clust_num_dropbox->setDisabled(true);
        widget->coordinateT.setNumberOfIterations(kmean.getNumberOfIterations());
        widget->coordinateT.ReadFile("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ClusterReferences.csv");
        widget->coordinateT.setRenderTogle(true);
        widget->setHashToRender(widget->coordinateT.getHash());
    }
}

/**
 * This method is used to handle the Cluster combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_clust_num_dropbox_currentIndexChanged()
{
    kmean.setK(ui->clust_num_dropbox->currentIndex() + 1);
    QString label = ui->clust_num_dropbox->currentText();
    string str = label.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setLabelCluster(str);
}

/**
 * This method is used to handle the Information menu click event
 * @author Mikayel Egibyan
 */
void MainWindow::on_actionInformation_triggered()
{
    QMessageBox::about(this, "How to use", "Press '@K-mean the data' to select a '.csv' file which you want to cluster. Press '@Load file' to select a '.csv' file with already clustered data, that you want to visualize.");
}

/**
 * This method is used to handle the Save value button click event
 * @author Mikayel Egibyan
 */
void MainWindow::on_pushButton_2_pressed()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.getSelectedPoint();
}

/**
 * This method is used to get the data to be rendered
 * @author Mikayel Egibyan
 */
void MainWindow::setHashOrig(QHash<QString, QVector<float> > hash)
{
    hashOrig = hash;
}

/**
 * This method is used to set the data to be rendered
 * @author Mikayel Egibyan
 */
QHash<QString, QVector<float> > MainWindow::getHashOrig()
{
    return hashOrig;
}

/**
 * This method is used to handle the Reset button click event
 * @author Mikayel Egibyan
 */
void MainWindow::on_pushButton_3_clicked()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    setHashOrig(widget->coordinateT.getHashOriginal());
    widget->setHashToRender(hashOrig);
    widget->coordinateT.setNewCentroidsCreated(false);
}

/**
 * This method is used to handle the Save changes menu click event
 * @author Mikayel Egibyan
 */
void MainWindow::on_actionSave_changes_triggered()
{
    QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\ChangedData.csv");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    if(file.isOpen())
    {

        QHash<QString, QVector<float> > changedHash = getHashOrig();
        int elements = changedHash["Dim_1"].size();
        int u=0;
        QHash<QString, QVector<float> >::iterator it;
        for(it = changedHash.begin(); it != changedHash.end(); it++)
        {
            u++;
        }

        if(getHashOrig().isEmpty())
            QMessageBox::warning(this, "Warning", "Nothing to save.");

        for(int j = 1; j < u; j++)
        {
            out << "Dim_" << j << ",";
        }
        out << "Cluster" << '\n';

        for(int d=0; d< elements; d++)
        {
            out << changedHash["Dim_1"].at(d) << "," << changedHash["Dim_2"].at(d) << "," << changedHash["Dim_3"].at(d) << "," << changedHash["Dim_4"].at(d) << "," << changedHash["Cluster"].at(d) <<'\n';
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(0, "Error", file.errorString());
    }
}

/**
 * This method is used to handle the radion button to show centroids
 * @author Mikayel Egibyan
 */
void MainWindow::on_radioButton_clicked()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setShowCentroids(true);
}

/**
 * This method is used to handle the radion button to hide centroids
 * @author Mikayel Egibyan
 */
void MainWindow::on_radioButton_2_clicked()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setShowCentroids(false);
}

/**
 * This method is used to handle the cluster number dropbox togle event
 * @author Mikayel Egibyan
 */
void MainWindow::on_Reset_clicked()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    ui->clust_num_dropbox->setDisabled(false);
}


