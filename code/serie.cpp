/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: serie.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "serie.h"
#include <stdlib.h>
#include <cmath>
#include "matematica.h"
#include <iostream>

Serie::Serie()
{
    this->x = 0;
    this->xR = 0; //sistemas con ruido y sin control
    this->f = 0;

    mediaRuido = 0;
    desvRuido = 1;
}

Serie::~Serie()
{
    delete x;
    delete xR;
    delete f;
}

void Serie::setParametrosSistema(double x0, double y0, double z0, double a, double b, double c, double d)
{
    this->x0 = x0;
    this->y0 = y0;
    this->z0 = z0;
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

void Serie::setParametrosControl(double K)
{
    this->K = K;
}

void Serie::setTipo(System tipo)
{
    this->miTipo = tipo;
}

void Serie::setRetardo(int retardo)
{
    this->retardo = retardo;
}

void Serie::ecuacionLogistica(int N)
{
    x[0] = this->x0;
    xR[0] = this->x0;
    f[0] = 0;
    double c,r;

    for(int i=1;i<N;i++)
    {
        if(i>this->retardo){
            c = this->control(x[i-1],x[i-this->retardo-1]);
        }else{
            c = 0;
        }
        x[i] = x[i-1]*(1-x[i-1])*this->a + c;
        f[i] = c;

        if(this->ruido){
            r = Matematica::getNumeroGauss(mediaRuido,desvRuido)*this->intensidadRuido;
            x[i] += r;
            if(this->K == 0){
                xR[i] = xR[i-1]*(1-xR[i-1])*this->a + r;
            }
        }
    }
}

void Serie::sistemaHenon(int N)
{
    double *y = new double[N];
    double *yR = new double[N];
    x[0] = this->x0;
    y[0] = this->y0;
    xR[0] = this->x0;
    yR[0] = this->y0;
    f[0] = 0;
    double c,r;

    for(int i=1;i<N;i++)
    {
        if(i>this->retardo){
            c = this->control(x[i-1],x[i-this->retardo-1]);
        }else{
            c = 0;
        }
        x[i] = y[i-1]-this->a*x[i-1]*x[i-1] + 1 + c;
        y[i] = this->b*x[i-1];
        f[i] = c;

        if(this->ruido){
            r = Matematica::getNumeroGauss(mediaRuido,desvRuido)*this->intensidadRuido;
            x[i] += r;
            if(this->K == 0){
                xR[i] = yR[i-1]-this->a*xR[i-1]*xR[i-1] + 1 + r;
                yR[i] = this->b*xR[i-1];
            }
        }
    }
    delete y;
    delete yR;
    y = 0;
    yR = 0;
}

void Serie::sistemaTinkerbell(int N)
{
    double *y = new double[N];
    double *yR = new double[N];
    x[0] = this->x0;
    y[0] = this->y0;
    xR[0] = this->x0;
    yR[0] = this->y0;
    f[0] = 0;
    double c,r;

    for(int i=1;i<N;i++)
    {
        if(i>this->retardo){
            c = this->control(x[i-1],x[i-this->retardo-1]);
        }else{
            c = 0;
        }
        x[i] = x[i-1]*x[i-1] - y[i-1]*y[i-1] + this->a*x[i-1] + this->b*y[i-1] + c;
        y[i] = 2*x[i-1]*y[i-1] + this->c*x[i-1] + this->d*y[i-1];
        f[i] = c;

        if(this->ruido){
            r = Matematica::getNumeroGauss(mediaRuido,desvRuido)*this->intensidadRuido;
            x[i] += r;
            if(this->K == 0){
                xR[i] = xR[i-1]*xR[i-1] - yR[i-1]*yR[i-1] + this->a*xR[i-1] + this->b*yR[i-1] + r;
                yR[i] = 2*xR[i-1]*yR[i-1] + this->c*xR[i-1] + this->d*yR[i-1];
            }
        }
    }
    delete y;
    delete yR;
    y = 0;
    yR = 0;
}

void Serie::sistemaIkeda(int N)
{
    double *y = new double[N];
    double *yR = new double[N];
    double u,c,r;
    x[0] = this->x0;
    y[0] = this->y0;
    f[0] = 0;

    for(int i=1;i<N;i++)
    {
        if(i>this->retardo){
            c = this->control(x[i-1],x[i-this->retardo-1]);
        }else{
            c = 0;
        }
        u = (this->c-this->d)/(1.0+x[i-1]*x[i-1]+y[i-1]*y[i-1]);
        x[i] = this->a+this->b*(x[i-1]*std::cos(u)-y[i-1]*std::sin(u)) + c;
        y[i] = this->b*(x[i-1]*std::sin(u)+y[i-1]*std::cos(u));
        f[i] = c;

        if(this->ruido){
            r = Matematica::getNumeroGauss(mediaRuido,desvRuido)*this->intensidadRuido;
            x[i] += r;
            if(this->K == 0){
                u = (this->c-this->d)/(1.0+xR[i-1]*xR[i-1]+yR[i-1]*yR[i-1]);
                xR[i] = this->a+this->b*(xR[i-1]*std::cos(u)-yR[i-1]*std::sin(u)) + r;
                yR[i] = this->b*(xR[i-1]*std::sin(u)+yR[i-1]*std::cos(u));
            }
        }
    }
    delete y;
    delete yR;
    y = 0;
    yR = 0;
}

void Serie::sistemaLorenz(int N)
{
    double c,r,*y,*z,*yR,*zR, dt=0.01, t0=0.0;
    y = new double[N];
    z = new double[N];
    yR = new double[N];
    zR = new double[N];
    QVector<double> result;
    x[0] = this->x0;
    y[0] = this->y0;
    z[0] = this->z0;
    xR[0] = this->x0;
    yR[0] = this->y0;
    zR[0] = this->z0;
    f[0] = 0;

    for(int i=1;i<N;i++)
    {
        if(i>this->retardo){
            c = this->control(x[i-1],x[i-this->retardo-1]);
        }else{
            c = 0;
        }
        result = Matematica::rungeKutta4(t0,x[i-1],y[i-1],z[i-1],this->a,this->b,this->c,dt,Matematica::dx_Lorenz,Matematica::dy_Lorenz,Matematica::dz_Lorenz);
        x[i]=result.at(0) + c;
        y[i]=result.at(1);
        z[i]=result.at(2);
        f[i] = c;

        if(this->ruido){
            r = Matematica::getNumeroGauss(mediaRuido,desvRuido)*this->intensidadRuido;
            x[i] += r;
            if(this->K == 0){
                result = Matematica::rungeKutta4(t0,xR[i-1],yR[i-1],zR[i-1],this->a,this->b,this->c,dt,Matematica::dx_Lorenz,Matematica::dy_Lorenz,Matematica::dz_Lorenz);
                xR[i]=result.at(0) + r;
                yR[i]=result.at(1);
                zR[i]=result.at(2);
            }
        }
        t0+=dt;
    }
    delete y;
    delete z;
    delete yR;
    delete zR;
    y = 0;
    z = 0;
    yR = 0;
    zR = 0;
}

double Serie::control(double st, double stm)
{
    return this->K*(stm-st);
}

void Serie::calcularSerie(int N)
{
    if(this->x != 0)
    {
        delete this->x;
        delete this->xR;
        delete this->f;

    }

    this->x = new double[N];
    this->xR = new double[N];
    this->f = new double[N];

    switch(miTipo)
    {
        case LogisticEcuation:
        {
            this->ecuacionLogistica(N);
            break;
        }
        case HenonSystem:
        {
            this->sistemaHenon(N);
            break;
        }
        case TinkerbellSystem:
        {
            this->sistemaTinkerbell(N);
            break;
        }
        case IkedaSystem:
        {
            this->sistemaIkeda(N);
            break;
        }
        case LorenzSystem:
        {
            this->sistemaLorenz(N);
        }
    }
}

double* Serie::getSerieX()
{
    if(this->K == 0 && this->ruido){
        return this->xR;
    }else{
        return this->x;
    }
}

double* Serie::getSerieF()
{
    return this->f;
}

void Serie::setX0(double x0)
{
    this->x0 = x0;
}

void Serie::setY0(double y0)
{
    this->y0 = y0;
}

void Serie::setA(double a)
{
    this->a = a;
}

void Serie::setB(double b)
{
    this->b = b;
}

void Serie::setC(double c)
{
    this->c = c;
}

void Serie::setD(double d)
{
    this->d = d;
}

void Serie::setRuido(bool ruido)
{
    this->ruido = ruido;
}

void Serie::setIntensidadRuido(double intensidadRuido)
{
    this->intensidadRuido = intensidadRuido;
}

double Serie::getX0()
{
    return this->x0;
}

double Serie::getY0()
{
    return this->y0;
}

double Serie::getA()
{
    return this->a;
}

double Serie::getB()
{
    return this->b;
}

double Serie::getC()
{
    return this->c;
}

double Serie::getD()
{
    return this->d;
}

double Serie::getK()
{
    return this->K;
}

double Serie::getRetardo()
{
    return this->retardo;
}

System Serie::getTipo()
{
    return this->miTipo;
}

bool Serie::getRuido()
{
    return this->ruido;
}

double Serie::getIntesidadRuido()
{
    return this->intensidadRuido;
}

