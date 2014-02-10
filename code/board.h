/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: board.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Es una interfaz gráfica que permite configurar todos los parámetros para la ejecución del algoritmo.
*/

#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"
#include <QWidget>

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT
    
public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    
private slots:
    void on_systemComboBox_currentIndexChanged(int index);
    void on_runButton_clicked();

private:
    Ui::Board *ui;
    System typeSystem;

    void setSystem(System system);

signals:
    void runSignal(int,int,int,int,int,int,int,int,double,double,double,double,double,double,double,bool,double);

public slots:
    void writeInfoSlot(QString info);
};

#endif // BOARD_H
