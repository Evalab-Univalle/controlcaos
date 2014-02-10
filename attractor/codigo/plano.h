#ifndef PLANO_H
#define PLANO_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//#include <QtOpenGL>
#include <QGLWidget>
//#include <GL/glu.h>
#include <QTimer>
#include <QKeyEvent>
#include <math.h>

class Plano : public QGLWidget
{
    Q_OBJECT

public:
    Plano();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void timeOut();

    void theKingDreamAttractor();
    void theHenonAttractor();
    void theLorenzAttractor(double x0, double y0, double z0, double a, double b, double c);

protected slots:
    void timeOutSlot();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QTimer *m_timer;
    GLfloat anglex;
    GLfloat angley;
    GLfloat anglez;
    GLfloat z;
};

#endif // PLANO_H
