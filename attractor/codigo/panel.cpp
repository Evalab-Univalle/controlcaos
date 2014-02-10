/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 * Nombre del archivo: panel.cpp
 *
 */

#include "panel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QDoubleSpinBox>

Panel::Panel(QWidget *parent) :
    QWidget(parent)
{
    optionTypeLabel = new QLabel(tr("Seleccione la acción"));
    optionTypeComboBox = new QComboBox;
    optionTypeComboBox->addItem(tr("Graficar Atractor"));
    optionTypeComboBox->addItem(tr("Ver Sensibilidad"));
    connect(optionTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(typeChangeSlot(int)));

    optionSystemLabel = new QLabel(tr("Seleccione el sistema"));
    optionSystemComboBox = new QComboBox;
    optionSystemComboBox->addItem(tr("Lorenz"));
    optionSystemComboBox->addItem(tr("Henon"));
    optionSystemComboBox->addItem(tr("Tinkerbell"));
    optionSystemComboBox->addItem(tr("Ikeda"));
    optionSystemComboBox->addItem(tr("Gumowisk-Mira"));
    optionSystemComboBox->addItem(tr("The King"));
    connect(optionSystemComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(systemChangeSlot(int)));

    drawButton = new QPushButton("Graficar");
    connect(drawButton,SIGNAL(clicked()),this,SLOT(drawSlot()));

    aSpinBox = new QDoubleSpinBox;
    aSpinBox->setDecimals(9);
    aSpinBox->setRange(-10,30);
    aSpinBox->setSingleStep(0.000000001);
    QLabel *labelA = new QLabel(tr("a: "));
    QHBoxLayout *layoutA = new QHBoxLayout;
    layoutA->addWidget(labelA);
    layoutA->addWidget(aSpinBox);

    bSpinBox = new QDoubleSpinBox;
    bSpinBox->setDecimals(9);
    bSpinBox->setRange(-10,30);
    bSpinBox->setSingleStep(0.000000001);
    QLabel *labelB = new QLabel(tr("b: "));
    QHBoxLayout *layoutB = new QHBoxLayout;
    layoutB->addWidget(labelB);
    layoutB->addWidget(bSpinBox);

    cSpinBox = new QDoubleSpinBox;
    cSpinBox->setDecimals(9);
    cSpinBox->setRange(-10,30);
    cSpinBox->setSingleStep(0.000000001);
    QLabel *labelC = new QLabel(tr("c: "));
    QHBoxLayout *layoutC = new QHBoxLayout;
    layoutC->addWidget(labelC);
    layoutC->addWidget(cSpinBox);

    dSpinBox = new QDoubleSpinBox;
    dSpinBox->setDecimals(9);
    dSpinBox->setRange(-10,30);
    dSpinBox->setSingleStep(0.000000001);
    QLabel *labelD = new QLabel(tr("d: "));
    QHBoxLayout *layoutD = new QHBoxLayout;
    layoutD->addWidget(labelD);
    layoutD->addWidget(dSpinBox);

    deltaSpinBox = new QDoubleSpinBox;
    deltaSpinBox->setDecimals(9);
    deltaSpinBox->setSingleStep(0.000000001);
    QLabel *labelDelta = new QLabel(tr("delta: "));
    QHBoxLayout *layoutDelta = new QHBoxLayout;
    layoutDelta->addWidget(labelDelta);
    layoutDelta->addWidget(deltaSpinBox);

    infoLabel = new QLabel;
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(optionTypeLabel);
    layout1->addWidget(optionTypeComboBox);
    layout1->addWidget(optionSystemLabel);
    layout1->addWidget(optionSystemComboBox);
    layout1->addWidget(drawButton);
    layout1->addSpacing(30);
    layout1->addLayout(layoutA);
    layout1->addLayout(layoutB);
    layout1->addLayout(layoutC);
    layout1->addLayout(layoutD);
    layout1->addLayout(layoutDelta);
    layout1->addStretch(250);
    layout1->addWidget(infoLabel);

    this->setLayout(layout1);
    this->setMaximumWidth(250);

    this->initValues();
}

Panel::~Panel()
{
    delete optionTypeComboBox;
    delete optionSystemComboBox;
    delete optionTypeLabel;
    delete optionSystemLabel;
    delete drawButton;
    delete aSpinBox;
    delete bSpinBox;
    delete cSpinBox;
    delete dSpinBox;
    delete deltaSpinBox;
    delete infoLabel;

    optionTypeComboBox = 0;
    optionSystemComboBox = 0;
    optionTypeLabel = 0;
    optionSystemLabel = 0;
    drawButton = 0;
    aSpinBox = 0;
    bSpinBox = 0;
    cSpinBox = 0;
    dSpinBox = 0;
    deltaSpinBox = 0;
    infoLabel = 0;
}

/*
Slot, recibe una señal del boton dibujar
*/
void Panel::drawSlot()
{
    this->getValues();
    QVector<double> value;
    value << x << y << z << a << b << c << d << delta;
    emit initValueChangeSignal(value);
    emit systemSignal(optionSystemComboBox->currentIndex());//por si no se ha seleccionado el sistema y está por defecto.
    if(optionTypeComboBox->currentIndex()==1)
    {
        emit startTimerSignal();//Esta señal inicia un timer en lienzo que llama a updateGL, no hay necesidad de volver a llamarlo al emitir drawSignal
    }
    else{
        emit drawSignal();//esta señal se conecta directamente con updateGL en el lienzo
    }
}

/*
Esta función inicializa los valores iniciales de la interfaz, que corresponde al sistema de Lorenz
*/
void Panel::initValues()
{
    this->x = 1.0;
    this->y = 1.0;
    this->z = 1.0;

    this->aSpinBox->setValue(-2.666666667);
    this->bSpinBox->setValue(-10);
    this->cSpinBox->setValue(28);
    this->cSpinBox->setEnabled(true);
    this->dSpinBox->setEnabled(false);
    this->deltaSpinBox->setValue(0.0001);

    this->infoLabel->setText(tr("Este Sistema está en 3D \n Use A W S D T F G H PDown y PUp"));
}

/*Slot, llamado cada vez que el comboBox del tipo de sistema cambie, hace que los spinBox
tomen un valor por defecto para cada sistema en particular. También emite una señal que actualiza
el tipo de sistema en el lienzo*/
void Panel::systemChangeSlot(const int &value)
{
    switch(value)
    {
        case Lorenz:
        {
            this->initValues();
            break;
        }
        case Henon:
        {
            this->x=-0.1;
            this->y=0.1;
            this->aSpinBox->setValue(1.3);
            this->bSpinBox->setValue(0.31);
            this->deltaSpinBox->setValue(0.0001);
            this->cSpinBox->setEnabled(false);
            this->dSpinBox->setEnabled(false);
            this->infoLabel->setText(tr("Este Sistema está en 2D \n Use T F G H PDown y PUp"));
            break;
        }
        case Tinkerbell:
        {
            this->x=-0.72;
            this->y=-0.64;
            this->aSpinBox->setValue(0.9);
            this->bSpinBox->setValue(-0.6013);
            this->cSpinBox->setValue(2.0);
            this->cSpinBox->setEnabled(true);
            this->dSpinBox->setValue(0.5);
            this->dSpinBox->setEnabled(true);
            this->deltaSpinBox->setValue(0.0001);
            this->infoLabel->setText(tr("Este Sistema está en 2D \n Use T F G H PDown y PUp"));
            break;
        }
        case Ikeda:
        {
            this->x=0.1;
            this->y=0.1;
            this->aSpinBox->setValue(1.0);
            this->bSpinBox->setValue(0.9);
            this->cSpinBox->setEnabled(true);
            this->cSpinBox->setValue(0.4);
            this->dSpinBox->setEnabled(true);
            this->dSpinBox->setValue(6.0);
            this->deltaSpinBox->setValue(0.0001);
            this->infoLabel->setText(tr("Este Sistema está en 3D \n Use A W S D T F G H PDown y PUp"));
            break;
        }
        case GumowiskMira:
        {
            this->x=-10;
            this->y=1;
            this->aSpinBox->setValue(-0.749);
            this->bSpinBox->setValue(1);
            this->cSpinBox->setEnabled(false);
            this->dSpinBox->setEnabled(false);
            this->deltaSpinBox->setValue(0.0001);
            this->infoLabel->setText(tr("Este Sistema está en 2D \n Use T F G H PDown y PUp"));
            break;
        }
        case TheKing:
        {
            this->x=0.1;
            this->y=0.1;
            this->aSpinBox->setValue(-0.966918);
            this->bSpinBox->setValue(2.879879);
            this->cSpinBox->setValue(0.765145);
            this->cSpinBox->setEnabled(true);
            this->dSpinBox->setValue(0.744728);
            this->dSpinBox->setEnabled(true);
            this->deltaSpinBox->setValue(0.0001);
            this->infoLabel->setText(tr("Este Sistema está en 2D \n Use T F G H PDown y PUp"));
        }
    }

    emit systemSignal(value);
}

/*Slot, emite una señal que actualiza el tipo de acción a realizar en el lienzo*/
void Panel::typeChangeSlot(const int &value)
{
    emit typeSignal(value);
}

/*Obtiene los valores de los spinBox*/
void Panel::getValues()
{
    this->a = this->aSpinBox->value();
    this->b = this->bSpinBox->value();
    this->c = this->cSpinBox->value();
    this->d = this->dSpinBox->value();
    this->delta = this->deltaSpinBox->value();
}
