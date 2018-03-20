#ifndef _CILINDRO_H
#define _CILINDRO_H

#include "objetoDeRevolucion.h"
using namespace std;

class Cilindro : public ObjetoDeRevolucion {
	private:
		vert altura;
		vert radio;

	public:
		// Constructor
		Cilindro(vert alt, vert rad, vert num_rev, color r, color g, color b);

};

#endif