/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: canvas.h
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 * Descripción: Dibuja el diagrama de bifurcación para diferentes sistemas
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <QGLWidget>
#include <QVector>

class Canvas : public QGLWidget
{
public:
    Canvas(int sistema, int cantidadPuntos);
    ~Canvas();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    enum Attractor {Logistica, Henon, Tinkerbell, Ikeda, Lorenz};
    Attractor atractor;
    int cantidadPuntos;
    void suavizar();
    void noSuavizar();

    QVector<double> ecuacionLogistica(double x0, double k, int N, int s);
    QVector<double> sistemaHenon(double x0, double y0, double a, double b, int N, int s);
    QVector<double> sistemaTinkerbell(double x0, double y0, double a, double b, double c, double d, int N, int s);
    QVector<double> sistemaIkeda(double x0, double y0, double a, double b, double c, double d, int N, int s);
    QVector<double> sistemaLorenz(double x0, double y0, double z0, double s, double r, double b, int N, int st);

};

#endif // CANVAS_H
