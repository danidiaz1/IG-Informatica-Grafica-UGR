#ifndef _SEMIESFERA_H
#define _SEMIESFERA_H

#include "objetoDeRevolucion.h"
using namespace std;

class Semiesfera : public ObjetoDeRevolucion {
	private:
		vert radio;
		void calcularPerfilInicial(void);

	public:
		// Constructor
		Semiesfera(vert rad, vert num_rev, color r, color g, color b);

};

#endif