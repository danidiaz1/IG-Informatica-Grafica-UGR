#ifndef _OBJETOREVOLUCION_H
#define _OBJETOREVOLUCION_H

#include "objeto3D.h"
using namespace std;

class ObjetoDeRevolucion : public Objeto3D {
protected:

	/************************ ATRIBUTOS *********************/
	float numero_revoluciones;
	char eje_rotacion; // 'X', 'Y' o 'Z'
	bool ver_tapa_sup, ver_tapa_inf; // controlan si ver o no las tapas superior o inferior.
	
	vector<vert> perfil_inicial; // vértices del perfil inicial.

	/*********************** MÉTODOS ***********************/

	// Calcula el conjunto de todos los vértices de la figura haciendo transformaciones de rotación
	// a partir del perfil inicial, dado el angulo de rotacion y el eje, almacenados en atributos de
	// la clase.
	void CalcularConjuntoVertices(void);

	// Calcula el vértice central de la tapa inferior y superior y los añade al vector de vertices en este orden.
	// El vértice central de la tapa superior sera el x, y o z máximo (dependiendo del eje de rotación),
	// idem para la tapa inferior pero el menor.
	void CalcularVerticesTapas(void);

	/* Las caras longitudinales del sólido (triángulos) se crean a partir de los vértices de dos
    perfiles consecutivos Qj y Qj+1. Tomando dos puntos adyacentes en cada uno de los
    dos perfiles Qj y Qj+1 y estando dichos puntos a la misma altura, se pueden crear
    dos triángulos */
	void CalcularConjuntoCaras(void);

	// Calcula las caras de las tapas inferior y superior y las añade al vector de caras, en este orden
	void CalcularCarasTapas(void);

	/* Quita las tapas del perfil inicial si este las tiene, para que no se repitan varias veces
	   al hacer la revolución. */
	void QuitarTapas(void);

	/* Método que realiza los cambios en drawElements para ver las tapas o no. Uno para modos normales,
	otro para modo ajedrez */
	void mostrarTapas(void);
	void mostrarTapasAjedrez(void);


public:
    // Constructores, uno para un vector con el perfil inicial, otro a partir de un fichero PLY. Se debe especificar
    // el ángulo de rotación, el eje de rotación y el color de la figura.
    ObjetoDeRevolucion(vector<float> &v, float num_revoluciones, char eje, color red, color green, color blue, bool tieneTapas);
    ObjetoDeRevolucion(char *File_name, float num_revoluciones, char eje, color red, color green, color blue, bool tieneTapas);
    // Constructor por defecto
    ObjetoDeRevolucion();

    // Establece los atributos de la clase ver_tapa_superior y ver_tapa_inferior. En función de los mismos, se 
    // tendrán en cuenta o no las caras de dichas tapas para dibujarlas, en el método void dibujar(GLenum mode).
    void verTapas(const bool superior, const bool inferior);

    // Tenemos que redefinir los método dibujar para conseguir ver o no la tapa superior o la inferior.
    void dibujar(GLenum mode = GL_FILL);
    void dibujarAjedrez(void);

    // Métodos get y set para el angulo de rotación
    void setNumeroRevoluciones(float num);
	float getNumeroRevoluciones(void);
};
#endif
