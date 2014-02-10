/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: mainwindow.cpp
 *
 */

#include "mainwindow.h"
#include "lienzo.h"
#include "panel.h"

#include <QHBoxLayout>
#include <QTextCodec>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);

    QHBoxLayout *layout = new QHBoxLayout;

    lienzo = new Lienzo;
    layout->addWidget(lienzo);

    panel = new Panel;
    layout->addWidget(panel);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);


    this->setCentralWidget(widget);
    this->setWindowTitle(tr("Vida Artificial - Atractores"));

    connect(panel,SIGNAL(drawSignal()),lienzo,SLOT(updateGL()));
    connect(panel,SIGNAL(systemSignal(int)),lienzo,SLOT(setSystem(int)));
    connect(panel,SIGNAL(typeSignal(int)),lienzo,SLOT(setType(int)));
    connect(panel,SIGNAL(initValueChangeSignal(QVector<double>)),lienzo,SLOT(setInit(QVector<double>)));
    connect(panel,SIGNAL(startTimerSignal()),lienzo,SLOT(startTime()));
}

MainWindow::~MainWindow()
{
    delete lienzo;
    delete panel;

    lienzo = 0;
    panel = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
            case Qt::Key_Escape:
                    //QCoreApplication::exit();
                    break;
            case Qt::Key_A:
                this->lienzo->plusAngleX(0.7);
                break;
            case Qt::Key_D:
                this->lienzo->plusAngleX(-0.7);
                break;
            case Qt::Key_W:
                this->lienzo->plusAngleY(0.7);
                break;
            case Qt::Key_S:
                 this->lienzo->plusAngleY(-0.7);
                 break;
            case Qt::Key_PageUp:
                this->lienzo->plusZ(0.5);
                break;
            case Qt::Key_PageDown:
                this->lienzo->plusZ(-0.5);
                break;
            case Qt::Key_T:
                this->lienzo->plusPosY(0.7);
                break;
            case Qt::Key_G:
                this->lienzo->plusPosY(-0.7);
                break;
            case Qt::Key_F:
                this->lienzo->plusPosX(-0.7);
                break;
            case Qt::Key_H:
                this->lienzo->plusPosX(0.7);
    }
    this->lienzo->updateGL();
}
