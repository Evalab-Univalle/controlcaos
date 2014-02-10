/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: choice.cpp
 * Email: cristian.rios@correounivalle.edu.co
 * Licencia: GPL v.1
 *
 */

#include "choice.h"
#include "ui_choice.h"
#include "canvas.h"
#include <QTextCodec>

Choice::Choice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choice)
{
    ui->setupUi(this);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QStringList opciones;
    opciones << tr("Ecuación Logística") << tr("Sistema de Henon") << tr("Sistema de Tinkerbell") << tr("Sistema de Ikeda") << tr("Sistema de Lorenz");
    ui->sistemaComboBox->addItems(opciones);
}

Choice::~Choice()
{
    delete ui;
}

void Choice::on_sistemaComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0: //ecuacion logistica
        {
            ui->cantidadSpinBox->setValue(4000);
            break;
        }
        case 1: //sistema de henon
        {
            ui->cantidadSpinBox->setValue(3000);
            break;
        }
        case 2: //sistema de tinkerbell
        {
            ui->cantidadSpinBox->setValue(2000);
            break;
        }
        case 3: //sistema de ikeda
        {
            ui->cantidadSpinBox->setValue(2000);
            break;
        }
        case 4: //sistema de lorenz
        {
            ui->cantidadSpinBox->setValue(100);
            break;
        }
    }
}

void Choice::on_graficarButton_clicked()
{
    QHBoxLayout *layout = new QHBoxLayout;
    Canvas *canvas = new Canvas(ui->sistemaComboBox->currentIndex(),ui->cantidadSpinBox->value());
    layout->addWidget(canvas);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    widget->resize(700,500);
    widget->show();
}
