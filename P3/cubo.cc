#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "cubo.h"

Cubo::Cubo(vert longitud, color red, color green, color blue)
{
	lado = longitud;

	asignaCoordenadas();
	asignaColores(red, green, blue);
}

void Cubo::asignaCoordenadas(){

	GLfloat lado_mitad = lado/2;
	vertices = {-lado_mitad,0,lado_mitad, lado_mitad,0,lado_mitad,
		-lado_mitad,lado,lado_mitad,	lado_mitad,lado,lado_mitad,	
		-lado_mitad,0,-lado_mitad,			lado_mitad,0,-lado_mitad,
		-lado_mitad,lado,-lado_mitad,		lado_mitad,lado,-lado_mitad};


	caras =	{0,1,2, 	1,3,2, 
			2,3,7, 		2,7,6,
			1,7,3,		1,5,7,
			6,7,4,		7,5,4,
			0,4,1,		1,4,5,
			2,6,4,		0,2,4
		};

	asignaVectoresAjedrez();	
}

void Cubo::setLado(vert longitud){
	if (longitud >= 0){
		lado = longitud;
		asignaCoordenadas();
	}
}
	
vert Cubo::getLado(void){
	return lado;
}