#ifndef _SHURIKEN_H
#define _SHURIKEN_H

#include "objetoPLY.h"
using namespace std;

class Shuriken : public ObjetoPLY {

private:
	float grado_traslacion, grado_rotacion, rotacion, traslacion, velocidad; 
public:
    Shuriken(color red, color green, color blue);
    void animar(bool activar = false);
    float getTraslacion(void);
    float getRotacion(void);
	void setTraslacion(float t);
	void setRotacion(float r);
	float getVelocidad(void);
	void setVelocidad(float v);

};

#endif