#ifndef _MANO_H
#define _MANO_H

#include "objeto3D.h"
#include "semiesfera.h"
#include "cilindro.h"
#include "cubo.h"
#include "objetoPLY.h"
#include "shuriken.h"
using namespace std;

class Mano : public Objeto3D {
	private:
		// Variables
		Semiesfera *semiesfera;
		Cilindro *cilindro;
		Cubo *cubo;
		Shuriken *shuriken;
		bool extension_mano, extension_antebrazo, animar_shuriken;
		/* Vector de rotaciones de cada dedo, donde:
			v[0] = rotacion 3º falange dedo indice
			v[1] = rotacion 2º falange dedo indice
			v[2] = rotacion 1º falange dedo indice
			v[3] = rotacion 3º falange dedo corazon
			v[4] = rotacion 2º falange dedo corazon
			....
			....
			....
			v[12] = rotacion 2º falange dedo pulgar
			v[13] = rotacion 1º falange dedo pulgar

		*/
		vector< GLfloat > rot_dedos;
		GLfloat rot_munieca_x, rot_antebrazo_y, rot_antebrazo_x, rot_antebrazo_z;

		// Constantes de escalado.
		const static vert ESCALADO_Y_PRIMERA_FALANGE, ESCALADO_Y_TERCERA_FALANGE,
			ESCALADO_X_PALMA, ESCALADO_Y_PALMA;

		// Variables para animacion
		float grado_contraccion_antebrazo, grado_extension_antebrazo, grado_contraccion_munieca,
			grado_extension_munieca, grado_contraccion_dedos, grado_extension_dedos, grado_disparo,
			velocidad;

		GLfloat m[16];
		// Métodos
		// Primera falange: La más pegada a la mano
		// Segunda falange: La del medio
		// Tercera falange: La última, la más pequeña
		void dibujarPrimeraFalange(GLenum mode, bool ajedrez = false);
		void dibujarSegundaFalange(GLenum mode, bool ajedrez = false);
		void dibujarTerceraFalange(GLenum mode, bool ajedrez = false);
		/*Donde numero significa el dedo al que nos referimos:
			0 = indice
			1 = corazon
			2 = anular
			3 = meñique

			Para el pulgar hay otro método ya que solo tiene 2 falanges.
		*/
		void dibujarDedo(int numero, GLenum mode, bool ajedrez = false);
		void dibujarDedoPulgar(GLenum mode, bool ajedrez = false);
		void dibujarPalma(GLenum mode, bool ajedrez = false);
		void dibujarMano(GLenum mode, bool ajedrez = false);
		void dibujarAntebrazo(GLenum mode, bool ajedrez = false);
		void dibujarShuriken(GLenum mode, bool ajedrez = false);


	public:
		Mano();
		~Mano();
		void animar();
		void dibujar(GLenum mode);
		void dibujarAjedrez(void);
		/*void setDesplazamientoShuriken(float desplazamiento);
		float getDesplazamientoShuriken(void);*/
		float getRotAntebrazoX(void);
		float getVelocidad(void);
		void setVelocidad(float v);
};

#endif
