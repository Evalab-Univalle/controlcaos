/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: matematica.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "matematica.h"
#include <stdlib.h>
#include <cmath>

Matematica::Matematica()
{
}

/*
 * Método getNumeroGauss: retorna un número con distribución normal según lo argumentos.
 * Usa el teorema del límite central para generarlo.
 */
double Matematica::getNumeroGauss(double media, double desviacion)
{
    double sum=0.0;
    int n=30;
    for(int i=0;i<n;i++)
    {
        sum += (double)rand() / (double)RAND_MAX;
    }
    return desviacion*sqrt(12.0/(double)n)*(sum-((double)n/2.0))+media;
}

bool Matematica::isNan(double num)
{
    double a = num;
    return a != num;
}

/*
 * Método rungeKutta4: implementación del método de Runge Kutta de orden cuatro para solucionar sistemas de ecuaciones diferenciales.
 */
QVector<double> Matematica::rungeKutta4(double t0, double x0, double y0, double z0, double a, double b, double c, double dt, double f( double x, double y, double z, double m ), double g( double x, double y, double z, double m ), double h( double x, double y, double z, double m ))
{
    double f11, f12, f13;
    double f21, f22, f23;
    double f31, f32, f33;
    double f41, f42, f43;
    double x1, y1, z1, x, y, z, t;

    f11 = f ( x0, y0, z0, a );
    f12 = g ( x0, y0, z0, b );
    f13 = h ( x0, y0, z0, c );


    x = x0 + dt * f11 / 2;
    y = y0 + dt * f12 / 2;
    z = z0 + dt * f13 / 2;
    t = t0 + dt/2;

    f21 = f ( x, y, z, a );
    f22 = g ( x, y, z, b );
    f23 = h ( x, y, z, c );


    x = x0 + dt * f21 / 2;
    y = y0 + dt * f22 / 2;
    z = z0 + dt * f23 / 2;

    f31 = f ( x, y, z, a );
    f32 = g ( x, y, z, b );
    f33 = h ( x, y, z, c );

    x = x0 + dt * f31;
    y = y0 + dt * f32;
    z = z0 + dt * f33;
    t = t0 + dt;

    f41 = f ( x, y, z, a );
    f42 = g ( x, y, z, b );
    f43 = h ( x, y, z, c );

    x1 = x0 + dt * ( f11 + 2.0 * f21 + 2.0 * f31 + f41 ) / 6.0;
    y1 = y0 + dt * ( f12 + 2.0 * f22 + 2.0 * f32 + f42 ) / 6.0;
    z1 = z0 + dt * ( f13 + 2.0 * f23 + 2.0 * f33 + f43 ) / 6.0;

    QVector<double> r;
    r.append(x1);
    r.append(y1);
    r.append(z1);

    return r;
}

double Matematica::dx_Lorenz(double x, double y, double z, double s)
{
    double m = s*(y-x);
    return m;
}

double Matematica::dy_Lorenz(double x, double y, double z, double r)
{
    double m = r*x - y - x*z;
    return m;
}

double Matematica::dz_Lorenz(double x, double y, double z, double b)
{
    double m = x*y - b*z;
    return m;
}
