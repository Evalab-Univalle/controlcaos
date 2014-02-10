/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: function.h
 *
 * Descripción: contiene definiciones usadas con regularidad por algunas clases del proyecto.
 */

#ifndef FUNCTION_H
#define FUNCTION_H

double dx_Lorenz(double t, double x, double y, double z, double a);
double dy_Lorenz(double t, double x, double y, double z, double b);
double dz_Lorenz(double t, double x, double y, double z, double c);

double dx_Lorenz(double t, double x, double y, double z, double a)
{
    double r = a*x + y*z;
    return r;
}

double dy_Lorenz(double t, double x, double y, double z, double b)
{
    double r = b*(y-z);
    return r;
}

double dz_Lorenz(double t, double x, double y, double z, double c)
{
    double r = -x*y + c*y - z;
    return r;
}

double f_GumowiskMira(double x, double a)
{
    double w = 1+x*x;
    return a*x + (2*(1-a)*x*x)/w;
}

#endif // FUNCTION_H
