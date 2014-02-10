/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: mainwindow.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Interfaz gráfica principal.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCursor>
#include "board.h"
#include "canvas.h"
#include "serie.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Board *board;
    Canvas *canvas;
    Serie serie;
    QCursor cursor;

    void writeInfo(double k, double mink, double maxk);

private slots:
    void runSlot(int,int,int,int,int,int,int,int,double,double,double,double,double,double,double,bool,double);
};

#endif // MAINWINDOW_H
