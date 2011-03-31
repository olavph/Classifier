#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <datum.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawDatum(Datum d);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
public slots:
    void showFileDialog();
    void generateRandomSet();
    void generateSpiral();
    void generateDoubleSpiral();
signals:
    void fileSelected(QString);
};

#endif // MAINWINDOW_H
