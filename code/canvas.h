/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: canvas.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Es una interfaz gráfica que permite visualizar el estado del sistema con control,
 * sin control y la acción de control aplicada. Hace uso de la libreria Qwt 6.0 http://qwt.sourceforge.net/
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <qwt_plot.h>
#include "serie.h"
#include <qwt_plot_curve.h>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT
    
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();
    void draw(double k, Serie &serie, int amountData);
    
private:
    Ui::Canvas *ui;
    QwtPlotCurve * curve1;
    QwtPlotCurve * curve2;
    QwtPlotCurve * curve3;

};

#endif // CANVAS_H
