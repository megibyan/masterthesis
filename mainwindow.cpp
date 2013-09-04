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
    //dim = new Coordinate;
    //mouseX = new Mouse(this->mapFromGlobal(QCursor::pos()).x());
    //mouseY = new Mouse(this->mapFromGlobal(QCursor::pos()).y());
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    connect(ui->actionLoad_file, SIGNAL(triggered()), this, SLOT(Load()));
    connect(ui->actionK_mean_the_data, SIGNAL(triggered()), this, SLOT(LoadKmeans()));
    ui->sellection_type_dropbox->setCurrentIndex(0);
    ui->clust_num_dropbox->setCurrentIndex(0);
    widget->kmean.setK(ui->clust_num_dropbox->currentIndex() + 1);
    widget->coordinateT.setSelectionType(ui->sellection_type_dropbox->currentIndex());
    //WidgetW = widget->getWidgetWidth();
    //WidgetH = widget->getWidgetHeight();
    /* modelH = qobject_cast<QStandardItemModel *>(ui->hor_axis_dropbox->model());
    modelV = qobject_cast<QStandardItemModel *>(ui->vert_axis_dropbox->model());
    itemV = modelV->item(ui->hor_axis_dropbox->currentIndex());
    itemH = modelH->item(ui->vert_axis_dropbox->currentIndex());*/

    for(int i = 1; i <= 6; i++)
        ui->clust_num_dropbox->addItem(QString::number(i));

    for(int i = 1; i <= 4; i++)
        ui->hor_axis_dropbox->addItem(QString::number(i));

    for(int j = 1; j <= 4; j++)
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
}

void MainWindow::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    if(releaseEvent->button() & Qt::LeftButton)
    {
        setMouseTracking(false);
        m = false;
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        buttonReleaseCoordinates.setX(x);
        buttonReleaseCoordinates.setY(y_);
        qDebug() << buttonReleaseCoordinates.x() << buttonReleaseCoordinates.y();
        widget->setQ(false);
        widget->setReleasedX(buttonReleaseCoordinates.x());
        widget->setReleasedY(buttonReleaseCoordinates.y());
    }
}

void MainWindow::promoteTo1()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 1)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 1);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 1)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 1);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}

void MainWindow::promoteTo2()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 2)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 2);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 2)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 2);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}

void MainWindow::promoteTo3()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 3)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 3);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 3)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 3);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}

void MainWindow::promoteTo4()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 4)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 4);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 4)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 4);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}

void MainWindow::promoteTo5()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 5)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 5);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 5)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 5);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}

void MainWindow::promoteTo6()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    if(kmean.getK() < 6)
    {
        QMessageBox::warning(this, "Warning", "No cluster found. The point is added to new cluster.");
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        hashOrig["Cluster"].replace(index, 6);
        setHashOrig(hashOrig);
        widget->setHashToRender(hashOrig);
    }
    else
    {
        if(getHashOrig().isEmpty())
            setHashOrig(widget->coordinateT.getHashOriginal());
        getHashOrig();
        index = widget->coordinateT.getSelectedPointIndex();
        if(hashOrig["Cluster"].value(index) == 6)
        {
            QMessageBox::warning(this, "Warning", "The selected point is already from first  cluster.");
        }
        else
        {
            hashOrig["Cluster"].replace(index, 6);
            setHashOrig(hashOrig);
            widget->setHashToRender(hashOrig);
        }
    }
}
void MainWindow::createPopUp()
{
    QPoint position;
    position = getMouseGlobalPosition();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    QMenu menu(widget);
    menu.addAction("Promote to 1", this, SLOT(promoteTo1()))->setDisabled(false);
    menu.addAction("Promote to 2", this, SLOT(promoteTo2()))->setDisabled(false);
    menu.addAction("Promote to 3", this, SLOT(promoteTo3()))->setDisabled(false);
    menu.addAction("Promote to 4", this, SLOT(promoteTo4()))->setDisabled(false);
    menu.addAction("Promote to 5", this, SLOT(promoteTo5()))->setDisabled(false);
    menu.addAction("Promote to 6", this, SLOT(promoteTo6()))->setDisabled(false);
    menu.exec(position);
}

QPoint MainWindow::getMouseGlobalPosition()
{
    return mouseGlobalPosition;
}

void MainWindow::mousePressEvent(QMouseEvent  *eventPress)
{
    if((eventPress->buttons() & Qt::RightButton))
    {
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        if(widget->coordinateT.getSelectionType() == 2)
        {
            if(widget->coordinateT.getPointAlreadySelected())
            {
                mouseGlobalPosition = eventPress->globalPos();
                createPopUp();
            }
        }
    }
    if((eventPress->button() & Qt::LeftButton))
    {
        setMouseTracking(true);
        m = true;
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        buttonPressCoordinates.setX(x);
        buttonPressCoordinates.setY(y_);
        qDebug() << buttonPressCoordinates.x() << buttonPressCoordinates.y();
        widget->setQ(true);
        widget->setPushedX(buttonPressCoordinates.x());
        widget->setPushedY(buttonPressCoordinates.y());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(eventMove->buttons() & Qt::LeftButton)
    {
        GLWidget *widget = this->findChild<GLWidget *>("glwidget");
        float x = widget->getNormalizedWidth(widget->mapFromGlobal(QCursor::pos()).x());
        float y = widget->getNormalizedHeight(widget->mapFromGlobal(QCursor::pos()).y());
        float y_ = 1.0 - y;
        mouseCurrentPosition.setX(x);
        mouseCurrentPosition.setY(y_);
        widget->setCurrentX(mouseCurrentPosition.x());
        widget->setCurrentY(mouseCurrentPosition.y());
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

void MainWindow::on_sellection_type_dropbox_currentIndexChanged()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.setSelectionType(ui->sellection_type_dropbox->currentIndex());

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
    widget->coordinateT.setRenderTogle(true);
    widget->setHashToRender(widget->coordinateT.getHash());
    //widget->coordinateT.readFileOfNotClustereData();
}

void MainWindow::LoadKmeans()
{
    filename_1 = QFileDialog::getOpenFileName(this, "Load a file");
    kmean.readFileOfNotClustereData(filename_1);
}

/**
 * This method is used to handle the Cluster combobox index change event
 * @author Mikayel Egibyan
 */
void MainWindow::on_clust_num_dropbox_currentIndexChanged()
{
    //QString cluster = ui->clust_num_dropbox->currentText();
    //string strCluster = cluster.toStdString();
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->kmean.setK(ui->clust_num_dropbox->currentIndex() + 1);
}


void MainWindow::on_actionInformation_triggered()
{
    QMessageBox::about(this, "How to use", "Press '@K-mean the data' to select a '.csv' file which you want to cluster. Press '@Load file' to select a '.csv' file with already clustered data, that you want to visualize.");
}


void MainWindow::on_pushButton_2_pressed()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    widget->coordinateT.getSelectedPoint();
    /*QFile file("C:\\Qt\\latest test\\build-Prototype-Desktop_Qt_5_1_0_MinGW_32bit-Debug\\debug\\SelectedItems.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    if(file.isOpen())
    {
    }*/
}

void MainWindow::setHashOrig(QHash<QString, QVector<float> > hash)
{
    hashOrig = hash;
}

QHash<QString, QVector<float> > MainWindow::getHashOrig()
{
    return hashOrig;
}

void MainWindow::on_pushButton_3_clicked()
{
    GLWidget *widget = this->findChild<GLWidget *>("glwidget");
    setHashOrig(widget->coordinateT.getHashOriginal());
    widget->setHashToRender(hashOrig);
}
