#include "shuriken.h"
#include <iostream>
using namespace std;

Shuriken::Shuriken(color red, color green, color blue)
	: ObjetoPLY("../Modelos_ply/modelos_ply/Shuriken1.ply",red,green,blue)
{
	velocidad=1;
	grado_traslacion = velocidad*2;
	grado_rotacion = velocidad*20;
	traslacion = 0;
	rotacion = 0;
}

void Shuriken::animar(bool activar){
	if (activar){
		rotacion+=grado_rotacion;
		traslacion+=grado_traslacion;
	}
}

float Shuriken::getTraslacion(void){
	return traslacion;
}

float Shuriken::getRotacion(void){
	return rotacion;
}

void Shuriken::setTraslacion(float t){
	traslacion = t;
}

void Shuriken::setRotacion(float r){
	rotacion = r;
}

float Shuriken::getVelocidad(void){
	return velocidad;
}

void Shuriken::setVelocidad(float v){
	velocidad = v;
	grado_traslacion = velocidad*2;
	grado_rotacion = velocidad*20;		
}