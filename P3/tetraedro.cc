#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "tetraedro.h"

Tetraedro::Tetraedro(vert longitud, GLubyte red, GLubyte green, GLubyte blue)
{
	lado = longitud;

	asignaCoordenadas();
	asignaColores(red,green,blue);
}

void Tetraedro::asignaCoordenadas(void){
	vertices = {0,lado,0,	-lado,-lado,0,
		lado,-lado, 0,		0,-lado,-lado};


	caras =	{0,1,2,	2,3,0,
		1,0,3,	3,2,1};

	asignaVectoresAjedrez();
}

void Tetraedro::setLado(vert longitud){
	if (longitud >= 0){
		lado = longitud;
		asignaCoordenadas();
	}
}

vert Tetraedro::getLado(void){
	return lado;
}