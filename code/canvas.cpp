/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: canvas.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);

    ui->qwtPlot1->setTitle(tr("Sistema Sin control"));
    ui->qwtPlot1->setCanvasBackground( Qt::white );
    ui->qwtPlot1->setAxisTitle(QwtPlot::xBottom, "n");
    ui->qwtPlot1->setAxisTitle(QwtPlot::yLeft, "X");

    ui->qwtPlot2->setTitle(tr("Sistema Con Control"));
    ui->qwtPlot2->setCanvasBackground( Qt::white );
    ui->qwtPlot2->setAxisTitle(QwtPlot::xBottom, "n");
    ui->qwtPlot2->setAxisTitle(QwtPlot::yLeft, "X");

    ui->qwtPlot3->setTitle(tr("Acción de Control"));
    ui->qwtPlot3->setCanvasBackground( Qt::white );
    ui->qwtPlot3->setAxisTitle(QwtPlot::xBottom, "n");
    ui->qwtPlot3->setAxisTitle(QwtPlot::yLeft, "F");

    // Insert new curves
    this->curve1 = new QwtPlotCurve;
    curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    curve1->attach( ui->qwtPlot1 );

    this->curve2 = new QwtPlotCurve;
    curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
    curve2->attach( ui->qwtPlot2 );

    this->curve3 = new QwtPlotCurve;
    curve3->setRenderHint( QwtPlotItem::RenderAntialiased );
    curve3->setPen( QPen(Qt::red) );
    curve3->attach( ui->qwtPlot3 );
}

Canvas::~Canvas()
{
    delete ui;
    delete curve1;
    delete curve2;
    delete curve3;
}

void Canvas::draw(double k, Serie &serie, int amountData)
{
    // Create data
    double n[amountData];
    for(int i=0;i<amountData;i++)
    {
        n[i] = i;
    }
    double *temp = new double[amountData];
    serie.setParametrosControl(0);
    serie.calcularSerie(amountData);
    temp = serie.getSerieX();
    double *serieSinControl = new double[amountData];
    for(int i=0;i<amountData;i++)
    {
        serieSinControl[i] = temp[i];
    }
    serie.setParametrosControl(k);
    serie.calcularSerie(amountData);
    double *serieConControl = serie.getSerieX();
    double *serieControl = serie.getSerieF();

    //asignar datos
    curve1->setSamples(n,serieSinControl,amountData);
    curve2->setSamples(n,serieConControl,amountData);
    curve3->setSamples(n,serieControl,amountData);
    ui->qwtPlot1->replot();
    ui->qwtPlot2->replot();
    ui->qwtPlot3->replot();

    delete serieSinControl;
    serieSinControl = 0;
    serieConControl = 0;
    serieControl = 0;
    temp = 0;
}
