# Autor: Cristian Leonardo Ríos López
# Código: 0842139
# Institución: Universidad del Valle
# Fecha: Mayo de 2013
# Licencia: GPL v.1
# Nombre del archivo: control.R
# Email: cristian.rios@correounivalle.edu.co
# Descripción: Permite crear series temporales de diferentes sistemas caóticos con y sin control y graficarlas
# Los parámetros que se usan para realizar el control son obtenidos usando otro algoritmo.

#-------------Ecuacion logistica-----------------------------------

x0<-0.1
r<-3.8
N<-100
O<-1 #cantidad de orbitas

serieEL<-function(x,r,N,R,K,O,I)
{
    #Xi -> sistema con ruido y control segun el caso
    #C -> accion de control aplicada
    #Zi -> sistemas sin control, con ruido o sin ruido segun el caso
    #S -> ruido
    Xi<-C<-Zi<-numeric()
    s<-rnorm(1)*I
    Zi[1]<-x
    Zi[2]<-r*Zi[1]*(1-Zi[1]) + s*R
	Xi[1]<-x
	Xi[2]<-r*Xi[1]*(1-Xi[1]) + s*R
    C[1]<-C[2]<-0
	
	for (i in 3:N)
	{
        s<-rnorm(1)*I
        C[i]<-K*(Xi[i-1-O]-Xi[i-1])
   		Xi[i]<-r*Xi[i-1]*(1-Xi[i-1]) + C[i] + s*R
        Zi[i]<-r*Zi[i-1]*(1-Zi[i-1]) + s*R
	}
	return(list(Xi,C,Zi))
}

Ruido<-0
K<-0
K<- -0.765887 #-0.8 <= K <= 0.12    periodo 1
K<- -0.206769 #-0.8 <= K <= 0.12    periodo 2
K<- -0.179432 #-0.8 <= K <= 0.12    periodo 3
X<-serieEL(x0,r,N,0,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='F',col='red')

Ruido<-0.02
K<- -0.481874 #-0.8 <= K <= 0.12    periodo 1   Ruido=0.02
K<- -0.372578 #-0.76 <= K <= 0.1    periodo 2   Ruido=0.02
K<- -0.285631 #-0.92 <= K <= 0.1    periodo 4   Ruido=0.02

Ruido<-0.01
K<- -0.42997 #-0.84 <= K <= 0.12    periodo 1   Ruido=0.01
K<- -0.240823 #-0.68 <= K <= 0.1    periodo 2   Ruido=0.01
K<- -0.208122 #-0.86 <= K <= 0.12   periodo 4   Ruido=0.01

X<-serieEL(x0,r,N,1,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='F',col='red')
plot(X[[3]],type='l',xlab='n',ylab='X') #sistemas solo con ruido

#-.-.-.-.-.-.-.-.-.-.--..-.-.--.-.--.-.-.-.-.-.-.-.--.
#---------------------sistema de henon----------------

x0<--0.1
y0<-0.1
a<-1.2
b<-0.3
N<-100
O<-1 #cantidad de orbitas

serieSH<-function(x,y,a,b,N,R,K,O,I)
{
	Xi<-Yi<-C<-Zxi<-Zyi<-numeric()
    s<-rnorm(1)*I
	Xi[1]<-x
	Yi[1]<-y
    Xi[2]<-1-a*Xi[1]*Xi[1]+Yi[1] + s*R
	Yi[2]<-b*Xi[1]
    Zxi[1]<-x
	Zyi[1]<-y
    Zxi[2]<-1-a*Zxi[1]*Zxi[1]+Zyi[1] + s*R
	Zyi[2]<-b*Zxi[1]
    C[1]<-C[2]<-0

	for(i in 3:N)
	{
        s<-rnorm(1)*I
        C[i]<-K*(Xi[i-1-O]-Xi[i-1])
		Xi[i]<-1-a*Xi[i-1]*Xi[i-1]+Yi[i-1] + C[i] + R*s
		Yi[i]<-b*Xi[i-1]
   		Zxi[i]<-1-a*Zxi[i-1]*Zxi[i-1]+Zyi[i-1] + R*s
		Zyi[i]<-b*Zxi[i-1]
	}

	return(list(Xi,Yi,C,Zxi,Zyi))
}

K<-0
K<--0.854827 #-1.24 <= K <= 0.16    periodo 1
K<--0.291749 #-1.24 <= K <= 0.16    periodo 2
K<--0.196889 #-1.24 <= K <= 0.16    periodo 4
X<-serieSH(x0,y0,a,b,N,0,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[1]][10:100],X[[2]][10:100],xlab='X',ylab='Y',pch='*',type='l')
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')

Ruido<-0.08
K<- -0.87709 #-1.2 <= K <= 0.12     periodo 1   Ruido=0.08
K<- -0.458163 #-1.18 <= K <= 0.28   periodo 2   Ruido=0.08
K<- -0.39932 #-1.24 <= K <= 0.1     periodo 4   Ruido=0.08

Ruido<-0.04
K<- -0.78253 #-1.22 <= K <= 0.14    periodo 1   Ruido=0.04
K<- -0.360447 #-1.26 <= K <= 0.1    periodo 2   Ruido=0.04
K<- -0.279422 #-1.24 <= K <= 0.12   periodo 4   Ruido=0.04

X<-serieSH(x0,y0,a,b,N,1,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[4]],type='l',xlab='n',ylab='X') #x sin control
plot(X[[5]],type='l',xlab='n',ylab='Y') #y sin control
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#---------------Sistema de Ikeda---------------------------------

x<-0.1
y<-0.1
a<-1.0
b<-0.9
c<-0.4
d<-6.0
N<-100
O<-1

serieIK<-function(x,y,a,b,c,d,N,R,K,O,I)
{
	Xi<-Yi<-Zxi<-Zyi<-C<-numeric()
    s<-rnorm(1)*I
	Xi[1]<-x
	Yi[1]<-y
    u<-(c-d)/(1+Xi[1]*Xi[1]+Yi[1]*Yi[1])
	Xi[2]<-a+b*(Xi[1]*cos(u)-Yi[1]*sin(u)) + s*R
	Yi[2]<-b*(Xi[1]*sin(u)+Yi[1]*cos(u))
    Zxi[1]<-x
	Zyi[1]<-y
    Zxi[2]<-a+b*(Zxi[1]*cos(u)-Zyi[1]*sin(u)) + s*R
	Zyi[2]<-b*(Zxi[1]*sin(u)+Zyi[1]*cos(u))	
	C[1]<-C[2]<-0

    for(i in 3:N)
	{
        s<-rnorm(1)*I
        C[i]<-K*(Xi[i-1-O]-Xi[i-1])
		u<-(c-d)/(1+Xi[i-1]*Xi[i-1]+Yi[i-1]*Yi[i-1])
		Xi[i]<-a+b*(Xi[i-1]*cos(u)-Yi[i-1]*sin(u)) + C[i] + s*R
		Yi[i]<-b*(Xi[i-1]*sin(u)+Yi[i-1]*cos(u))
        u<-(c-d)/(1+Zxi[i-1]*Zxi[i-1]+Zyi[i-1]*Zyi[i-1])
		Zxi[i]<-a+b*(Zxi[i-1]*cos(u)-Zyi[i-1]*sin(u)) + s*R
		Zyi[i]<-b*(Zxi[i-1]*sin(u)+Zyi[i-1]*cos(u))
	}
	return(list(Xi,Yi,C,Zxi,Zyi))
}

K<-0
K<- -1.05136  #-2 <= K <= 2 periodo 1
K<- -0.159932 #-2 <= K <= 2 periodo 2
K<- -0.324299 #-2 <= K <= 2 periodo 4

#otros
K<- -0.803969   #periodo A

X<-serieIK(x,y,a,b,c,d,N,0,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[1]][60:300],X[[2]][60:300],xlab='X',ylab='Y',pch='*',type='l')
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')

Ruido<-0.015
K<- -0.569009  #-2 <= K <= 2    periodo 1 Ruido=0.02
K<- -0.166959  #-2 <= K <= 2    periodo 2 Ruido=0.02
K<- -0.315061  #-2 <= K <= 2    periodo 4 Ruido=0.02

X<-serieIK(x,y,a,b,c,d,N,1,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[4]],type='l',xlab='n',ylab='X') #x sin control
plot(X[[5]],type='l',xlab='n',ylab='Y') #y sin control
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')
#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#---------------Sistema de Tinkerbell---------------------------------

x<-0.1
y<-0.1
a<-0.5
b<--0.6
c<-2.2
d<-0.5
N<-100
O<-1

serieTK<-function(x,y,a,b,c,d,N,R,K,O,I)
{
    Xi<-Yi<-C<-Zxi<-Zyi<-numeric()
    s<-rnorm(1)*I
	Xi[1]<-x
	Yi[1]<-y
    Xi[2]<-Xi[1]*Xi[1]-Yi[1]*Yi[1]+a*Xi[1]+b*Yi[1] + s*R
    Yi[2]<-2*Xi[1]*Yi[1]+c*Xi[1]+d*Yi[1]
    Zxi[1]<-x
	Zyi[1]<-y
    Zxi[2]<-Zxi[1]*Zxi[1]-Zyi[1]*Zyi[1]+a*Zxi[1]+b*Zyi[1] + s*R
    Zyi[2]<-2*Zxi[1]*Zyi[1]+c*Zxi[1]+d*Zyi[1]
    C[1]<-C[2]<-0

	for(i in 3:N)
	{
        s<-rnorm(1)*I
        C[i]<-K*(Xi[i-1-O]-Xi[i-1])
		Xi[i]<-Xi[i-1]*Xi[i-1]-Yi[i-1]*Yi[i-1]+a*Xi[i-1]+b*Yi[i-1] + C[i] + s*R
        Yi[i]<-2*Xi[i-1]*Yi[i-1]+c*Xi[i-1]+d*Yi[i-1]
        Zxi[i]<-Zxi[i-1]*Zxi[i-1]-Zyi[i-1]*Zyi[i-1]+a*Zxi[i-1]+b*Zyi[i-1] + s*R
        Zyi[i]<-2*Zxi[i-1]*Zyi[i-1]+c*Zxi[i-1]+d*Zyi[i-1]
	}

	return(list(Xi,Yi,C,Zxi,Zyi))
}

K<-0
K<-0.820371 #-0.22 <= K <= 1.16     periodo 1
K<-1.15024 #-0.22 <= K <= 1.16      periodo 2
K<-1.01948 #-0.22 <= K <= 1.16      periodo 4
X<-serieTK(x,y,a,b,c,d,N,0,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[1]],X[[2]],xlab='X',ylab='Y',pch='*',type='l')
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')

Ruido<-0.005
K<- 0.838537 #-0.22 <= K <= 1.14    periodo 1   Ruido=0.005
K<- 1.12989 #-0.2 <= K <= 1.14      periodo 2   Ruido=0.005
K<- 1.05484 #-0.18 <= K <= 1.16     periodo 4   Ruido=0.005

X<-serieTK(x,y,a,b,c,d,N,1,K,O,Ruido)
plot(X[[1]],type='l',xlab='n',ylab='X')
plot(X[[2]],type='l',xlab='n',ylab='Y')
plot(X[[4]],type='l',xlab='n',ylab='X') #x sin control
plot(X[[5]],type='l',xlab='n',ylab='Y') #y sin control
plot(X[[3]],type='l',xlab='n',ylab='F',col='red')

#-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-
