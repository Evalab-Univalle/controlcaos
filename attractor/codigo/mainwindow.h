/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: mainwindow.h
 *
 * Descripción: crea la ventana principal, reuno todas las demás clases.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class Lienzo;
class Panel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void keyPressEvent(QKeyEvent *event);

private:
    Lienzo *lienzo;
    Panel *panel;
};

#endif // MAINWINDOW_H
