#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "dobleTetraedro.h"

DobleTetraedro::DobleTetraedro(vert longitud, color red, color green, color blue)
{
	lado = longitud;

	verDobleTetraedro();
	asignaColores(red, green, blue);
}

void DobleTetraedro::verDobleTetraedro(){
	vertices = {0,0,lado, lado,0,lado,
		0,lado,lado,	lado,lado,lado,	
		0,0,0,			lado,0,0,
		0,lado,0,		lado,lado,0};


	caras =	{0,1,2, 	1,3,2, 
			2,3,7, 		2,7,6,
			1,7,3,		1,5,7,
			6,7,4,		7,5,4,
			0,4,1,		1,4,5,
			2,6,4,		0,2,4
		};
}

void DobleTetraedro::verPrimerTetraedro(void){
	vertices = {lado,0,lado, 0,lado,lado,	
		lado,lado,lado,	lado,lado,0};

	caras =	{0,2,1, 0,3,2,
		2,3,1,	0,1,3
		};
}

void DobleTetraedro::verSegundoTetraedro(void){
	vertices = {0,0,0,	0,lado,0,
		lado,lado,0,	0,lado,lado};

	caras =	{0,1,2, 0,3,1,
		1,3,2,	0,2,3
		};
}

void DobleTetraedro::setLado(vert longitud){
	if (longitud >= 0){
		lado = longitud;
		verDobleTetraedro();
	}
}
	
vert DobleTetraedro::getLado(void){
	return lado;
}