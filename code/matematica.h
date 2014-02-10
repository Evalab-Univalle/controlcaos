/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: matematica.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Implementación de algunas funciones matemáticas.
*/

#ifndef MATEMATICA_H
#define MATEMATICA_H

#include <QVector>

class Matematica
{
public:
    Matematica();
    double static getNumeroGauss(double media, double desviacion);
    bool static isNan(double num);
    double static dx_Lorenz(double x, double y, double z, double s);
    double static dy_Lorenz(double x, double y, double z, double r);
    double static dz_Lorenz(double x, double y, double z, double b);

    QVector<double> static rungeKutta4(double t0, double x0, double y0, double z0, double a, double b, double c, double dt, double f(double x, double y, double z, double m ), double g(double x, double y, double z, double m ), double h(double x, double y, double z, double m ));
};

#endif // MATEMATICA_H
