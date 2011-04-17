#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation
#include <string>
#include <cstdlib>

#include "datacontainer.h"
#include "class.h"
#include "ibl/ibl.h"

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    DataContainer dataContainer;
    QVector<Class*> classes;
    IBL * ibl;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawDatum(Datum * d, bool selected = false);
    void drawFromFile(QString f);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
public slots:
    void showFileDialog();
    void generateRandomSet();
    void generateSpiral();
    void generateDoubleSpiral();
    void clear();
    void openFile();
    void insertAndClassify();
    void trainWithData();
    void drawData();
    void drawConceptualDescriptor();
    void drawIncorrectlyClassifiedData();
    void drawDelaunayTriangles();
    void drawDelaunayCircles();
    void drawVoronoiDiagram();
    void redraw();
signals:
    void fileSelected(QString);
};

#endif // MAINWINDOW_H
