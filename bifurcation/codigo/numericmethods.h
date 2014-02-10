/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: numericmethods.h
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 * Descripción: Algunas funciones matemáticas.
 */

#ifndef NUMERICMETHODS_H
#define NUMERICMETHODS_H

#include <QVector>

class NumericMethods
{
    public:
        NumericMethods();

        QVector<double> rungeKutta4(double t0, double x0, double y0, double z0, double s, double r, double b, double dt, double f( double x, double y, double z, double m ), double g( double x, double y, double z, double m ), double h( double x, double y, double z, double m ));
};

#endif // NUMERICMETHODS_H
