#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "datum.h"
#include "class.h"
#include "generator.h"
#include "classifier.h"
#include "distancecalculation.h"
#include "euclidiandistance.h"
#include "manhattandistance.h"
#include "triple.h"
#include "circle.h"
#include "line.h"
#include "singleton.h"
#include "ibl/ibl1.h"
#include "ibl/ibl2.h"
#include "ibl/ibl3.h"
#include "ibl/ibl4.h"


#define WIDTH 500
#define HEIGHT 500
#define GOLDEN_RATIO 1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788067520876689250171169620703222104321626954862629631361443814975870122034080588795445474924618569536486444924104432077134494704956584678850987433944221254487706647809158846074998871240076521705751797883416625624940758906970400028121042762177111777805315317141011704666599146697987317613560067087480710131795236894275219484353056783002287856997829778347845878228911097625003026961561700250464338243776486102838312683303724292675263116533924731671112115881863851331620384005222165791286675294654906811317159934323597349498509040947621322298101726107059611645629909816290555208524790352406020172799747175342777592778625619432082750513121815628551222480939471234145170223735805772786160086883829523045926478780178899219902707769038953219681986151437803149974110692608867429622675756052317277752035361393621076738937645560606059216589466759551900400555908950229530942312482355212212415444006470340565734797663972394949946584578873039623090375033993856210242369025138680414577995698122445747178034173126453220416397232134044449487302315417676893752103068737880344170093954409627955898678723209512426893557309704509595684401755519881921802064052905518934947592600734852282101088194644544222318891319294689622002301443770269923007803085261180754519288770502109684249362713592518760777884665836150238913493333122310533923213624319263728910670503399282265263556209029798642472759772565508615487543574826471814145127000602389016207773224499435308899909501680328112194320481964387675863314798571911397815397807476150772211750826945863932045652098969855567814106968372884058746103378105444390943683583581381131168993855576975484149144534150912954070050194775486163075422641729394680367319805861833918328599130396072014455950449779212076124785645916160837059498786006970189409886400764436170933417270919143365013715
#define POINT_RADIUS 5

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

    ibl = new IBL1();
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
    QSet<Datum*> generatedPoints = Generator::randomSet(ui->RandomNumberOfPointsSpinBox->value(), bounds, classes);

    dataContainer.addData(generatedPoints);
    redraw();
}

void MainWindow::generateSpiral()
{
    QRect bounds(QRect(ui->SpiralMinimumXSpinBox->value(),
                 ui->SpiralMinimumYSpinBox->value(),
                 ui->SpiralMaximumXSpinBox->value(),
                 ui->SpiralMaximumYSpinBox->value()));
    QSet<Datum*> generatedPoints = Generator::spiral(bounds,
                                                ui->SpiralRadiusBaseSpinBox->value(),
                                                ui->SpiralRadiusIncreaseFactorSpinBox->value(),
                                                0, ui->SpiralNoiseSpinBox->value(), classes.at(0));

    dataContainer.addData(generatedPoints);
    redraw();
}

void MainWindow::generateDoubleSpiral()
{
    QRect bounds(QRect(ui->SpiralMinimumXSpinBox->value(),
                 ui->SpiralMinimumYSpinBox->value(),
                 ui->SpiralMaximumXSpinBox->value(),
                 ui->SpiralMaximumYSpinBox->value()));
    QSet<Datum*> generatedPoints = Generator::doubleSpiral(bounds,
                                                ui->SpiralRadiusBaseSpinBox->value(),
                                                ui->SpiralRadiusIncreaseFactorSpinBox->value(),
                                                0, ui->SpiralNoiseSpinBox->value(), classes.at(0), classes.at(1));

    dataContainer.addData(generatedPoints);
    redraw();
}

void MainWindow::clear()
{
    dataContainer.clearData();
    scene->clear();
}

QSet<Datum*> read(QString nomeDoArquivo, int n){
    // assume-se que o arquivo de entrada seja formado por d1, d2, ..., dn, nomeDaClasse\n
    ifstream fp_in;  // declarations of streams fp_in
    string arq = nomeDoArquivo.toStdString();
    fp_in.open(arq.c_str(), ios::in);

    QVector<double> vec;
    QVector<Datum*> result;

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

        Datum * data = new Datum(vec, new Class(QColor(255,0,255),QString(className.c_str())));
        result.push_back(data);
        vec.clear();
    }

    //por algum motivo bizarro isso retorna sempre uma repetiçao da ultima coord, e da ultima classe.... eliminar! então:
    result.pop_back(); //POG!

    fp_in.close();   // close the streams

    return QSet<Datum*>::fromList(QList<Datum*>::fromVector(result));
}

void MainWindow::drawFromFile(QString f)
{
    QSet<Datum*> readPoints = read(f, 4);

    dataContainer.addData(readPoints);
    redraw();
}


void MainWindow::openFile()
{
    QString filePath = ui->FilePathTextBox->text();
    if(filePath.size() == 0)
        return;
    QSet<Datum*> points = read(filePath, 4);
    foreach (Datum * d, points)
        drawDatum(d);
}

void MainWindow::addDatum()
{
    double x = ui->AddDataXSpinBox->value();
    double y = ui->AddDataYSpinBox->value();
    Datum * newDatum = new Datum(x, y);

    DistanceCalculation * algorithm;
    if(ui->EuclidianRadioButton->isChecked())
        algorithm = Singleton<EuclidianDistance>::instance();
    else if(ui->ManhattanRadioButton->isChecked())
        algorithm = Singleton<ManhattanDistance>::instance();

    size_t k = ui->kNNSpinBox->value();
    if(ui->NNRadioButton->isChecked())
        Classifier::nN(algorithm, newDatum, dataContainer.getData());
    else if(ui->kNNRadioButton->isChecked())
        Classifier::kNN(algorithm, k, newDatum, dataContainer.getData());

    dataContainer.addDatum(newDatum);
    redraw();
}

void MainWindow::fillDrawArea()
{
    DistanceCalculation * algorithm;
    if(ui->EuclidianRadioButton->isChecked())
        algorithm = Singleton<EuclidianDistance>::instance();
    else if(ui->ManhattanRadioButton->isChecked())
        algorithm = Singleton<ManhattanDistance>::instance();

    size_t k = ui->kNNSpinBox->value();

    for (int i = 0; i < WIDTH; i+=2) {
        for (int j = 0; j < HEIGHT; j+=2) {
            Datum * newDatum = new Datum(i, j);
            if(ui->NNRadioButton->isChecked())
                Classifier::nN(algorithm, newDatum, ibl->conceptualDescriptor());
            else if(ui->kNNRadioButton->isChecked())
                Classifier::kNN(algorithm, k, newDatum, ibl->conceptualDescriptor());
            dataContainer.addDatum(newDatum);
        }
    }

    redraw();
}

void MainWindow::trainWithData()
{
    delete ibl;
    if (ui->IBLAlgorithm1RadioButton->isChecked())
        ibl = new IBL1();
    else if (ui->IBLAlgorithm2RadioButton->isChecked())
        ibl = new IBL2();
    else if (ui->IBLAlgorithm3RadioButton->isChecked())
        ibl = new IBL3();
    else if (ui->IBLAlgorithm4RadioButton->isChecked())
        ibl = new IBL4();

    ibl->train(dataContainer.getData(), Singleton<EuclidianDistance>::instance());
    dataContainer.clearData();
    redraw();
}

void MainWindow::drawDatum(Datum * d, QColor color)
{
    QPen pen(color);
    scene->addEllipse(d->getCoordinate(0)-POINT_RADIUS, d->getCoordinate(1)-POINT_RADIUS, POINT_RADIUS*2, POINT_RADIUS*2, pen, QBrush(d->myOwnSuperSecretClass->getColor()));
}

void MainWindow::drawPixel(Datum * d)
{
    QPen pen(d->myOwnSuperSecretClass->getColor());
    scene->addLine(d->x(), d->y(), d->x(), d->y(), pen);
}

void MainWindow::drawData()
{
    foreach (Datum * d, dataContainer.getData())
        drawPixel(d);
}

void MainWindow::drawConceptualDescriptor()
{
    foreach (Datum * d, ibl->conceptualDescriptor())
        drawDatum(d, QColor(Qt::black));
}

void MainWindow::drawIncorrectlyClassifiedData()
{
    foreach (Datum * d, ibl->incorrectlyClassifiedData())
        drawDatum(d, QColor(Qt::red));
}

void MainWindow::drawDelaunayTriangles()
{
    foreach (Triple * t, dataContainer.getTriples()) {
        double xA = t->getA()->x();
        double yA = t->getA()->y();
        double xB = t->getB()->x();
        double yB = t->getB()->y();
        double xC = t->getC()->x();
        double yC = t->getC()->y();

        scene->addLine(xA, yA, xB, yB, QPen(QColor(102,111,208)));
        scene->addLine(xB, yB, xC, yC, QPen(QColor(102,111,208)));
        scene->addLine(xC, yC, xA, yA, QPen(QColor(102,111,208)));
    }
}

void MainWindow::drawDelaunayCircles()
{
    foreach (Triple * t, dataContainer.getTriples()) {
        Circle circle = t->circumcircle();

        QRect bounds(QRect(circle.getCenter().x() - circle.getRadius(),
                    circle.getCenter().y() - circle.getRadius(),
                    2 * circle.getRadius(),
                    2 * circle.getRadius()));
        scene->addEllipse(bounds);
    }
}

void MainWindow::drawVoronoiDiagram()
{
    foreach (Triple * currentTriple, dataContainer.getTriples()) {
        foreach (Triple * neighbor, dataContainer.getTriples()) {
            double x1 = currentTriple->centroid().x();
            double y1 = currentTriple->centroid().y();
            double x2 = neighbor->centroid().x();
            double y2 = neighbor->centroid().y();
            scene->addLine(x1, y1, x2, y2);
            if (currentTriple->isBorder())
                scene->addLine(x1, y1, currentTriple->toInfinityAndBeyondPoint().x(), currentTriple->toInfinityAndBeyondPoint().y());
        }
    }
}

void MainWindow::redraw()
{
    scene->clear();
    if (ui->DrawDataPointsCheckBox->isChecked())
        drawData();
    if (ui->DrawConceptualDescriptorCheckBox->isChecked())
        drawConceptualDescriptor();
    if (ui->DrawIncorrectlyClassifiedDataCheckBox->isChecked())
        drawIncorrectlyClassifiedData();
    if (ui->DrawDelaunayTrianglesCheckBox->isChecked())
        drawDelaunayTriangles();
    if (ui->DrawDelaunayCirclesCheckBox->isChecked())
        drawDelaunayCircles();
    if (ui->DrawVoronoiCheckBox->isChecked())
        drawVoronoiDiagram();
}
