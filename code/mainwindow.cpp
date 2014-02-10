/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: mainwindow.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algoritmo.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    this->ui->setupUi(this);
    this->canvas = new Canvas(this);
    this->ui->centralWidget->layout()->addWidget(canvas);
    this->board = new Board(this);
    this->ui->centralWidget->layout()->addWidget(board);

    connect(this->board,SIGNAL(runSignal(int,int,int,int,int,int,int,int,double,double,double,double,double,double,double,bool,double)),this,SLOT(runSlot(int,int,int,int,int,int,int,int,double,double,double,double,double,double,double,bool,double)));
    this->setCursor(this->cursor);
    setWindowTitle(tr("Control de Sistemas Dinámicos Caóticos"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
    delete canvas;
}

void MainWindow::runSlot(int amountGeneration,int amountIndividual,int amountRun,int amountData,int stablePeriod,int system,int amountOrbits,int delay,double x,double y,double z,double a,double b,double c,double d, bool noise, double noiseIntensity)
{
    int amountGenes = 1;

    this->serie.setTipo(System(system));
    this->serie.setParametrosSistema(x,y,z,a,b,c,d);
    this->serie.setRetardo(delay);
    this->serie.setRuido(noise);
    this->serie.setIntensidadRuido(noiseIntensity);

    Algoritmo algorithm(amountIndividual,amountGenes,amountGeneration,amountRun,&this->serie);
    algorithm.setOrbitas(amountOrbits,0);//para este caso en particular se pasa 0 como apuntador ya que no hay orbitas
    algorithm.setTamanoSerie(amountData);
    algorithm.setPeriodoEstable(stablePeriod);
    QCursor cursor(Qt::WaitCursor);
    this->setCursor(cursor);
    algorithm.buscar();
    cursor.setShape(Qt::ArrowCursor);
    this->setCursor(cursor);
    if(algorithm.getSolucionEncontrada()){
        double *result = algorithm.getResultado();
        double k = result[0];
        this->canvas->draw(k,this->serie,amountData);
        delete result;
        result = 0;
        this->writeInfo(k,algorithm.getMinK(),algorithm.getMaxK());
    }else{
        this->board->writeInfoSlot("--> Intervalo no encontrado...\n");
    }

}

void MainWindow::writeInfo(double k, double mink, double maxk)
{
    QString info = "--> K = " + QString::number(k) + "\n";
    info += "   " + QString::number(mink) + " <= K <= " + QString::number(maxk) + "\n";
    this->board->writeInfoSlot(info);
}
