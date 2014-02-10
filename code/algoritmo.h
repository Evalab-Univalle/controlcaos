/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: algoritmo.h
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
 *
 * Descripción: Implementación de un algoritmo evolutivo que permite controlar sistemas dinámicos caóticos.
*/

#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "serie.h"
#include <QVector>

class Algoritmo
{
private:
    int cantidadGeneraciones;
    int cantidadIndividuos;
    int cantidadGenes;
    int cantidadEjecuciones;
    int periodoEstable;
    int cantidadOrbitas;
    int tamanoSerie;
    int indexMejorP; //mejor individuo del mating pool
    int P;//tamano del mating pool
    double minK;
    double maxK;
    double **poblacion;
    double **matingPool;
    double *orbitas;
    Serie *serie;
    double *solucion;
    bool solucionEncontrada;

    void generarPoblacionInicial();
    void mutar(double *cromosoma);
    void seleccionar();
    void reproducir();
    double evaluacion(double *cromosoma);
    void encontrarIntervalo();

    enum variable {K, R};

public:
    Algoritmo();
    Algoritmo(int cantidadIndividuos, int cantidadGenes, int cantidadGeneraciones, int cantidadEjecuciones, Serie *serie=0);
    ~Algoritmo();
    void setCantidadGeneraciones(int cantidadGeneraciones);
    void setCantidadIndividuos(int cantidadIndividuos);
    void setCantidadGenes(int cantidadGenes);
    void setSerie(Serie *serie);
    void setOrbitas(int cantidadOrbitas, double* orbitas);
    void setPeriodoEstable(int periodoEstable);
    void setTamanoSerie(int tamanoSerie);
    int getCantidadGeneraciones();
    int getCantidadIndividuos();
    int getCantidadGenes();
    int getTamanoSerie();
    double getMinK();
    double getMaxK();
    double* getResultado(bool resultadoFinal=true);
    void buscar();
    void imprimirPoblacion();
    bool getSolucionEncontrada();
};

#endif // ALGORITMO_H
