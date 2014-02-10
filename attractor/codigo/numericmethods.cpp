/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: numericmethods.cpp
 *
 */

#include "numericmethods.h"

NumericMethods::NumericMethods()
{
}

QVector<double> NumericMethods::rungeKutta4(double t0, double x0, double y0, double z0, double a, double b, double c, double dt, double f( double t, double x, double y, double z, double m ), double g( double t, double x, double y, double z, double m ), double h( double t, double x, double y, double z, double m ))
{
    double f11, f12, f13;
    double f21, f22, f23;
    double f31, f32, f33;
    double f41, f42, f43;
    double x1, y1, z1, x, y, z, t;

    f11 = f ( t0, x0, y0, z0, a );
    f12 = g ( t0, x0, y0, z0, b );
    f13 = h ( t0, x0, y0, z0, c );


    x = x0 + dt * f11 / 2;
    y = y0 + dt * f12 / 2;
    z = z0 + dt * f13 / 2;
    t = t0 + dt/2;

    f21 = f ( t, x, y, z, a );
    f22 = g ( t, x, y, z, b );
    f23 = h ( t, x, y, z, c );


    x = x0 + dt * f21 / 2;
    y = y0 + dt * f22 / 2;
    z = z0 + dt * f23 / 2;

    f31 = f ( t, x, y, z, a );
    f32 = g ( t, x, y, z, b );
    f33 = h ( t, x, y, z, c );

    x = x0 + dt * f31;
    y = y0 + dt * f32;
    z = z0 + dt * f33;
    t = t0 + dt;

    f41 = f ( t, x, y, z, a );
    f42 = g ( t, x, y, z, b );
    f43 = h ( t, x, y, z, c );

    x1 = x0 + dt * ( f11 + 2.0 * f21 + 2.0 * f31 + f41 ) / 6.0;
    y1 = y0 + dt * ( f12 + 2.0 * f22 + 2.0 * f32 + f42 ) / 6.0;
    z1 = z0 + dt * ( f13 + 2.0 * f23 + 2.0 * f33 + f43 ) / 6.0;

    QVector<double> r;
    r.append(x1);
    r.append(y1);
    r.append(z1);

    return r;
}
