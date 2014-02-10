/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: numericmethods.h
 *
 * Descripción: Implementa algunos métodos matemáticos.
 */

#ifndef NUMERICMETHODS_H
#define NUMERICMETHODS_H

#include <QVector>

class NumericMethods
{
    public:
        NumericMethods();

        QVector<double> rungeKutta4(double t0, double x0, double y0, double z0, double a, double b, double c, double dt, double f( double t, double x, double y, double z, double m ), double g( double t, double x, double y, double z, double m ), double h( double t, double x, double y, double z, double m ));
};

#endif // NUMERICMETHODS_H
