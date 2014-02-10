/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: choice.h
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 * Descripción: Interfaz gráfica que permite seleccionar qué sistema graficar.
 */

#ifndef CHOICE_H
#define CHOICE_H

#include <QWidget>

namespace Ui {
class Choice;
}

class Choice : public QWidget
{
    Q_OBJECT
    
public:
    explicit Choice(QWidget *parent = 0);
    ~Choice();
    
private slots:
    void on_sistemaComboBox_currentIndexChanged(int index);

    void on_graficarButton_clicked();

private:
    Ui::Choice *ui;
};

#endif // CHOICE_H
