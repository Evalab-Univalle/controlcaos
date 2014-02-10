/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: canvas.cpp
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 */

#include "canvas.h"
#include "numericmethods.h"
#include "function.h"
#include <cmath>
#include <GL/glu.h>

Canvas::Canvas(int sistema, int cantidadPuntos)
{
    this->atractor = Attractor(sistema);
    this->cantidadPuntos = cantidadPuntos;
}

Canvas::~Canvas()
{

}

void Canvas::initializeGL()
{
    glClearStencil(0x0);
    glEnable(GL_STENCIL_TEST);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);  // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);  // The Type Of Depth Test To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective
    glEnable(GL_NORMALIZE);

    this->suavizar();
}

void Canvas::resizeGL(int width, int height)
{
    if (height==0) // Prevent A Divide By Zero By
    {
        height=1;  // Making Height Equal One
    }

    glViewport(0, 0, width, height); // Reset The Current Viewport

    //The projection matrix is responsible for adding perspective to our scene
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Reset The Projection Matrix
    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//borrar el contenido actual
    glLoadIdentity();

    switch(this->atractor)
    {
        case Logistica:
        {
            glTranslatef(-3.0,-0.5,-2.0);
            glColor4f(1.0f,1.0f,1.0f,0.02f);

            glBegin(GL_POINTS);
            for(double k=2.4;k<4.0;k+=0.001)
            {
                QVector<double> points = this->ecuacionLogistica(0.1,k,this->cantidadPuntos,500);
                for(int i=0;i<points.size();i++)
                {
                    glVertex2f(k,points.at(i));
                }
            }
            glEnd();
            break;
        }
        case Henon:
        {
            glTranslatef(0.0,0.0,-5.0);
            glColor4f(1.0f,1.0f,1.0f,0.02f);

            glBegin(GL_POINTS);
            for(double a=0.0;a<10.0;a+=0.001)
            {
                QVector<double> points = this->sistemaHenon(-0.1,0.1,a,0.3,this->cantidadPuntos,500);
                for(int i=0;i<points.size();i++)
                {
                    glVertex2f(a,points.at(i));
                }
            }
            glEnd();
            break;
        }
        case Tinkerbell:
        {
            glTranslatef(0.0,0.5,-2.0);
            glColor4f(1.0f,1.0f,1.0f,0.02f);

            glBegin(GL_POINTS);
            for(double a=-0.7;a<1.0;a+=0.001)
            {
                QVector<double> points = this->sistemaTinkerbell(0.1,0.1,a,-0.6,2.2,0.5,this->cantidadPuntos,500);
                for(int i=0;i<points.size();i++)
                {
                    glVertex2f(a,points.at(i));
                }
            }
            glEnd();
            break;
        }
        case Ikeda:
        {
            glTranslatef(0.0,0.0,-5.5);
            glColor4f(1.0f,1.0f,1.0f,0.02f);

            glBegin(GL_POINTS);
            for(double a=-1.5;a<1.5;a+=0.001)
            {
                QVector<double> points = this->sistemaIkeda(0.1,0.1,a,0.9,0.4,6.0,this->cantidadPuntos,500);
                for(int i=0;i<points.size();i++)
                {
                    glVertex2f(a,points.at(i));
                }
            }
            glEnd();
            break;
        }
        case Lorenz:
        {
            glTranslatef(-100,-20,-180);
            glColor4f(1.0f,1.0f,1.0f,0.02f);

            glBegin(GL_POINTS);
            for(double r=0;r<200;r+=0.01)
            {
                QVector<double> points = this->sistemaLorenz(0.3,0.3,0.3,10,r,8/3,this->cantidadPuntos,1000);
                for(int i=0;i<points.size();i++)
                {
                    glVertex2f(r,points.at(i));
                }
            }
            glEnd();
            break;
        }
    }

    //Sistema de Lorenz
    /*Para grafica en z
        glTranslatef(-100,-200,-480)
        25<r<325 step:0.01

      Para graficar x
         glTranslatef(-100,-20,-180);
         0<r<200 step: 0.01
    */
    glFlush();
}

void Canvas::suavizar()
{
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable point smoothing
    glEnable(GL_POINT_SMOOTH);
   glPointSize(0.5f);
}

/*
Esta función quita el suavizado al dibujar, esto se hace porque no todos los atractores necesitan
suavizado para que se vea bien su dibujo
*/
void Canvas::noSuavizar()
{
    // enable blending
    glDisable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable point smoothing
    glDisable(GL_POINT_SMOOTH);
    //glPointSize(1.0f);
}

QVector<double> Canvas::ecuacionLogistica(double x0, double k, int N, int s)
{
    double xnew;
    QVector<double> points;
    for(int i=0;i<s;i++)
    {
        xnew = x0*k*(1-x0);
        x0 = xnew;
    }

    for(int i=0;i<N;i++)
    {
        xnew = x0*k*(1-x0);
        x0 = xnew;
        points.append(xnew);
    }

    return points;
}

QVector<double> Canvas::sistemaHenon(double x0, double y0, double a, double b, int N, int s)
{
    double xnew,ynew;
    QVector<double> points;

    for(int i=0;i<s;i++)
    {
        xnew = 1-a*x0*x0+y0;
        ynew = b*x0;
        x0 = xnew;
        y0 = ynew;
    }

    for(int i=0;i<N;i++)
    {
        xnew = 1-a*x0*x0+y0;
        ynew = b*x0;
        x0 = xnew;
        y0 = ynew;

        points.append(xnew);
    }

    return points;
}

QVector<double> Canvas::sistemaTinkerbell(double x0, double y0, double a, double b, double c, double d, int N, int s)
{
    double xnew, ynew;
    QVector<double> points;

    for(int i=0;i<s;i++)
    {
        xnew = x0*x0-y0*y0+a*x0+b*y0;
        ynew = 2*x0*y0+c*x0+d*y0;
        x0 = xnew;
        y0 = ynew;
    }
    for(int i=0;i<N;i++)
    {
        xnew = x0*x0-y0*y0+a*x0+b*y0;
        ynew = 2*x0*y0+c*x0+d*y0;
        x0 = xnew;
        y0 = ynew;

        points.append(xnew);
    }

    return points;
}

QVector<double> Canvas::sistemaIkeda(double x0, double y0, double a, double b, double c, double d, int N, int s)
{
    double xnew, ynew, u;
    QVector<double> points;

    for(int i=0;i<s;i++)
    {
        u = (c-d)/(1+x0*x0+y0*y0);
        xnew = a+b*(x0*cos(u)-y0*sin(u));
        ynew = b*(x0*sin(u)+y0*cos(u));
        x0 = xnew;
        y0 = ynew;
    }
    for(int i=0;i<N;i++)
    {
        u = (c-d)/(1+x0*x0+y0*y0);
        xnew = a+b*(x0*cos(u)-y0*sin(u));
        ynew = b*(x0*sin(u)+y0*cos(u));
        x0 = xnew;
        y0 = ynew;

        points.append(xnew);
    }

    return points;
}

QVector<double> Canvas::sistemaLorenz(double x0, double y0, double z0, double s, double r, double b, int N, int st)
{
    NumericMethods num;
    double xnew,ynew,znew, dt=0.001, t0=0.0;
    QVector<double> temp, points;

    while (t0<st*dt)
    {
        temp = num.rungeKutta4(t0,x0,y0,z0,s,r,b,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
        xnew=temp.at(0);
        ynew=temp.at(1);
        znew=temp.at(2);
        x0=xnew;
        y0=ynew;
        z0=znew;
        t0+=dt;
    }
    t0=0.0;
    while (t0<N*dt)
    {
        temp = num.rungeKutta4(t0,x0,y0,z0,s,r,b,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
        xnew=temp.at(0);
        ynew=temp.at(1);
        znew=temp.at(2);
        x0=xnew;
        y0=ynew;
        z0=znew;
        t0+=dt;

        points.append(xnew);
    }

    return points;
}
