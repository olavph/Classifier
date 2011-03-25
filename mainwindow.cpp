#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    emit fileSelected(fileName);
}


/*
Implementar um programa que satisfaça as seguintes propriedades:

    O programa deve ser capaz de gerar 4 tipos de conjuntos de dados:
        Um conjunto de dados 2D (duas variáveis apenas).
        Um conjunto de dados ND (com um grande número de variáveis)
        Conjuntos de dados de espiral simples.
        Conjuntos de dados de espiral dupla.
    Euclidiana entre padrões de dimensões arbitrárias, de maneira que possam
    ser usados para todos os conjuntos de dados gerados.
    Implemente o algoritmo de NN (Nearest Neighbour) e kNN (k-Nearest
    Neighbours) e teste em todos os 4 conjuntos de dados.

Observações:

    Os dados 2D e ND podem ser utilizados a partir de conjuntos de dados
    disponíveis nos sites sugeridos.
Ismael Seidel dit (16:32)
Os dados em espiral devem ser gerados a partir de algoritmos que você
mesmo vai implementar. Inclua no algoritmo a possibilidade de introduzir
ruído na geração dos dados (através, por exemplo, de uma variável aleatória
que modifica levemente o comprimento do raio gerado para o próximo
ponto).
Observe que na espiral dupla cada braço da espiral em seu total
representa uma classe.
    O programa deve ser capaz de desenhar os padrões na tela com cores
    distintas para cada classe.
    Deve ser possível entrar com padrões arbitrários (2D e ND) para que o
    programa os classifique.
*/
