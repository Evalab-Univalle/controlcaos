# Autor: Cristian Leonardo Ríos López
# Código: 0842139
# Institución: Universidad del Valle
# Fecha: Mayo de 2013
# Licencia: GPL v.1
# Nombre del archivo: boxcount.R
# Email: cristian.rios@correounivalle.edu.co
# Descripción: Estima la dimensión fractal de una serie usando el algoritmo boxcount


#crea la serie para la ecuacion logistica
#x_t+1 = k*x_t*(1-x_t)

serieEL<-function(x,k,N,s)
{
	Xi<-numeric()
	Xi[1]<-x
	for (i in 2:(N+s))
	{
   		Xi[i]<-k*Xi[i-1]*(1-Xi[i-1])
	}
	return(array(Xi[(s+1):(N+s)], dim=c(N,1)))
}

#crea una serie para el sistema de Henon
#x_t+1 = 1-a*x^2_t+y_t
#y_t+1 = b*x_t

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

serieSH<-function(x,y,a,b,N,s)
{
  points <- numeric()
	Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:(N+s))
	{
		Xi[i]<-1-a*Xi[i-1]*Xi[i-1]+Yi[i-1]
		Yi[i]<-b*Xi[i-1]
	}

  return(array(c(Xi[(s+1):(N+s)],Yi[(s+1):N+s]),dim=c(N,2)))
}

#crea una serie para el sistema de Tinkerbell
serieTK<-function(x,y,a,b,c,d,N,s)
{
   Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:(N+s))
	{
		Xi[i]<-Xi[i-1]*Xi[i-1]-Yi[i-1]*Yi[i-1]+a*Xi[i-1]+b*Yi[i-1]
        Yi[i]<-2*Xi[i-1]*Yi[i-1]+c*Xi[i-1]+d*Yi[i-1]
	}

	#se puede retornar cualquiera de las componentes
	return(array(c(Xi[(s+1):(N+s)], Yi[(s+1):(N+s)]), dim=c(N,2)))
}

#crea una serie para el sistema de Ikeda
serieIK<-function(x,y,a,b,c,d,N,s)
{
	Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:(N+s))
	{
		u<-c-(d/(1+Xi[i-1]*Xi[i-1]+Yi[i-1]*Yi[i-1]))
		Xi[i]<-a+b*(Xi[i-1]*cos(u)-Yi[i-1]*sin(u))
		Yi[i]<-b*(Xi[i-1]*sin(u)+Yi[i-1]*cos(u))	
	}
	return(array(c(Xi[(s+1):(N+s)], Yi[(s+1):(N+s)]), dim=c(N,2)))
}

#-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-

boxcount <- function(data)
{
  nmax <- numeric() #maximo punto
  nmin <- numeric() #minimo punto
  ncol <- ncol(data) #numero de columnas
  N <- numeric() #cantidad de cajas
  L <- numeric() #lonfitud de cajas
  c <- 1 #contador

  if(ncol == 1)#una dimensión
  {
    nmax <- max(data)
    nmin <- min(data)
  }else #ncol == 2 dos dimensiones
  {
    nmax <- max(max(data[,1]), max(data[,2]))
    nmin <- min(min(data[,1]), min(data[,2]))
  }
  
  rango <- nmax - nmin  #distancia entre el numero maximo y minimo

  for(i in 2^(1:8)) #cantidad de diviciones
  {
    l <- rango / i # longitud de la caja
    #print(l)
  
    if(ncol == 1)
    {
      boxes <- array(rep(0,i))
      for(k in 0:(i-1)) #numero de diviciones
      {
        for(j in 1:nrow(data))
        {
          if(data[j,1] >= k*l+nmin && data[j,1] < (k+1)*l+nmin)#el punto maximo no entra en ningun caja
          {
            boxes[k+1] = 1
            break
          }
        }
      }
      print(paste("boxes ",i,": ",sum(boxes)))
      N[c] <- sum(boxes)
      L[c] <- l
      c <- c+1
    }else #ncol == 2
    {
      boxes <- matrix(rep(0,i*2), nrow=i, ncol=i)
      for(k in 0:(i-1)) #numero de diviciones fila
      {
        for(k2 in 0:(i-1)) #numero diviciones columna
        {
          for(j in 1:nrow(data))
          {
            if(data[j,1] >= k*l+nmin && data[j,1] < (k+1)*l+nmin &&
               data[j,2] >= k2*l+nmin && data[j,2] < (k2+1)*l+nmin)
            {
              boxes[k+1,k2+1] = 1
              break
            }
          } 
        }
      }
      print(paste("boxes ",i,": ",sum(boxes)))
      N[c] <- sum(boxes)
      L[c] <- l
      c <- c+1
    }
  }

  N <- log(N)
  L <- log(L)

  ajuste <- lm(N ~ L)
  return(-ajuste$coefficients[2])
}

#-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.---.-.-.-..-.

#calcular para la ecuacion logistica
x<-0.1  #valor inicial de x
k<-3.9    #parametro de la ecuacion
N<-1000 #cantidad de puntos de la serie
s<-100	#estabilización
Xi_EL<-serieEL(x,k,N,s)	#serie temporal de la ecuacion logistica
dim_EL <- boxcount(Xi_EL)
#0.9942281 N=1000 s=100

#---------------------------------

#calcular para el sistema de Henon
x<--0.1  #valores iniciales de x e y
y<-0.1
a<-1.4   #parametros de la ecuación
b<-0.3
N<-1000
s<-100	#estabilización
Xi_SH<-serieSH(x,y,a,b,N,s)  #serie temporal del sistema de Henon
dim_SH <- boxcount(Xi_SH) 
#1.147951 N=1000 s=100

#-------------------------------------

#calcular para el sistema de tinkerbell
x<-0.1
y<-0.1
a<-0.5
b<--0.6
c<-2.2
d<-0.5
N<-1000
s<-100
Xi_TK<-serieTK(x,y,a,b,c,d,N,s)
dim_TK <- boxcount(Xi_TK) 
#1.085137 N=1000 s=100 

#----------------------------------------

#calcular para el sistema de Ikeda
x<-0.1
y<-0.1
a<-1.0
b<-0.9
c<-0.4
d<-6.0
N<-1000
s<-100
Xi_IK<-serieIK(x,y,a,b,c,d,N,s)
dim_IK <- boxcount(Xi_IK)
#1.18931 N=1000 s=100
#1.294413
