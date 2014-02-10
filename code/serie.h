/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: serie.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Crea las series temporales de multiples sistemas, tanto discretos como continuos
*/

#ifndef SERIES_H
#define SERIES_H

#include "definitions.h"

class Serie
{
public:
    Serie();
    Serie(Serie &serie);
    ~Serie();

    void calcularSerie(int N);
    double* getSerieX();
    double* getSerieF();

    void setParametrosSistema(double x0, double y0, double z0, double a, double b, double c, double d);
    void setParametrosControl(double K);
    void setTipo(System tipo);
    void setRetardo(int retardo);
    void setX0(double x0);
    void setY0(double y0);
    void setA(double a);
    void setB(double b);
    void setC(double c);
    void setD(double d);
    void setRuido(bool ruido);
    void setIntensidadRuido(double intensidadRuido);

    double getX0();
    double getY0();
    double getA();
    double getB();
    double getC();
    double getD();
    double getK();
    double getRetardo();
    System getTipo();
    bool getRuido();
    double getIntesidadRuido();

private:
    System miTipo;
    double K, a, b, c, d, x0, y0, z0;
    int retardo;
    double *x, *xR, *f;
    bool ruido;
    double intensidadRuido,mediaRuido,desvRuido;

    void ecuacionLogistica(int N);
    void sistemaHenon(int N);
    void sistemaTinkerbell(int N);
    void sistemaIkeda(int N);
    void sistemaLorenz(int N);
    double control(double st, double stm);

};

#endif // SERIES_H
