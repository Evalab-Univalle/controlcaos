/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: numericmethos.cpp
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 */

#include "numericmethods.h"

NumericMethods::NumericMethods()
{
}

QVector<double> NumericMethods::rungeKutta4(double t0, double x0, double y0, double z0, double s, double r, double b, double dt, double f( double x, double y, double z, double m ), double g( double x, double y, double z, double m ), double h( double x, double y, double z, double m ))
{
    double f11, f12, f13;
    double f21, f22, f23;
    double f31, f32, f33;
    double f41, f42, f43;
    double x1, y1, z1, x, y, z, t;

    f11 = f ( x0, y0, z0, s );
    f12 = g ( x0, y0, z0, r );
    f13 = h ( x0, y0, z0, b );


    x = x0 + dt * f11 / 2;
    y = y0 + dt * f12 / 2;
    z = z0 + dt * f13 / 2;
    t = t0 + dt/2;

    f21 = f ( x, y, z, s );
    f22 = g ( x, y, z, r );
    f23 = h ( x, y, z, b );


    x = x0 + dt * f21 / 2;
    y = y0 + dt * f22 / 2;
    z = z0 + dt * f23 / 2;

    f31 = f ( x, y, z, s );
    f32 = g ( x, y, z, r );
    f33 = h ( x, y, z, b );

    x = x0 + dt * f31;
    y = y0 + dt * f32;
    z = z0 + dt * f33;
    t = t0 + dt;

    f41 = f ( x, y, z, s );
    f42 = g ( x, y, z, r );
    f43 = h ( x, y, z, b );

    x1 = x0 + dt * ( f11 + 2.0 * f21 + 2.0 * f31 + f41 ) / 6.0;
    y1 = y0 + dt * ( f12 + 2.0 * f22 + 2.0 * f32 + f42 ) / 6.0;
    z1 = z0 + dt * ( f13 + 2.0 * f23 + 2.0 * f33 + f43 ) / 6.0;

    QVector<double> temp;
    temp.append(x1);
    temp.append(y1);
    temp.append(z1);

    return temp;
}
