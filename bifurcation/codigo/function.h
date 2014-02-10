/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: function.h
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 * Descripción: Funciones que representan el sistema de lorenz
 */

#ifndef FUNCTION_H
#define FUNCTION_H

double dx_Lorenz(double x, double y, double z, double s);
double dy_Lorenz(double x, double y, double z, double r);
double dz_Lorenz(double x, double y, double z, double b);

double dx_Lorenz(double x, double y, double z, double s)
{
    double m = s*(y-x);
    return m;
}

double dy_Lorenz(double x, double y, double z, double r)
{
    double m = r*x - y - x*z;
    return m;
}

double dz_Lorenz(double x, double y, double z, double b)
{
    double m = x*y - b*z;
    return m;
}

#endif // FUNCTION_H
