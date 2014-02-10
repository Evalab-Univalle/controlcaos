/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: lienzo.cpp
 *
 */

#include "lienzo.h"
#include "numericmethods.h"
#include "function.h"
#include <cmath>
#include <QKeyEvent>
#include <QTimer>
#include <GL/glu.h>

Lienzo::Lienzo(int type, int system)
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    this->type = type;
    this->system = Attractor(system);
    this->lastExecute = -1;
    this->startPoints = 0;
}

Lienzo::~Lienzo()
{
    delete m_timer;
    m_timer = 0;
}

/*
función virtual de QGLWidget
Es llamada al instanciar la clase
*/
void Lienzo::initializeGL()
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
}

/*
función virtual de QGLWidget
Es llamada cuando la ventana se redimensiona, lo que hace es acomodar el punto de perspectiva
*/
void Lienzo::resizeGL(int width, int height)
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

/*
función virtual de QGLWidget
Es llamda cada vez que se dibuja
*/
void Lienzo::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//borrar el contenido actual
    glLoadIdentity();

    switch(this->type)
    {
        case 0 : //attractor
        {
            glPointSize(1.0f);
            switch(this->system)
            {
                case Lorenz :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glColor3f(0.0f,0.0f,0.50f);
                        glVertex3f(px.at(i),py.at(i),pz.at(i));

                        glColor3f(0.39f,0.58f,0.92f);
                        glVertex3f(px2.at(i),py2.at(i),pz2.at(i));
                    }
                    glEnd();
                    break;
                }
                case Henon :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);
                    glColor3f(1.0f,0.0f,0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glVertex2f(px.at(i),py.at(i));
                    }
                    glEnd();
                    break;
                }
                case Tinkerbell :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glColor4f(1.0f,0.64f,0.0f,0.03f);
                        glVertex2f(px.at(i),py.at(i));

                        glColor4f(0.69f,0.13f,0.13f,0.03f);
                        glVertex2f(px2.at(i),py2.at(i));
                    }
                    glEnd();
                    break;
                }
                case Ikeda:
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);
                    glColor4f(0.0001f,0.54f,0.34f,0.3f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glVertex3f(px.at(i),py.at(i),pz.at(i));
                    }
                    glEnd();
                    break;
                }
                case TheKing:
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);
                    glColor4f(1.0f,1.0f,1.0f,0.03f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glVertex2f(px.at(i),py.at(i));
                    }
                    glEnd();
                    break;
                }
                case GumowiskMira :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);
                    glColor4f(0.11f,0.56f,1.0f,0.3f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=0;i<px.size();i++)
                    {
                        glVertex2f(px.at(i),py.at(i));
                    }
                    glEnd();
                }
            }
            break;
        }
        case 1 : //sensibility
        {
            glPointSize(2.0f);
            switch(this->system)
            {
                case Lorenz :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(0.0f,0.5f,0.0f);//verde claro
                        glVertex3f(px.at(i),py.at(i),pz.at(i));

                        glColor3f(0.39f,0.58f,0.92f);//azul claro
                        glVertex3f(px2.at(i),py2.at(i),pz2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                    break;
                }
                case Henon :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(1.0f,0.0f,0.0f);//rojo
                        glVertex2f(px.at(i),py.at(i));

                        glColor3f(0.0f,1.0f,0.0f);//verde
                        glVertex2f(px2.at(i),py2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                    break;
                }
                case Tinkerbell :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(1.0f,1.0f,0.0f);
                        glVertex2f(px.at(i),py.at(i));

                        glColor3f(0.69f,0.13f,0.13f);
                        glVertex2f(px2.at(i),py2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                    break;
                }
                case Ikeda:
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    glRotatef(this->angley,1.0f,0.0f,0.0f);
                    glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(0.0001f,0.54f,0.34f);
                        glVertex3f(px.at(i),py.at(i),pz.at(i));

                        glColor3f(1.0f,0.0f,0.0f);
                        glVertex3f(px2.at(i),py2.at(i),pz2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                    break;
                }
                case TheKing:
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);

                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(1.0f,1.0f,1.0f);
                        glVertex2f(px.at(i),py.at(i));

                        glColor3f(0.69f,0.13f,0.13f);
                        glVertex2f(px2.at(i),py2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                    break;
                }
                case GumowiskMira :
                {
                    glTranslatef(this->posx,this->posy,this->zdepth);
                    //glRotatef(this->angley,1.0f,0.0f,0.0f);
                    //glRotatef(this->anglex, 0.0f, 1.0f, 0.0f);


                    this->points();
                    glBegin(GL_POINTS);
                    for(int i=startPoints;i<startPoints+100;i++)
                    {
                        glColor3f(0.11f,0.56f,1.0f);
                        glVertex2f(px.at(i),py.at(i));

                        glColor3f(0.69f,0.13f,0.13f);
                        glVertex2f(px2.at(i),py2.at(i));
                    }
                    glEnd();
                    startPoints += 50;
                    if(startPoints == px.size())
                    {
                        this->stopTime();
                        startPoints = 0;
                    }
                }
            }
        }
    }
    glFlush();//asegurar que se ejecuten los comandos
}

/*
Slot, es llamado por un timer, usado para simular el movimiento
*/
void Lienzo::timeOutSlot()
{
    updateGL();
}

/*
Esta función suaviza los puntos dibujados, es usada solo cuando se van a graficar algunos atractores
*/
void suavizar()
{
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable point smoothing
    glEnable(GL_POINT_SMOOTH);
   //glPointSize(1.0f);
}

/*
Esta función quita el suavizado al dibujar, esto se hace porque no todos los atractores necesitan
suavizado para que se vea bien su dibujo
*/
void noSuavizar()
{
    // enable blending
    glDisable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable point smoothing
    glDisable(GL_POINT_SMOOTH);
    //glPointSize(1.0f);
}

/*
Esta función actualiza es sistema que se está graficando, dado que cada sisitema tiene ciertas
particularidades como los angulos o las posiciones en la ventana donde se va a dibujar, estas
se hacen acá.Dado que el timer hace que se dibuje a ciertos intervalos de tiempo, si el sistema
cambia, lo detengo, o sino se verian cosas extrañas
*/
void Lienzo::setSystem(int system)
{
    this->m_timer->stop();
    this->system = Attractor(system);
    this->anglex = 0.0f;
    this->angley = 0.0f;
    this->lastExecute = -1;
    this->startPoints = 0;

    switch(this->system)
    {
        case Lorenz:
            this->zdepth =-100.0f;
            this->posx=-19.0f;
            this->posy=0.0f;
            noSuavizar();
            break;
        case Henon:
            this->zdepth = -5.0f;
            this->posx=0.0f;
            this->posy=0.0f;
            noSuavizar();
            break;
        case Tinkerbell :
            this->zdepth = -3.0f;
            this->posx=0.4f;
            this->posy=0.55f;
            suavizar();
            break;
        case Ikeda:
            this->zdepth = -5.0f;
            this->posx=0.0f;
            this->posy=1.0f;
            suavizar();
            break;
        case TheKing :
            this->zdepth = -6.0f;
            this->posx=0.0f;
            this->posy=0.0f;
            suavizar();
            break;
        case GumowiskMira :
            this->zdepth = -120.0f;
            this->posx=0.0f;
            this->posy=0.0f;
            suavizar();
    }
}

int Lienzo::getSystem()
{
    return this->system;
}

void Lienzo::setType(int type)
{
    this->m_timer->stop();
    this->type = type;
}

int Lienzo::getType()
{
    return this->type;
}

/*
Esta función calcula los puntos que se quieren dibujar,segun el tipo de sistema.
Los puntos son los mismos tanto para el atractor como para la sensibilidad
*/
void Lienzo::points()
{
    switch(this->system)
    {
    case Lorenz :
    {
        /*lastExecute se usa para no calcular los puntos nuevamente en caso de no ser necesario, como
        por ejemplo cuando la imagen se rota o se traslada. Solo se vulven a calcular, por ejemplo,
        si los valores iniciales cambian*/
        if(this->lastExecute==Lorenz) break;
        this->clearPoints();

        NumericMethods num;
        double x,y,z, dt=0.001, t0=0.0, x02=x0+delay, y02=y0, z02=z0;
        QVector<double> r;

        /*ejecutar dos veces las mismas cosas se hacen varias veces en esta función, esto es para que
        la orbita del atractor se estabilice*/
        while (t0<10.0)
        {
            r = num.rungeKutta4(t0,x0,y0,z0,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
            x=r.at(0);
            y=r.at(1);
            z=r.at(2);
            x0=x;
            y0=y;
            z0=z;
            r = num.rungeKutta4(t0,x02,y02,z02,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
            x=r.at(0);
            y=r.at(1);
            z=r.at(2);
            x02=x;
            y02=y;
            z02=z;
            t0+=dt;
        }
        t0=0.0;
        while (t0<100)
        {
            r = num.rungeKutta4(t0,x0,y0,z0,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
            x=r.at(0);
            y=r.at(1);
            z=r.at(2);
            x0=x;
            y0=y;
            z0=z;

            r = num.rungeKutta4(t0,x02,y02,z02,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
            x=r.at(0);
            y=r.at(1);
            z=r.at(2);
            x02=x;
            y02=y;
            z02=z;
            t0+=dt;

            px.append(x0);
            py.append(y0);
            pz.append(z0);
            px2.append(x02);
            py2.append(y02);
            pz2.append(z02);

        }
        this->lastExecute = Lorenz;
        break;
    }
    case Henon :
    {
        if(this->lastExecute==Henon) break;
        this->clearPoints();

        double xnew,ynew,x02=x0+delay,y02=y0;
        int iterations = 1000000;

        for(int i=0;i<iterations;i++)
        {
            xnew = 1-a*x0*x0+y0;
            ynew = b*x0;
            x0 = xnew;
            y0 = ynew;

            xnew = 1-a*x02*x02+y02;
            ynew = b*x02;
            x02 = xnew;
            y02 = ynew;

            px.append(x0);
            py.append(y0);
            px2.append(x02);
            py2.append(y02);
        }
        this->lastExecute=Henon;
        break;
    }

    case Tinkerbell:
    {
        if(this->lastExecute==Tinkerbell) break;
        this->clearPoints();

        double xnew, ynew, x02=x0+delay, y02=y0;
        int	initialIterations = 100, iterations = 1000000;

        for(int i=0;i<initialIterations;i++)
        {
            xnew = x0*x0-y0*y0+a*x0+b*y0;
            ynew = 2*x0*y0+c*x0+d*y0;
            x0 = xnew;
            y0 = ynew;
            xnew = x02*x02-y02*y02+a*x02+b*y02;
            ynew = 2*x02*y02+c*x02+d*y02;
            x02 = xnew;
            y02 = ynew;
        }

        for(int i=0;i<iterations;i++)
        {
            xnew = x0*x0-y0*y0+a*x0+b*y0;
            ynew = 2*x0*y0+c*x0+d*y0;
            x0 = xnew;
            y0 = ynew;

            xnew = x02*x02-y02*y02+a*x02+b*y02;
            ynew = 2*x02*y02+c*x02+d*y02;
            x02 = xnew;
            y02 = ynew;

            px.append(x0);
            py.append(y0);
            px2.append(x02);
            py2.append(y02);
        }
        this->lastExecute=Tinkerbell;
        break;
    }
    case Ikeda:
    {
        if(this->lastExecute==Ikeda) break;
        this->clearPoints();

        double u,xnew,ynew,x02=x0+delay,y02=y0;
        int	initialIterations = 100, iterations = 1000000;

        for(int i=0;i<initialIterations;i++)
        {
            u=c-d/(1+x0*x0+y0*y0);
            xnew = a+b*(x0*cos(u)-y0*sin(u));
            ynew = b*(x0*sin(u)+y0*cos(u));
            x0 = xnew;
            y0 = ynew;

            u=c-d/(1+x02*x02+y02*y02);
            xnew = a+b*(x02*cos(u)-y02*sin(u));
            ynew = b*(x02*sin(u)+y02*cos(u));
            x02 = xnew;
            y02 = ynew;

        }

        for(int i=0;i<iterations;i++)
        {
            u=c-d/(1+x0*x0+y0*y0);
            xnew = a+b*(x0*cos(u)-y0*sin(u));
            ynew = b*(x0*sin(u)+y0*cos(u));
            x0 = xnew;
            y0 = ynew;
            pz.append(u);

            u=c-d/(1+x02*x02+y02*y02);
            xnew = a+b*(x02*cos(u)-y02*sin(u));
            ynew = b*(x02*sin(u)+y02*cos(u));
            x02 = xnew;
            y02 = ynew;
            pz2.append(u);

            px.append(x0);
            py.append(y0);
            px2.append(x02);
            py2.append(y02);
        }

        this->lastExecute=Ikeda;
        break;
    }
    case GumowiskMira:
    {
        if(this->lastExecute==GumowiskMira) break;
        this->clearPoints();

        double xnew,ynew,x02=x0+delay,y02=y0;
        int	iterations = 1000000;

        for(int i=0;i<iterations;i++)
        {
            xnew = b*y0 + f_GumowiskMira(x0,a);
            ynew = -x0 + f_GumowiskMira(xnew,a);
            x0 = xnew;
            y0 = ynew;

            xnew = b*y02 + f_GumowiskMira(x02,a);
            ynew = -x02 + f_GumowiskMira(xnew,a);
            x02 = xnew;
            y02 = ynew;

            px.append(x0);
            py.append(y0);
            px2.append(x02);
            py2.append(y02);
        }

        this->lastExecute=GumowiskMira;
        break;
    }
    case TheKing:
    {
        if(this->lastExecute==TheKing) break;
        this->clearPoints();

        double xnew,ynew,x02=x0+delay,y02=y0;
        int	initialIterations = 100,
                iterations = 1000000;

        // se calculan algunos valores para que el atractor se estabilice
        for (int i = 0; i < initialIterations; i++)
        {
            // compute a new point using the strange attractor equations
            xnew = sin(y0*b) + c*sin(x0*b);
            ynew = sin(x0*a) + d*sin(y0*a);
            x0 = xnew;
            y0 = ynew;

            xnew = sin(y02*b) + c*sin(x02*b);
            ynew = sin(x02*a) + d*sin(y02*a);
            x02 = xnew;
            y02 = ynew;
        }

        // ahora si, calculamos los puntos y los guardamos
        for (int i = 0; i < iterations; i++) {
            xnew = sin(y0*b) + c*sin(x0*b);
            ynew = sin(x0*a) + d*sin(y0*a);
            x0 = xnew;
            y0 = ynew;

            xnew = sin(y02*b) + c*sin(x02*b);
            ynew = sin(x02*a) + d*sin(y02*a);
            x02 = xnew;
            y02 = ynew;

            px.append(x0);
            py.append(y0);
            px2.append(x02);
            py2.append(y02);
        }
        this->lastExecute=TheKing;
    }

    }
}

/*
Slot, cambia los valores iniciales del sistema para calcular los puntos
*/
void Lienzo::setInit(QVector<double> values)
{
    this->x0=values.at(0);
    this->y0=values.at(1);
    this->z0=values.at(2);
    this->a=values.at(3);
    this->b=values.at(4);
    this->c=values.at(5);
    this->d=values.at(6);
    this->delay=values.at(7);
}

void Lienzo::setAngleX(double anglex)
{
    this->anglex = anglex;
}

double Lienzo::getAngleX()
{
    return this->anglex;
}

void Lienzo::setAngley(double angley)
{
    this->angley = angley;
}

double Lienzo::getAngleY()
{
    return this->angley;
}

void Lienzo::plusAngleX(double value)
{
    this->anglex += value;
}

void Lienzo::plusAngleY(double value)
{
    this->angley += value;
}

//zdepth es la profundidad a la que se realiza el dibujo
void Lienzo::setZ(double z)
{
    this->zdepth = z;
}

double Lienzo::getZ()
{
    return this->zdepth;
}

void Lienzo::plusZ(double value)
{
    this->zdepth += value;
}

void Lienzo::startTime()
{
    m_timer->start(100);
}

void Lienzo::stopTime()
{
    m_timer->stop();
}

/*
Esta función limpia los vectores de puntos
*/
void Lienzo::clearPoints()
{
    px.clear();
    py.clear();
    pz.clear();
    px2.clear();
    py2.clear();
    pz2.clear();
}

double Lienzo::getPosX()
{
    return this->posx;
}

double Lienzo::getPosY()
{
    return this->posy;
}

void Lienzo::setPosX(double posx)
{
    this->posx = posx;
}

void Lienzo::setPosY(double posy)
{
    this->posy = posy;
}

void Lienzo::plusPosX(double value)
{
    this->posx += value;
}

void Lienzo::plusPosY(double value)
{
    this->posy += value;
}
