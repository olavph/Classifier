#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "datum.h"
#include "class.h"
#include "generator.h"
#include "classifier.h"


#define WIDTH 500
#define HEIGHT 500
#define GOLDEN_RATIO 1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788067520876689250171169620703222104321626954862629631361443814975870122034080588795445474924618569536486444924104432077134494704956584678850987433944221254487706647809158846074998871240076521705751797883416625624940758906970400028121042762177111777805315317141011704666599146697987317613560067087480710131795236894275219484353056783002287856997829778347845878228911097625003026961561700250464338243776486102838312683303724292675263116533924731671112115881863851331620384005222165791286675294654906811317159934323597349498509040947621322298101726107059611645629909816290555208524790352406020172799747175342777592778625619432082750513121815628551222480939471234145170223735805772786160086883829523045926478780178899219902707769038953219681986151437803149974110692608867429622675756052317277752035361393621076738937645560606059216589466759551900400555908950229530942312482355212212415444006470340565734797663972394949946584578873039623090375033993856210242369025138680414577995698122445747178034173126453220416397232134044449487302315417676893752103068737880344170093954409627955898678723209512426893557309704509595684401755519881921802064052905518934947592600734852282101088194644544222318891319294689622002301443770269923007803085261180754519288770502109684249362713592518760777884665836150238913493333122310533923213624319263728910670503399282265263556209029798642472759772565508615487543574826471814145127000602389016207773224499435308899909501680328112194320481964387675863314798571911397815397807476150772211750826945863932045652098969855567814106968372884058746103378105444390943683583581381131168993855576975484149144534150912954070050194775486163075422641729394680367319805861833918328599130396072014455950449779212076124785645916160837059498786006970189409886400764436170933417270919143365013715
#define POINT_RADIUS 2

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(QRect(0,0,WIDTH,HEIGHT), this);
    ui->DrawingArea->setScene(scene);

    Class * c = new Class(QColor(255,0,0), "a");
    Class * d = new Class(QColor(0,255,0), "b");
    classes.push_back(c);
    classes.push_back(d);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    this->drawFromFile(fileName);
    emit fileSelected(fileName);
}

void MainWindow::generateRandomSet()
{
    QRect bounds(QRect(ui->RandomVariableMinimumValue1->value(),
                 ui->RandomVariableMinimumValue1->value(),
                 ui->RandomVariableMaximumValue1->value(),
                 ui->RandomVariableMaximumValue1->value()));
    QVector<Datum> * generatedPoints = Generator::randomSet(ui->RandomNumberOfPointsSpinBox->value(), bounds, classes);
    for(int i = 0; i < generatedPoints->size(); i++){
        drawDatum(generatedPoints->at(i));
    }
    points += *generatedPoints;
}

void MainWindow::generateSpiral()
{
    QRect bounds(QRect(ui->SpiralMinimumXSpinBox->value(),
                 ui->SpiralMinimumYSpinBox->value(),
                 ui->SpiralMaximumXSpinBox->value(),
                 ui->SpiralMaximumYSpinBox->value()));
    QVector<Datum> * generatedPoints = Generator::spiral(bounds,
                                                ui->SpiralRadiusBaseSpinBox->value(),
                                                ui->SpiralRadiusIncreaseFactorSpinBox->value(),
                                                0, ui->SpiralNoiseSpinBox->value(), classes.at(0));
    for(int i = 0; i < generatedPoints->size(); i++){
        drawDatum(generatedPoints->at(i));
    }
    points += *generatedPoints;
}

void MainWindow::generateDoubleSpiral()
{
    QRect bounds(QRect(ui->SpiralMinimumXSpinBox->value(),
                 ui->SpiralMinimumYSpinBox->value(),
                 ui->SpiralMaximumXSpinBox->value(),
                 ui->SpiralMaximumYSpinBox->value()));
    QVector<Datum> * generatedPoints = Generator::doubleSpiral(bounds,
                                                ui->SpiralRadiusBaseSpinBox->value(),
                                                ui->SpiralRadiusIncreaseFactorSpinBox->value(),
                                                0, ui->SpiralNoiseSpinBox->value(), classes.at(0), classes.at(1));
    for(int i = 0; i < generatedPoints->size(); i++){
        drawDatum(generatedPoints->at(i));
    }
    points += *generatedPoints;
}

void MainWindow::clear()
{
    points.clear();
    scene->clear();
}



QVector<Datum>* read(QString nomeDoArquivo, int n){
    // assume-se que o arquivo de entrada seja formado por d1, d2, ..., dn, nomeDaClasse\n
    ifstream fp_in;  // declarations of streams fp_in
    string arq = nomeDoArquivo.toStdString();
    fp_in.open(arq.c_str(), ios::in);

    QVector<double> vec;
    QVector<Datum>* result = new QVector<Datum>();

    char virgula;
    string className;

    double temp;

    while (!fp_in.eof())
    {
        for (int dim = 0; dim < n; dim++) {
            fp_in >> temp;
            fp_in >> virgula;
            vec.push_back(temp);
            qDebug("%f\n", temp);
        }
        fp_in >> className;

        Datum data(vec, new Class(QColor(255,0,255),QString(className.c_str())));
        result->push_back(data);
        vec.clear();
    }

    //por algum motivo bizarro isso retorna sempre uma repetiçao da ultima coord, e da ultima classe.... eliminar! então:
    result->pop_back(); //POG!

    fp_in.close();   // close the streams

    return result;
}

void MainWindow::drawFromFile(QString f)
{
    QVector<Datum> * points = read(f, 4);
    for(int i = 0; i < points->size(); i++){
        this->drawDatum(points->at(i));
        qDebug("%f, %f", points->at(i).getCoordinate(0), points->at(i).getCoordinate(1));
    }
}


void MainWindow::openFile()
{
    QString filePath = ui->FilePathTextBox->text();
    if(filePath.size() == 0)
        return;
    QVector<Datum> * points = read(filePath, 4);
    for(int i = 0; i < points->size(); i++){
        drawDatum(points->at(i));
    }
}

void MainWindow::drawDatum(Datum d)
{
    scene->addEllipse(d.getCoordinate(0)-POINT_RADIUS, d.getCoordinate(1)-POINT_RADIUS, POINT_RADIUS*2, POINT_RADIUS*2, QPen(d.myOwnSuperSecretClass->getColor()), QBrush(d.myOwnSuperSecretClass->getColor()));
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
