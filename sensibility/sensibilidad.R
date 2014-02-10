# Autor: Cristian Leonardo Ríos López
# Código: 0842139
# Institución: Universidad del Valle
# Fecha: Mayo de 2013
# Licencia: GPL v.1
# Nombre del archivo: sensibilidad.R
# Email: cristian.rios@correounivalle.edu.co
# Descripción: Permite crear series temporales de diferentes sistemas caóticos para mostrar su sensibilidad a las
# condiciones iniciales.

#.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.
#libreria para resolver el sistema de lorenz
library('deSolve')

dif<-0.000001
#--------------------------------------------------------------------------------

#diagrama de sensibilidad para la ecuación logística
serieEL<-function(x,k,N)
{
	Xi<-numeric()
	Xi[1]<-x
	for (i in 2:N)
	{
   		Xi[i]<-k*Xi[i-1]*(1-Xi[i-1])
	}
	return(Xi)
}

sensibilidadEL<-function(dif,N)
{	k<-3.9
	x0<-0.1
	y1<-0
	y2<-1

	plot(serieEL(x0,k,N), xlab="", ylab="", xlim=c(0,N), ylim=c(y1,y2),axes=FALSE, col='blue', type='l')
	par(new=TRUE)
	plot(serieEL(x0+dif,k,N), xlim=c(0,N), ylim=c(y1,y2), col='red', xlab='N', ylab='X',type='l')
}

jpeg('sensibilidad_EL.jpg',width=700,height=700,quality=100)
sensibilidadEL(dif,40)
dev.off()

errorSensibilidadEL<-function(dif,N)
{
	k<-3.9
	x0<-0.1

	plot(serieEL(x0,k,N)-serieEL(x0+dif,k,N), type='l', ylab='Diferencia(Serie1, Serie2)', xlab='N', col='red')
}

jpeg('errorSensibilidad_EL.jpg',width=700,height=700,quality=100)
errorSensibilidadEL(dif,40)
dev.off()

#-------------------------------------------------------------------------------------

#diagrama de sensibilidad para el sistema de henon
serieSH<-function(x,y,a,b,N)
{
	Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:N)
	{
		Xi[i]<-1-a*Xi[i-1]*Xi[i-1]+Yi[i-1]
		Yi[i]<-b*Xi[i-1]
	}
	return(Xi)
}

sensibilidadSH<-function(dif,N)
{	a<-1.3
	b<-0.31
	x0<--0.1
	y0<-0.1
	y1<--1.5
	y2<-1.5

	plot(serieSH(x0,y0,a,b,N), xlab="", ylab="", xlim=c(0,N), ylim=c(y1,y2),axes=FALSE, col='blue', type='l')
	par(new=TRUE)
	plot(serieSH(x0+dif,y0,a,b,N), xlim=c(0,N), ylim=c(y1,y2), col='red', xlab='N', ylab='X',type='l')
}

jpeg('sensibilidad_SH.jpg',width=700,height=700,quality=100)
sensibilidadSH(dif,70)
dev.off()

errorSensibilidadSH<-function(dif,N)
{
	a<-1.3
	b<-0.31
	x0<--0.1
	y0<-0.1

	plot(serieSH(x0,y0,a,b,N)-serieSH(x0+dif,y0,a,b,N), type='l', ylab='Diferencia(Serie1, Serie2)', xlab='N', col='red')
}

jpeg('errorSensibilidad_SH.jpg',width=700,height=700,quality=100)
errorSensibilidadSH(dif,70)
dev.off()

#-------------------------------------------------------------------------------------

#diagrama de sensibilidad para el sistema de tinkerbell
serieTK<-function(x,y,a,b,c,d,N)
{
   Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:N)
	{
		Xi[i]<-Xi[i-1]*Xi[i-1]-Yi[i-1]*Yi[i-1]+a*Xi[i-1]+b*Yi[i-1]
      	Yi[i]<-2*Xi[i-1]*Yi[i-1]+c*Xi[i-1]+d*Yi[i-1]
	}

	return(Xi)
}

sensibilidadTK<-function(dif,N)
{	a<-0.5
	b<--0.6
	c<-2.2
	d<-0.5
	x0<-0.1
	y0<-0.1
	y1<--0.5
	y2<-0.2

	plot(serieTK(x0,y0,a,b,c,d,N), xlab="", ylab="", xlim=c(0,N), ylim=c(y1,y2),axes=FALSE, col='blue', type='l')
	par(new=TRUE)
	plot(serieTK(x0+dif,y0,a,b,c,d,N), xlim=c(0,N), ylim=c(y1,y2), col='red', xlab='N', ylab='X',type='l')
}

jpeg('sensibilidad_TK.jpg',width=700,height=700,quality=100)
sensibilidadTK(dif,200)
dev.off()

errorSensibilidadTK<-function(dif,N)
{
	a<-0.5
	b<--0.6
	c<-2.2
	d<-0.5
	x0<-0.1
	y0<-0.1

	plot(serieTK(x0,y0,a,b,c,d,N)-serieTK(x0+dif,y0,a,b,c,d,N), type='l', ylab='Diferencia(Serie1, Serie2)', col='red', xlab='N')
}

jpeg('ErrorSensibilidad_TK.jpg',width=700,height=700,quality=100)
errorSensibilidadTK(dif,200)
dev.off()

#--------------------------------------------------------------------------------

#diagrama de bifurcación para el sistema de lorenz

Lorenz<-function(t, state, parameters) 
{
	with(as.list(c(state, parameters)),
		{
		# rate of change
	 	dX <- s*(Y-X)
		dY <- r*X - Y - X*Z
		dZ <- X*Y - b*Z

		# return the rate of change
		list(c(dX, dY, dZ))
		}
	)
}
#para probar si funciona
parameters<-c(s=10, r=28, b=8/3)
state<-c(X=0.3, Y=0.3, Z=0.3)
times <- seq(0, 100, by = 0.01)
out <- ode(y = state, times = times, func = Lorenz, parms = parameters)
plot(out[,'X'],out[,'Y'],pch='.')
#**********************************

sensibilidadSL<-function(dif,N)
{	parameters<-c(s=10, r=28, b=8/3)
	state<-c(X=0.3, Y=0.3, Z=0.3)
	times <- seq(0, N*0.01, by = 0.01)
	y1<--20
	y2<-20

	out <- ode(y = state, times = times, func = Lorenz, parms = parameters)
	plot(out[,'X'], xlab="", ylab="", xlim=c(0,N), ylim=c(y1,y2),axes=FALSE, col='blue', type='l')
	par(new=TRUE)
	state<-c(X=0.3+dif, Y=0.3, Z=0.3)
	out <- ode(y = state, times = times, func = Lorenz, parms = parameters)
	plot(out[,'X'], xlim=c(0,N), ylim=c(y1,y2), col='red', xlab='N', ylab='X',type='l')
}

jpeg('sensibilidad_SL.jpg',width=700,height=700,quality=100)
sensibilidadSL(dif,6000)
dev.off()

errorSensibilidadSL<-function(dif,N)
{
	parameters<-c(s=10, r=28, b=8/3)
	state<-c(X=0.3, Y=0.3, Z=0.3)
	times <- seq(0, N*0.01, by = 0.01)
	y1<--20
	y2<-20

	out1 <- ode(y = state, times = times, func = Lorenz, parms = parameters)
	state<-c(X=0.3+dif, Y=0.3, Z=0.3)
	out2 <- ode(y = state, times = times, func = Lorenz, parms = parameters)
	plot(out1[,'X']-out2[,'X'], type='l', ylab='Diferencia(Serie1, Serie2)', col='red', xlab='N')
}

jpeg('ErrorSensibilidad_SL.jpg',width=700,height=700,quality=100)
errorSensibilidadSL(dif,6000)
dev.off()

#*********************************************************
#diagrama de sensibilidad para el sistema de ikeda
serieIK<-function(x,y,a,b,c,d,N)
{
	Xi<-Yi<-numeric()
	Xi[1]<-x
	Yi[1]<-y
	for(i in 2:N)
	{
		u<-(c-d)/(1+Xi[i-1]*Xi[i-1]+Yi[i-1]*Yi[i-1])
		Xi[i]<-a+b*(Xi[i-1]*cos(u)-Yi[i-1]*sin(u))
		Yi[i]<-b*(Xi[i-1]*sin(u)+Yi[i-1]*cos(u))	
	}
	return(Xi)
}

sensibilidadIK<-function(dif,N)
{	a<-1-0
	b<-0.9
	c<-0.4
	d<-6.0
	x0<-0.1
	y0<-0.1
	y1<--0.5
	y2<-1.6

	plot(serieIK(x0,y0,a,b,c,d,N), xlab="", ylab="", xlim=c(0,N), ylim=c(y1,y2),axes=FALSE, col='blue', type='l')
	par(new=TRUE)
	plot(serieIK(x0+dif,y0,a,b,c,d,N), xlim=c(0,N), ylim=c(y1,y2), col='red', xlab='N', ylab='X',type='l')
}

jpeg('sensibilidad_IK.jpg',width=700,height=700,quality=100)
sensibilidadIK(dif,80)
dev.off()

errorSensibilidadIK<-function(dif,N)
{
	a<-1-0
	b<-0.9
	c<-0.4
	d<-6.0
	x0<-0.1
	y0<-0.1

	plot(serieIK(x0,y0,a,b,c,d,N)-serieIK(x0+dif,y0,a,b,c,d,N), type='l', ylab='Diferencia(Serie1, Serie2)', col='red', xlab='N')
}

jpeg('ErrorSensibilidad_IK.jpg',width=700,height=700,quality=100)
errorSensibilidadIK(dif,80)
dev.off()

#.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#el ancho de la linea lwd=num positivo
#tamaño de la fuente del los ejes y la leyenda de los ejes
#cex.axis="num" and cex.lab="num"
