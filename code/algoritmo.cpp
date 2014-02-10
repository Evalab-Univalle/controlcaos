/*
 * Autor: Cristian Leonardo Ríos López
 * Código: 0842139
 * Institución: Universidad del Valle
 * Fecha: Mayo de 2013
 * Nombre del archivo: algoritmo.cpp
 * Licencia: GPL v.1
 * Email: cristian.rios@correounivalle.edu.co
*/

#include "algoritmo.h"
#include "matematica.h"
#include <math.h>
#include <iostream>

Algoritmo::Algoritmo(){}

Algoritmo::Algoritmo(int cantidadIndividuos, int cantidadGenes, int cantidadGeneraciones, int cantidadEjecuciones, Serie *serie)
{
    this->cantidadGeneraciones = cantidadGeneraciones;
    this->cantidadIndividuos = cantidadIndividuos;
    this->cantidadGenes = cantidadGenes;
    this->cantidadEjecuciones = cantidadEjecuciones;
    this->solucion = 0;

    this->poblacion = new double*[this->cantidadIndividuos];
    for(int i=0;i<this->cantidadIndividuos;i++)
    {
        this->poblacion[i] = new double[this->cantidadGenes];//K
    }

    this->P = ceil(this->cantidadIndividuos*0.1);//el tamanoo del mating pool es aprox 10% la cantidad de cromosomas
    this->matingPool = new double*[this->P];

    this->serie = serie;
}

Algoritmo::~Algoritmo()
{
    for(int i=0;i<this->cantidadIndividuos;i++)
    {
        delete this->poblacion[i];
        this->poblacion[i]=0;
    }
    delete this->poblacion;
    this->poblacion=0;

    for(int i=0;i<this->P;i++)
    {
        this->matingPool[i]=0;
    }
    this->matingPool=0;
}

/*
 * Método buscar: realiza el proceso del algoritmo.
 */
void Algoritmo::buscar()
{
    this->encontrarIntervalo();
    if(!this->solucionEncontrada)
        return;
    for(int g=0;g<this->cantidadEjecuciones;g++)
    {
        this->generarPoblacionInicial();

        for(int i=0;i<this->cantidadGeneraciones;i++)
        {
            this->seleccionar();
            this->reproducir();
            //como son punteros, al momento de realizar la reproduccion se realiza el reemplazo
        }

        double *resultado = this->getResultado(false);//es un resultado parcial

        //se asigna a solucion el mejor resultado de cada generacion
        if(this->solucion == 0)
        {
            this->solucion = resultado;
        }else
        {
            double evalActual = this->evaluacion(resultado);
            double evalAnterior = this->evaluacion(this->solucion);

            if(evalActual<evalAnterior)//la solucion obtenida es mejor que la actual
            {
                delete this->solucion;//solucion contiene una copia de un cromosoma de la poblacion
                this->solucion = resultado;
                resultado = 0;
            }
        }
    }
}

/*
 * Método encontraIntervalo: encuentra el intervalo en el que debe de encontrar K.
 * El proceso se repite 100 veces como máximo, si en eso no encuentra el intervalo el
 * proceso del algoritmo se detiene.
 */
void Algoritmo::encontrarIntervalo()
{
    double step = 0.02;
    double top = 2;
    double bottom = -2;

    double *minK = new double[1];
    double *maxK = new double[1];

    int executions = 0;
    int amount = 100;

    do{
        minK[0] = bottom;
        maxK[0] = top;
        double evalNeg = this->evaluacion(minK);
        double evalPos = this->evaluacion(maxK);

        while(Matematica::isNan(evalNeg) && minK[0]<0)
        {
            minK[0] += step;
            evalNeg = this->evaluacion(minK);
        }
        while(Matematica::isNan(evalPos) && maxK[0]>0)
        {
            maxK[0] -= step;
            evalPos = this->evaluacion(maxK);
        }
        executions++;
    }while((Matematica::isNan(this->evaluacion(minK)) || Matematica::isNan(this->evaluacion(maxK))) && executions < amount);

    if(executions == amount){
        this->solucionEncontrada = false;
    }else{
        this->solucionEncontrada = true;
        this->minK = minK[0];
        this->maxK = maxK[0];
    }

    delete minK;
    minK = 0;
    delete maxK;
    maxK = 0;
}

/*
 * Método evaluacion: implementa la función de evaluación del algoritmo
 */
double Algoritmo::evaluacion(double *cromosoma)
{
    this->serie->setParametrosControl(cromosoma[Algoritmo::K]);
    this->serie->calcularSerie(this->periodoEstable);//debido a la particularidad de la evaluación no son necesarios todos los datos
    double *serieSistema = serie->getSerieX();
    double diferencia = 0.0;

    for(int i=0;i<this->periodoEstable;i++)
    {
        diferencia += fabs(serieSistema[i+this->cantidadOrbitas]-serieSistema[i]);
    }

    //no eliminar, la serie resultado realmente pertenece al objeto serie
    serieSistema = 0;

    return diferencia;
}

/*
 * Método generarPoblacionInicial: genera la población inicial para la ejecución del algoritmo
 */
void Algoritmo::generarPoblacionInicial()
{
    for(int i=0;i<this->cantidadIndividuos;i++)
    {
        for(int j=0;j<this->cantidadGenes;j++)
        {
            double num = Matematica::getNumeroGauss(0,1);
            if((num >= this->minK) && (num <= this->maxK))
            {
                this->poblacion[i][j] = num;
            }else
            {
                j--;
            }
        }
    }
}

int Algoritmo::getCantidadGeneraciones()
{
    return cantidadGeneraciones;
}

int Algoritmo::getCantidadIndividuos()
{
    return cantidadIndividuos;
}

int Algoritmo::getCantidadGenes()
{
    return this->cantidadGenes;
}

double Algoritmo::getMinK()
{
    return this->minK;
}

double Algoritmo::getMaxK()
{
    return this->maxK;
}

/*
 * Método getResultado: retorna el resultado del algoritmo. Existen dos posibles resultados uno parcial y otro final.
 * El resultado parcial se da cuando se ejecuta el algoritmo multimples veces.
 */
double* Algoritmo::getResultado(bool resultadoFinal)
{
    if(resultadoFinal)
    {
        return this->solucion;
    }else
    {
        double mejorPuntaje = 10000.0, eval;
        int index=-1;
        for(int i=0;i<this->cantidadIndividuos;i++)
        {
            eval = this->evaluacion(this->poblacion[i]);
            if(eval < mejorPuntaje)
            {
                index = i;
                mejorPuntaje = eval;
            }
        }

        double *resultado = new double[this->cantidadGenes];
        for(int i=0;i<this->cantidadGenes;i++)
        {
            resultado[i] = this->poblacion[index][i];
        }
        return resultado;
    }
}

bool Algoritmo::getSolucionEncontrada()
{
    return this->solucionEncontrada;
}

int Algoritmo::getTamanoSerie()
{
    return this->tamanoSerie;
}

void Algoritmo::imprimirPoblacion()
{
    int cantidadNan = 0;
    double eval;

    for(int i=0;i<this->cantidadIndividuos;i++)
    {
        eval = this->evaluacion(this->poblacion[i]);
        std::cout << "Individuo " << i << ": " << this->poblacion[i][K] << " Aptitud: " << eval << std::endl;
        if(Matematica::isNan(eval))
            cantidadNan++;
    }
    std::cout << "Cantidad nan " << cantidadNan << std::endl << std::endl;
}

void Algoritmo::mutar(double *cromosoma)
{
    for(int i=0;i<this->cantidadGenes;i++)
    {
         cromosoma[i] += Matematica::getNumeroGauss(0,0.06); //numeros entre -0.2 y 0.2 aprox
    }
}

/*
 * Método reproducir: realiza la reproducción, mantiene el mejor de la población.
 */
void Algoritmo::reproducir()
{
    for(int i=0;i<this->P;i++)
    {
        if(i!=this->indexMejorP)
        {
            this->mutar(this->poblacion[i]);
        }
    }
}

/*
 * Método seleccionar: realiza la selección, esta se hace por torneo.
 */
void Algoritmo::seleccionar()
{
    //los cromosomas se seleccionan por torneo

    int tamTemporal = ceil(this->cantidadIndividuos*0.03);//se tomará el 3% de los individuos
    double puntajeMejorP = 10000.0;

    for(int i=0;i<this->P;i++)
    {
        double puntajeMejor = 10000.0;//el mejor puntaje es un numero cercano a cero, desconozco lo grande que este valor inicial deba ser
        int index, indexMejor=-1;

        for(int j=0;j<tamTemporal;j++)
        {
            index = rand()%this->cantidadIndividuos;
            double eval = this->evaluacion(this->poblacion[index]);

            if(eval < puntajeMejor)
            {
                puntajeMejor = eval;
                indexMejor = index;
            }
        }
        if(indexMejor != -1)
        {
            this->matingPool[i] = this->poblacion[indexMejor];
            if(puntajeMejor < puntajeMejorP)
            {
                this->indexMejorP = index;
                puntajeMejorP = puntajeMejor;
            }
        }else
        {
            i--;
        }
    }
}

void Algoritmo::setCantidadGeneraciones(int cantidadGeneraciones)
{
    this->cantidadGeneraciones = cantidadGeneraciones;
}

void Algoritmo::setCantidadIndividuos(int cantidadIndividuos)
{
    this->cantidadIndividuos = cantidadIndividuos;
}

void Algoritmo::setCantidadGenes(int cantidadGenes)
{
    this->cantidadGenes = cantidadGenes;
}

void Algoritmo::setOrbitas(int cantidadOrbitas, double *orbitas)
{
    this->cantidadOrbitas = cantidadOrbitas;
    this->orbitas = orbitas;
}

void Algoritmo::setPeriodoEstable(int periodoEstable)
{
    this->periodoEstable = periodoEstable;
}

void Algoritmo::setSerie(Serie *serie)
{
    this->serie = serie;
}

void Algoritmo::setTamanoSerie(int tamanoSerie)
{
    this->tamanoSerie = tamanoSerie;
}

/*double Algoritmo::evaluacion(double *cromosoma)
{
    this->serie->setParametrosControl(cromosoma[Algoritmo::K]);
    double *serieSistema = serie->getSerie(this->tamanoSerie);
    double diferencia = 0.0;

    bool encontro = false;
    for(int i=0;i<this->tamanoSerie;i++)//se recorre el total de la serie
    {
        if(fabs(this->orbitas[0]-serieSistema[i])<0.001)//hacer la tolerancia variable. Se busca que el valor obtenido este muy cerca del  valor real
        {
            //cout << "econtro " << i << endl;
            encontro = true;
            if((this->tamanoSerie-i) > this->periodoEstable)//hay datos suficientes para cumplir con el periodo estable
            {
                for(int j=i;j<this->periodoEstable+i;)
                {
                    for(int k=0;k<this->cantidadOrbitas;k++,j++)
                    {
                        diferencia += fabs(this->orbitas[k]-serieSistema[j]);
                    }
                }
                break;//si aun quedan mas datos no es necesario que siga recorriendo la serie
            }else //no hay suficientes datos para cubrir el periodoEstable, se suma una penalizacion
            {
                for(int j=i;j<this->tamanoSerie;)
                {
                    for(int k=0;k<this->cantidadOrbitas;k++,j++)
                    {
                        diferencia += fabs(this->orbitas[k]-serieSistema[j]) + j;
                    }
                }
                break;//igual hay que hacer break porque no se incrementa i
            }
        }
    }
    if(!encontro)//si al terminar de recorrer toda la serie no encontro el valor deseado, el valor retornado es muy grande, es el peor valor posible
    {
        diferencia = 10000;
    }
}*/

/*double Algoritmo::evaluacion(double *cromosoma)
{
    this->serie->setParametrosControl(cromosoma[Algoritmo::K]);
    double *serieSistema = serie->getSerie(this->tamanoSerie);
    double diferencia = 0.0;

    for(int i=0;i<this->periodoEstable;)
    {
        for(int j=0;j<cantidadOrbitas;j++,i++)
        {
            diferencia += fabs(this->orbitas[j]-serieSistema[i]);
        }
    }

    delete serieSistema;
    serieSistema = 0;

    return diferencia;
}*/
