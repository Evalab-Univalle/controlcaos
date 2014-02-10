/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: lienzo.h
 *
 * Descripción: es la clase encargada de dibujar las gráficas. Usa opengl implementado por QT.
 */

#ifndef LIENZO_H
#define LIENZO_H

#include <QGLWidget>

QT_BEGIN_NAMESPACE
class QKeyEvent;
QT_END_NAMESPACE

class Lienzo : public QGLWidget
{
    Q_OBJECT

public:
    Lienzo(int type=0, int system=-1);
    ~Lienzo();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    int getSystem();
    int getType();
    double getAngleX();
    double getAngleY();
    double getZ();
    double getPosX();
    double getPosY();

    void setAngleX(double anglex);
    void setAngley(double angley);
    void setPosX(double posx);
    void setPosY(double posy);
    void setZ(double z);

    void plusAngleX(double anglex);
    void plusAngleY(double angley);
    void plusZ(double value);
    void plusPosX(double value);
    void plusPosY(double value);


public slots:
    void startTime();
    void stopTime();
    void setSystem(int system);
    void setType(int type);
    void setInit(QVector<double> values);

private slots:
    void timeOutSlot();

private:
    QTimer *m_timer;
    GLfloat anglex;
    GLfloat angley;
    GLfloat posx;
    GLfloat posy;
    GLfloat zdepth;
    QVector<double> px, py, pz, px2, py2, pz2;
    int type;
    double x0, y0, z0, a, b, c, d, delay;
    int lastExecute;    
    int startPoints;
    enum Attractor {Lorenz, Henon, Tinkerbell, Ikeda, GumowiskMira, TheKing};
    Attractor system;

    void clearPoints();
    void points();
};

#endif // LIENZO_H
