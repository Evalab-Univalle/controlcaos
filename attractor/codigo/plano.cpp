#include "plano.h"
#include "function.h"
#include "numericmethods.h"
#include <QDebug>
#include <iostream>
#include <QVector>
using namespace std;

Plano::Plano()
{
    //m_timer = new QTimer(this);
    //connect(m_timer,SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    //m_timer->start(100); //100 milisegundo
    anglex=0.0f;
    angley=0.0f;
    anglez=0.0f;
    z=-100.0f;
}

void Plano::initializeGL()
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

    // set the foreground (pen) color
    //glColor4f(1.0f, 1.0f, 1.0f, 0.02f);

    // enable blending
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable point smoothing
    //glEnable(GL_POINT_SMOOTH);
    //glPointSize(1.0f);
}

void Plano::resizeGL(int width, int height)
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

void Plano::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//borrar el contenido actual

    glLoadIdentity();
    glTranslatef(0.0f,0.0f,z);

    // draw some points
    glBegin(GL_POINTS);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            glVertex2f(0.0f, 1.0f);
            glVertex2f(-1.0f, 0.0f);
            glVertex2f(0.0f, -1.0f);
    glEnd();

    glRotatef(angley,1.0f,0.0f,0.0f);
    glRotatef(anglex, 0.0f, 1.0f, 0.0f);

    //this->theKingDreamAttractor();
    //this->theHenonAttractor();
    glColor3f(1.0f,0.0f,0.0f);
    this->theLorenzAttractor(1.0, 1.0, 1.0, -8/3, -10, 28);
    glColor3f(0.0f,1.0f,0.0f);
    this->theLorenzAttractor(1.1, 1.0, 1.0, -8/3, -10, 28);

    glFlush();//asegurar que se ejecuten los comandos
}

void Plano::timeOut()
{
    //angle+=0.5f;
    //updateGL();
}

void Plano::timeOutSlot()
{
    this->timeOut();
}

void Plano::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
            case Qt::Key_Escape:
                    //QCoreApplication::exit();
                    break;

            case Qt::Key_Left:
                anglex -= 0.7;
                break;
            case Qt::Key_Right:
                anglex += 0.7;
                break;
            case Qt::Key_Up:
                 angley += 0.7;
                break;
            case Qt::Key_Down:
                 angley -= 0.7;
                 break;
            case Qt::Key_PageUp:
                z += 0.5;
                break;
            case Qt::Key_PageDown:
                z -= 0.5;
                break;
    }
    updateGL();
}

void Plano::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
            case Qt::LeftButton:
                    //updateGL();
                    break;

            case Qt::MidButton:
            case Qt::RightButton:
                    //updateGL();
                    break;
            default:
                    break;
    }
}

void Plano::theKingDreamAttractor()
{
    float   x = 0.1, y = 0.1,		// starting point
            a = -0.966918,			// coefficients for "The King's Dream"
            b = 2.879879,
            c = 0.765145,
            d = 0.744728;
    int	initialIterations = 100,	// initial number of iterations
                                            // to allow the attractor to settle
            iterations = 1000000;		// number of times to iterate through
                                            // the functions and draw a point

    // compute some initial iterations to settle into the orbit of the attractor
    for (int i = 0; i < initialIterations; i++) {

        // compute a new point using the strange attractor equations
        float xnew = sin(y*b) + c*sin(x*b);
        float ynew = sin(x*a) + d*sin(y*a);

        // save the new point
        x = xnew;
        y = ynew;
    }

    // draw some points
    glBegin(GL_POINTS);

        // go through the equations many times, drawing a point for each iteration
        for (int i = 0; i < iterations; i++) {
            // compute a new point using the strange attractor equations
            float xnew = sin(y*b) + c*sin(x*b);
            float ynew = sin(x*a) + d*sin(y*a);

            // save the new point
            x = xnew;
            y = ynew;

            // draw the new point
            glVertex2f(x, y);
        }
    glEnd();
}

void Plano::theHenonAttractor()
{
    float x = -0.1, y = 0.1, a = 1.3, b = 0.31;
    int iterations = 10000;

    glBegin(GL_POINTS);
        for(int i=0;i<iterations;i++)
        {
            float xnew = 1-a*x*x+y;
            float ynew = b*x;

            x = xnew;
            y = ynew;

            glVertex2f(x,y);
        }
    glEnd();

}

void Plano::theLorenzAttractor(double x0, double y0, double z0, double a, double b, double c)
{
    NumericMethods num;
    //double x0=1.0, y0=1.0, z0=1.0, t0=0.0, dt=0.001, x, y, z, a=-8/3, b=-10, c=28;
    double x,y,z, dt=0.001, t0=0.0;
    QVector<double> r;

    //r = num.rungeKutta4(t0,x0,y0,z0,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
    glBegin(GL_POINTS);
    while (t0<100) {
        r = num.rungeKutta4(t0,x0,y0,z0,a,b,c,dt,dx_Lorenz,dy_Lorenz,dz_Lorenz);
        x = r.at(0);
        y = r.at(1);
        z = r.at(2);

        x0=x;
        y0=y;
        z0=z;
        t0+=dt;

        //cout << x << " " << y << " " << z << endl;

        glVertex3f(x,y,z);
    }
    glEnd();

}
