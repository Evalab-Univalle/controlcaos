/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: board.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "board.h"
#include "ui_board.h"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);

    //contenidos de los combobox
    QStringList names;
    names << tr("Ecuación Logística") << tr("Sistema de Henon") << tr("Sistema de Tinkerbell") << tr("Sistema de Ikeda") << tr("Sistema de Lorenz");
    ui->systemComboBox->addItems(names);
    QStringList orbits;
    orbits << "1" << "2" << "4";
    ui->amountOrbitComboBox->addItems(orbits);

    //Configuraciones de apariencia de la consola
    QPalette p = ui->consolePlainTextEdit->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->consolePlainTextEdit->setPalette(p);

    //se configura un sistema por defecto
    this->setSystem(System(0));
}

Board::~Board()
{
    delete ui;
}

void Board::on_systemComboBox_currentIndexChanged(int index)
{
    this->setSystem(System(index));
}

/*
 * Método setSystem: para cada sistema cra una configuración por defecto.
 */
void Board::setSystem(System system)
{
    this->typeSystem = system;

    switch(system)
    {
        case LogisticEcuation :
        {
            ui->ySpinBox->setEnabled(false);
            ui->zSpinBox->setEnabled(false);
            ui->bSpinBox->setEnabled(false);
            ui->cSpinBox->setEnabled(false);
            ui->dSpinBox->setEnabled(false);

            ui->xSpinBox->setValue(0.1);
            ui->aSpinBox->setValue(3.8);

            break;
        }
        case HenonSystem :
        {
            ui->ySpinBox->setEnabled(true);
            ui->zSpinBox->setEnabled(false);
            ui->bSpinBox->setEnabled(true);
            ui->cSpinBox->setEnabled(false);
            ui->dSpinBox->setEnabled(false);

            ui->xSpinBox->setValue(-0.1);
            ui->ySpinBox->setValue(0.1);
            ui->aSpinBox->setValue(1.2);
            ui->bSpinBox->setValue(0.3);

            break;
        }
        case TinkerbellSystem:
        {
            ui->ySpinBox->setEnabled(true);
            ui->zSpinBox->setEnabled(false);
            ui->bSpinBox->setEnabled(true);
            ui->cSpinBox->setEnabled(true);
            ui->dSpinBox->setEnabled(true);

            ui->xSpinBox->setValue(0.1);
            ui->ySpinBox->setValue(0.1);
            ui->aSpinBox->setValue(0.5);
            ui->bSpinBox->setValue(-0.6);
            ui->cSpinBox->setValue(2.2);
            ui->dSpinBox->setValue(0.5);

            break;
        }
        case IkedaSystem:
        {
            ui->ySpinBox->setEnabled(true);
            ui->zSpinBox->setEnabled(false);
            ui->bSpinBox->setEnabled(true);
            ui->cSpinBox->setEnabled(true);
            ui->dSpinBox->setEnabled(true);

            ui->xSpinBox->setValue(0.1);
            ui->ySpinBox->setValue(0.1);
            ui->aSpinBox->setValue(1.0);
            ui->bSpinBox->setValue(0.9);
            ui->cSpinBox->setValue(0.4);
            ui->dSpinBox->setValue(6.0);

            break;
        }
        case LorenzSystem:
        {
            ui->xSpinBox->setEnabled(true);
            ui->ySpinBox->setEnabled(true);
            ui->zSpinBox->setEnabled(true);
            ui->bSpinBox->setEnabled(true);
            ui->cSpinBox->setEnabled(true);
            ui->dSpinBox->setEnabled(false);

            ui->xSpinBox->setValue(0.3);
            ui->ySpinBox->setValue(0.3);
            ui->zSpinBox->setValue(0.3);
            ui->aSpinBox->setValue(10);
            ui->bSpinBox->setValue(28);
            ui->cSpinBox->setValue(8.0/3.0);
        }
    }
}

void Board::on_runButton_clicked()
{
    int amountGeneration = ui->amountGenerationSpinBox->value();
    int amountIndividual = ui->amountIndividualSpinBox->value();
    int amountRun = ui->amountRunSpinBox->value();
    int amountData = ui->amountDataSpinBox->value();
    int stablePeriod = ui->stablePeriodSpinBox->value();
    int amountOrbits = ui->amountOrbitComboBox->currentText().toInt();
    int system = ui->systemComboBox->currentIndex();
    int delay = ui->delaySpinBox->value();
    double x = ui->xSpinBox->value();
    double y = ui->ySpinBox->value();
    double z = ui->zSpinBox->value();
    double a = ui->aSpinBox->value();
    double b = ui->bSpinBox->value();
    double c = ui->cSpinBox->value();
    double d = ui->dSpinBox->value();
    bool noise = ui->noiseCheckBox->isChecked();
    double noiseIntensity = ui->noiseSpinBox->value();

    emit runSignal(amountGeneration,amountIndividual,amountRun,amountData,stablePeriod,system,amountOrbits,delay,x,y,z,a,b,c,d,noise,noiseIntensity);
}

 void Board::writeInfoSlot(QString info)
 {
     ui->consolePlainTextEdit->appendPlainText(info);
 }
