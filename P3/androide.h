#ifndef _ANDROIDE_H
#define _ANDROIDE_H

#include "objeto3D.h"
#include "semiesfera.h"
#include "cilindro.h"
using namespace std;

class Androide : public Objeto3D {
	private:
		Semiesfera *semiesfera;
		Cilindro *cilindro;
		void dibujarPierna(GLenum mode, bool ajedrez = false);
		void dibujarBrazo(GLenum mode, bool ajedrez = false);
		void dibujarCuerpo(GLenum mode, bool ajedrez = false);
		void dibujarCabeza(GLenum mode, bool ajedrez = false);
		void dibujarCabezaCuerpo(GLenum mode, bool ajedrez = false);
		void dibujarAndroide(GLenum mode, bool ajedrez = false);
		float rot_cabeza, rot_brazo_der, rot_brazo_izq, rot_pierna_der, rot_pierna_izq;
		bool cambio_de_sentido_piernas, cambio_de_sentido_cabeza;

	public:
		Androide();
		~Androide();
		void animar();
		void dibujar(GLenum mode);
		void dibujarAjedrez(void);
		float getRotacionCabeza();
		void setRotacionCabeza(float rot);
		float getRotacionBrazoDerecho();
		void setRotacionBrazoDerecho(float rot);
		float getRotacionBrazoIzquierdo();
		void setRotacionBrazoIzquierdo(float rot);
		float getRotacionPiernaDerecha();
		void setRotacionPiernaDerecha(float rot);
		float getRotacionPiernaIzquierda();
		void setRotacionPiernaIzquierda(float rot);
};

#endif