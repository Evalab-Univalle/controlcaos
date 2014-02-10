/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: panel.h
 *
 * Descripción: interfaz gráfica que permite definir los parámetros para realizar las gráficas.
 */

#ifndef PANEL_H
#define PANEL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QComboBox;
class QLabel;
class QPushButton;
class QDoubleSpinBox;
QT_END_NAMESPACE

class Panel : public QWidget
{
    Q_OBJECT

public:
    explicit Panel(QWidget *parent = 0);
    ~Panel();

private:
   QComboBox *optionTypeComboBox;
   QComboBox *optionSystemComboBox;
   QLabel *optionTypeLabel;
   QLabel *optionSystemLabel;
   QLabel *infoLabel;
   QPushButton *drawButton;
   QDoubleSpinBox *aSpinBox;
   QDoubleSpinBox *bSpinBox;
   QDoubleSpinBox *cSpinBox;
   QDoubleSpinBox *dSpinBox;
   QDoubleSpinBox *deltaSpinBox;

   double x,y,z,a,b,c,d,delta;
   enum Attractor {Lorenz, Henon, Tinkerbell, Ikeda, GumowiskMira, TheKing};

   void initValues();
   void getValues();

 private slots:
   void drawSlot();
   void systemChangeSlot(const int &value);
   void typeChangeSlot(const int &value);

signals:
   void drawSignal();
   int typeSignal(int);
   int systemSignal(int);
   QVector<double> initValueChangeSignal(QVector<double>);
   void startTimerSignal();
};

#endif // PANEL_H
