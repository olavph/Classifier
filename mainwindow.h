#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <datum.h>
#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation
#include <string>
#include <cstdlib>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QVector<Datum> points;
    QVector<Class*> classes;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawDatum(Datum d);
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
signals:
    void fileSelected(QString);
};

#endif // MAINWINDOW_H
